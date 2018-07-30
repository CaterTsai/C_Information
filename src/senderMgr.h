#pragma once

#include "constParameter.h"
#include "ofxUDPManager.h"

class senderUnit
{
public:
	senderUnit() :_isSetup(false)
	{}
	void init(string ip, int port)
	{
		_ip = ip;
		_port = port;
		_udp.Create();
		_udp.Connect(ip.c_str(), port);
		_udp.SetNonBlocking(true);
		_isSetup = true;
	}

	bool send(int c1, int c2, int c3)
	{
		if (!_isSetup || !_canSend)
		{
			return false;
		}

		char msg[cUdpSendLength] = { 0 };
		msg[0] = c1;
		msg[1] = c2;
		msg[2] = c3;
		msg[3] = cUdpSendEnd;
		_udp.Send(msg, cUdpSendLength);
		
		_canSend = false;
		_timer = cUdpSendInterv;

		return true;
	}

	void update(float delta)
	{
		if (!_canSend)
		{
			_timer -= delta;
			if (_timer <= 0.0f)
			{
				_canSend = true;
			}
		}
	}
private:
	bool _isSetup, _canSend;
	int _port;
	string _ip;
	ofxUDPManager _udp;
	float _timer;
};

class senderMgr
{
public:
	void update(float delta)
	{
		for (auto& iter : _senderMgr)
		{
			iter.second.update(delta);
		}

	}
	void addSender(eCubeType type, string ip, int port)
	{
		_senderMgr.insert(make_pair(type, senderUnit()));
		_senderMgr[type].init(ip, port);
		
		array<int, cColorNumEachUnit> color = { 0 };
		_dataCheckr.insert(make_pair(type, color));

	}

	void send(eCubeType type, array<int, cColorNumEachUnit> &data)
	{

		if (_senderMgr.find(type) != _senderMgr.end())
		{
			bool isSame = true;
			for (int i = 0; i < cColorNumEachUnit; i++)
			{
				if (data[i] != _dataCheckr[type][i])
				{
					_dataCheckr[type][i] = data[i];
					isSame = false;
				}
			}

			if (!isSame)
			{
				_senderMgr[type].send(data[0], data[1], data[2]);
			}
		}
		else
		{
			ofLog(OF_LOG_ERROR, "[senderMgr::send]Can't found sender");
			
		}
	}

private:
	map<eCubeType, senderUnit> _senderMgr;
	map<eCubeType, array<int, cColorNumEachUnit>> _dataCheckr;
//-------------------
//Singleton
//-------------------
private:
	senderMgr()
	{
		
	};
	~senderMgr()
	{
		senderMgr::Destroy();
	}
	senderMgr(senderMgr const&);
	void operator=(senderMgr const&);

public:
	static senderMgr* GetInstance();
	static void Destroy();

private:
	static senderMgr *pInstance;
};


