#include "cubeMgr.h"

//--------------------------------------------------------------
cubeMgr* cubeMgr::pInstance = 0;
cubeMgr* cubeMgr::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new cubeMgr();
	}
	return pInstance;
}

//--------------------------------------------------------------
void cubeMgr::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}