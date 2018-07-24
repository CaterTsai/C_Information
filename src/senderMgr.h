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
		cout << "Send:" << c1 << " " << c2 << " " << c3 << ";"<< endl;
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
	}

	bool send(eCubeType type, array<int, cColorNumEachUnit> &data)
	{

		if (_senderMgr.find(type) != _senderMgr.end())
		{
			return _senderMgr[type].send(data[0], data[1], data[2]);
		}
		else
		{
			ofLog(OF_LOG_ERROR, "[senderMgr::send]Can't found sender");
			return false;
		}
	}

private:
	map<eCubeType, senderUnit> _senderMgr;

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


