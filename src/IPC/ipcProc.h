#ifndef _IPCPROC_H_
#define _IPCPROC_H_

#include "osa_thr.h"
#include "ipc_custom_head.h"
#include <string>
#pragma once
using namespace std;

typedef struct{
	int status;
	float errx;
	float erry;
}GstRectParm_t;
	
class  CIPCProc{

public:
	CIPCProc();
	~CIPCProc();

	int IPCSendMsg(CMD_ID cmd, void* prm, int len);
	int IPCRecvMsg(void* prm);
	int IPCRecvGstMsg(void* prm);

	GstRectParm_t m_gstRectParm;
	IPC_ONVIF_POS m_setpos;
	IPC_ONVIF_POS m_setspeed;
	CtrlParams_t m_ctrlprm;
	
private:
	static CIPCProc* pThis;
	pthread_mutex_t mutex;

};
#endif
