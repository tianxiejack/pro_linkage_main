/*
 * eventParsing.hpp
 *
 *  Created on: 2019年5月7日
 *      Author: d
 */

#ifndef EVENTPARSING_HPP_
#define EVENTPARSING_HPP_
#include <iostream>
#include "js_usb.hpp"
#include "PortFactory.hpp"
#include "CMessage.hpp"
#include <vector>
#include  "osa_thr.h"
#include "osa_mutex.h"
#include "configtable.h"
#include "ipc_custom_head.h"

using namespace std;

#define AXIS_X 0
#define AXIS_Y 1
#define POV_BUTTON 5
#define BUTTON 6

#define  	RECV_BUF_SIZE   	1024
#define  	TIME_FOR_THREAD_END 3
#define 	MAXSENDSIZE 		136

typedef enum
{
	/*button1234 ==>data[5]
	 * other ===> data[6]
	 * */
	js_1 = 0x1f,
	js_2 = 0x2f,
	js_3 = 0x4f,
	js_4 = 0x8f,
	js_5 = 0x01,
	js_6 = 0x02,
	js_7 = 0x04,
	js_8 = 0x08,
	js_9 = 0x10,
	js_10 = 0x20,
	js_11 = 0x40,
	js_12 = 0x80,
}js_button;

typedef enum
{
	/*pov ==> data[5]*/
	js_pov_reset = 0x0f,
	js_pov_up = 0x00,
	js_pov_rightUp = 0x01,
	js_pov_right = 0x02,
	js_pov_rightDown = 0x03,
	js_pov_down = 0x04,
	js_pov_leftDown = 0x05,
	js_pov_left = 0x06,
	js_pov_leftUp = 0x07,
}js_pov;


typedef enum{
	usb_1_8 = 0,
	usb_special,
	usb_enter,
	usb_X,
	usb_Y,
	usb_Z
}HK_JosParams;

typedef enum{
	hk_button_1 = 0x1,
	hk_button_2 = 0x2,
	hk_button_3 = 0x4,
	hk_button_4 = 0x8,
	hk_button_5 = 0x10,
	hk_button_6 = 0x20,
	hk_button_7 = 0x40,
	hk_button_8 = 0x80,
}hk_button;

typedef enum{
	hk_button_9 = 0x1,
	hk_button_0 = 0x2,
	hk_button_f1 = 0x10,
	hk_button_f2 = 0x20,
	hk_button_f3 = 0x40,
	hk_button_left = 0x4,
	hk_button_right = 0x8,
}hk_button_spe;



typedef enum _sys_msg_id_ {
	MSGID_SYS_INIT  = 0,
   	MSGID_EXT_INPUT_TRACKCTRL,
	MSGID_EXT_INPUT_SwitchSensor,
	MSGID_EXT_INPUT_TRACKSEARCHCTRL,
	MSGID_EXT_INPUT_captureMode,
	MSGID_EXT_INPUT_IrisAndFocusAndExit,
	MSGID_EXT_INPUT_workMode,
	MSGID_EXT_INPUT_JOSPOS,
	MSGID_EXT_INPUT_TRKMOVE,
	
	MSGID_COM_INPUT_SELFCHECK,
	MSGID_COM_INPUT_TRKCONTROL,
	MSGID_COM_INPUT_SECTRKPOS,
	MSGID_COM_INPUT_MTDSELECT,
	MSGID_COM_INPUT_GATEMOVE,
	MSGID_COM_INPUT_ZOOMCTRL,
	MSGID_COM_INPUT_APERTURECTRL,
	MSGID_COM_INPUT_FOCUSCTRL,
	MSGID_COM_INPUT_SETPLATSPEED,
	MSGID_COM_INPUT_SETPLATANGLE,
	MSGID_COM_INPUT_PREPOS,
	MSGID_COM_INPUT_SETZOOM,
	MSGID_COM_INPUT_QUERYPTZPOS,
	MSGID_COM_INPUT_GETZOOM,
	MSGID_COM_INPUT_TRKOUTPUT,
	MSGID_COM_INPUT_SETCFG,
	MSGID_COM_INPUT_GETCFG,
	MSGID_COM_INPUT_SETOSD,
	MSGID_COM_INPUT_DEFAULTCFG,
	MSGID_COM_INPUT_SAVECFG,
	MSGID_COM_INPUT_SETPOS,
	MSGID_IPC_INPUT_CTRLPARAMS,
	MSGID_COM_INPUT_STOP,
	MSGID_COM_INPUT_LINKSPEED,
	MSGID_INPUT_TEST,
    MAX_MSG_NUM
}MSG_PROC_ID;



typedef enum{
	ACK_SelfTest = 0x01,
	ACK_Sensor = 0x02,
	ACK_Workmode = 0x03,
	ACK_CaptureMode = 0x04,
	ACK_TrkStat = 0x05,
	ACK_SectrkStat = 0x07,
	ACK_CtrlPos = 0x10,
	ACK_PresetPos = 0x11,
	ACK_SetZoom = 0x12,
	ACK_QueryPos = 0x41,
	ACK_QueryZoom = 0x42,
	ACK_output = 0x43,
	ACK_SetConfig = 0x51,
	ACK_GetConfig = 0x52,
	ACK_SetOsd = 0x53,
	ACK_DefaultConfig = 0x54,
	ACK_impconfig = 0x55,
	ACK_expconfig = 0x56,
	ACK_saveconfig = 0x57,
	ACK_upgradefw = 0x58,


	ACK_GetOsd = 0x90,
	ACK_MAXID
}ACK_Cmdid;

