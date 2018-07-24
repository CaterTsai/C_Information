#include "senderMgr.h"

//--------------------------------------------------------------
senderMgr* senderMgr::pInstance = 0;
senderMgr* senderMgr::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new senderMgr();
	}
	return pInstance;
}

//--------------------------------------------------------------
void senderMgr::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}