typedef struct{
	int connfd;
	bool bConnecting;
    	OSA_ThrHndl getDataThrID;
    	OSA_ThrHndl sendDataThrID;
}CConnectVECTOR;

typedef struct{
	int block;
	int field;
	int value;
}Set_config_t;

typedef struct{
	int block;
	int field;
	unsigned char buf[USEROSD_LENGTH + 1];
}Get_osd_t;

typedef struct{
	int block;
	int field;
}Get_config_t;

typedef struct{
	unsigned char osdID;
	unsigned char type;
	unsigned char buf[USEROSD_LENGTH + 1];
}osdbuffer_t;

typedef struct{
	int fd;
	int type;// 1. /dev/ttyTHS1   2.network
}comtype_t;
typedef struct{
	comtype_t comtype;
	int displaychid;
	int capturechid;
	int workmode;
	int capturemode;
	int trkctrl;
	int trkmove;
	int sectrkctrl;
	short sectrkx;
	short sectrky;
	int mtdselect;
	int gatemove;
	unsigned short gatestepx;
	unsigned short gatestepy;
	int zoomctrl;
	int irisctrl;
	int focusctrl;
	short platspeedx;
	short platspeedy;
	unsigned short platPan;
	unsigned short platTilt;
	int prepos;
	unsigned short setzoom;
	int trkoutput;
	vector<Set_config_t>  setConfigQueue;
	vector<Get_config_t>  getConfigQueue;
	vector<int>  defConfigQueue;
	osdbuffer_t setosd;
	float linkspeedx;
	float linkspeedy;
	float linkspeedz;
	float linkposp;
	float linkpost;
	float linkposz;
	unsigned char oriDatap;
	unsigned char oriDatat;
}ComParams_t;

typedef struct{
	comtype_t comtype;
	int cmdid;
	int displaychid;
	int capturechid;
	int workmode;
	int capturemode;
	int trkctrl;
	int sectrkctrl;
	unsigned short ctrlpan;
	unsigned short ctrltil;
	unsigned short setzoom;
	int trkstat;
	unsigned short querypan;
	unsigned short querytil;
	unsigned short queryzoom;
	int outtype;
	float trkerrx;
	float trkerry;
	vector<Set_config_t>  setConfigQueue;
	vector<Set_config_t>  getConfigQueue;
	vector<Get_osd_t> getOsdQueue;
	vector<int>  defConfigQueue;
	int saveconfig;
}ACK_ComParams_t;

typedef struct {
	comtype_t comtype;
    	int byteSizeSend;
   	unsigned char sendBuff[MAXSENDSIZE];
}sendInfo;

class CEventParsing
{
public:
	CEventParsing();
	~CEventParsing();
	CjoyStick* _Js;
	CMessage* _Msg;
	OSA_ThrHndl jsEvent_thid, comrecvEvent_thid, comsendEvent_thid,Getaccept_thid, ReclaimConnect_thid;
	static void *thread_jsEvent(void *p);
private:
	static CEventParsing* pThis;
	bool exit_jsParsing,exit_comParsing,exit_netParsing;
	bool m_josValid;
	void parsingJostickEvent(unsigned char* jos_data);


public:
	static void *thread_comrecvEvent(void *p);
	static void *thread_comsendEvent(void *p);
	static void *thread_Getaccept(void *p);
	static void *thread_ReclaimConnect(void *p);
	ComParams_t ComParams;
	
private:
	static void *thread_netrecvEvent(void *p);
	void parsingframe(unsigned char *tmpRcvBuff, int sizeRcv, comtype_t comtype);
	int parsingComEvent(comtype_t comtype);
	unsigned char recvcheck_sum(int len_t);
	int getSendInfo(sendInfo * psendBuf);
	int  package_ACK_Sensor(sendInfo *psendBuf);
	int  package_ACK_Workmode(sendInfo *psendBuf);
	int  package_ACK_Capturemode(sendInfo *psendBuf);
	int  package_ACK_TrkStat(sendInfo *psendBuf);
	int  package_ACK_SecTrkStat(sendInfo *psendBuf);
	int  package_ACK_CtrlPos(sendInfo *psendBuf);
	int  package_ACK_SetZoom(sendInfo *psendBuf);
	int  package_ACK_QueryPos(sendInfo *psendBuf);
	int  package_ACK_QueryZoom(sendInfo *psendBuf);
	int  package_ACK_Output(sendInfo *psendBuf);
	int  package_ACK_GetConfig(sendInfo *psendBuf);
	int  package_ACK_SetConfig(sendInfo *psendBuf);
	int  package_ACK_DefaultConfig(sendInfo *psendBuf);
	int  package_ACK_SaveConfig(sendInfo *psendBuf);
	int  package_ACK_GetOsd(sendInfo *psendBuf);
	int  package_ACK_commondata(sendInfo *psendBuf, int bodylen);
	unsigned char sendcheck_sum(unsigned char *tmpbuf, int len);
	int comfd;
	CPortInterface *pCom1, *pCom2;
	vector<unsigned char>  rcvBufQue;
	vector<CConnectVECTOR *>  connetVector;
	OSA_MutexHndl mutexConn;
	CtrlParams_t m_josParams;

private:
	void parsingJostickPovData(unsigned char* jos_data);
	void parsingJostickButtonData(unsigned char* jos_data);
	void parsingJostickAxisData(unsigned char* jos_data);
	void buttonStopHandle(int index);
	void parsingHKButton(unsigned char* jos_data);
	void parsingHKJos(unsigned char* jos_data);

	float HK_JosToSpeedX(int X);
	float HK_JosToSpeedY(int Y);
	float HK_JosToSpeedZ(int Z);

};




#endif /* EVENTPARSING_HPP_ */
