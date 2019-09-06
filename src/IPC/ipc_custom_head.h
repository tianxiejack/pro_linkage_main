/*
 * ipc_custom_head.h
 *
 *  Created on: 2019骞?鏈?4鏃?
 *      Author: alex
 */

#ifndef IPC_CUSTOM_HEAD_HPP_
#define IPC_CUSTOM_HEAD_HPP_

#ifdef __cplusplus
extern "C" {
#endif

#include "Ipcctl.h"
#include "stdlib.h"
#include <string.h>

#define CFGID_FEILD_MAX	16
#define CFGID_BLOCK_MAX	128
#define CFGID_USEROSD_MAX	32
#define USEROSD_LENGTH	128

#define DEFAULTPATH "/"

typedef enum 
{
	sensor,  /*0*/
	BoresightPos,
	AcqPos,
	sceneTrk,
	trk,
	mtd,
	mtdSelect,
	sectrk,
	posmove,
	workmode,
	Iris,
	
	focus,
	exit_IrisAndFocus,
	exit_img,
	read_shm_config,
	read_shm_block,
	read_shm_single,
	read_shm_usrosd,
	querypos,
	setPos,
	setSpeed,
	
	ballstop,
	josctrl,
	josmode,
}CMD_ID;


typedef enum 
{
    IPC_TOIMG_MSG = 0,  // SERVER TO CLIENT
    IPC_FRIMG_MSG,		// CLIENT TO SERCER
    IPC_IMG_SHA,
    IPC_USER_SHA,
    IPC_SEM,
   
    
    IPC_GSTREAM_PTZ=10, //attach to the gstreamer app of DAO
	IPC_MAX,

}IPC_MTYPE;

typedef enum
{
	shm_rdonly,
	shm_rdwr
}shm_perms;


typedef enum
{
	cursor_move = 1,
	jos_button,
	jos_Dir,
	mouse_button,
	enter,
	jos_menu,
	workMode,
	ctrlMode
}josType;


typedef enum
{
	button0 = 0,
	button1,
	button2,
	button3,
	button4,
	button5,
	button6,
	button7,
	button8,
	button9,
	buttonF1,
	buttonF2,
	buttonF3,
	buttonEnter,
	buttonLeft,
	buttonRigth,
}JosHKButton_t;


typedef struct{
	int type;
	int cursor_x;  //0~1920
	int cursor_y;	//0~1080
	int jos_button;	//0~9
	int jos_Dir;	//up down left right
	int mouse_button;	//left button --- right button
	int mouse_state;	//down:1  up:2
	int enter;	//0,1
	int menu;	//0,1
	int workMode;	//1~3
	int ctrlMode;	//0:ballctrl 1:virtual mouse
}CtrlParams_t;

typedef enum{
	manual_linkage = 0,
	Auto_linkage,
	ballctrl,
	calibmode
}Work_Mode_t;

typedef enum{
	jos = 1,
	mouse
}jos_Mode;

typedef enum{
	jos_mode = 1,
	mouse_mode,
	exit_calibrate_mode
}jos_mouse_Mode;

typedef enum{
	cursor_up = 1,
	cursor_down,
	cursor_left,
	cursor_right,
}josDir;

typedef struct
{
	float p;
	float t;
	float z;
}IPC_ONVIF_POS;

typedef struct
{
	unsigned int intPrm[PARAMLEN/4];
}IPC_PRM_INT;

static IPC_Handl_t * tmpIpc;

static void Ipc_init()
{
	tmpIpc = (IPC_Handl_t*)malloc(IPC_MAX* sizeof(IPC_Handl_t));
	memset(tmpIpc,0,sizeof(IPC_Handl_t)*IPC_MAX);
	char tmp[256] = {"/"};
	memcpy(tmpIpc[IPC_TOIMG_MSG].name,tmp,sizeof(tmp));
	tmpIpc[IPC_TOIMG_MSG].Identify = IPC_TOIMG_MSG;
	tmpIpc[IPC_TOIMG_MSG].Class = IPC_Class_MSG;
	tmpIpc[IPC_TOIMG_MSG].IPCID = IPC_MAX;
	tmpIpc[IPC_TOIMG_MSG].length = 0;
	tmpIpc[IPC_TOIMG_MSG].ptr = NULL;
	
	memcpy(tmpIpc[IPC_FRIMG_MSG].name,tmp,sizeof(tmp));
	tmpIpc[IPC_FRIMG_MSG].Identify = IPC_FRIMG_MSG;
	tmpIpc[IPC_FRIMG_MSG].Class = IPC_Class_MSG;
	tmpIpc[IPC_FRIMG_MSG].IPCID = IPC_MAX;
	tmpIpc[IPC_FRIMG_MSG].length = 0;
	tmpIpc[IPC_FRIMG_MSG].ptr = NULL;
	
	memcpy(tmpIpc[IPC_IMG_SHA].name,tmp,sizeof(tmp));
	tmpIpc[IPC_IMG_SHA].Identify = IPC_IMG_SHA;
	tmpIpc[IPC_IMG_SHA].Class=IPC_Class_SHA;
	tmpIpc[IPC_IMG_SHA].IPCID = IPC_MAX;
	tmpIpc[IPC_IMG_SHA].length = 4*CFGID_FEILD_MAX*CFGID_BLOCK_MAX;
	tmpIpc[IPC_IMG_SHA].RWmode = shm_rdwr;
	tmpIpc[IPC_IMG_SHA].ptr = NULL;

	memcpy(tmpIpc[IPC_USER_SHA].name,tmp,sizeof(tmp));
	tmpIpc[IPC_USER_SHA].Identify = IPC_USER_SHA;
	tmpIpc[IPC_USER_SHA].Class=IPC_Class_SHA;
	tmpIpc[IPC_USER_SHA].IPCID = IPC_MAX;
	tmpIpc[IPC_USER_SHA].length = USEROSD_LENGTH*CFGID_USEROSD_MAX;
	tmpIpc[IPC_USER_SHA].RWmode = shm_rdwr;
	tmpIpc[IPC_USER_SHA].ptr = NULL;

	memcpy(tmpIpc[IPC_SEM].name,tmp,sizeof(tmp));
	tmpIpc[IPC_SEM].Identify = IPC_SEM;
	tmpIpc[IPC_SEM].Class = IPC_Class_SEM;
	tmpIpc[IPC_SEM].IPCID = IPC_MAX;
	tmpIpc[IPC_SEM].ptr = NULL;

	memcpy(tmpIpc[IPC_GSTREAM_PTZ].name,tmp,sizeof(tmp));
	tmpIpc[IPC_GSTREAM_PTZ].Identify = IPC_SEM;
	tmpIpc[IPC_GSTREAM_PTZ].Class = IPC_Class_MSG;
	tmpIpc[IPC_GSTREAM_PTZ].IPCID = IPC_MAX;
	tmpIpc[IPC_GSTREAM_PTZ].length = 0;
	tmpIpc[IPC_GSTREAM_PTZ].ptr = NULL;

	return;
}

//static int *sysConfig = NULL;
//static unsigned char *userConfig = NULL;
static void *ipc_getSharedMem(IPC_MTYPE itype)
{
	if(itype == IPC_IMG_SHA || itype == IPC_USER_SHA)
		return ipc_getSharedAddress(itype);
		//return (void*)IpcHandl[itype].ptr;
	else
		return NULL;
}

#ifdef __cplusplus
}
#endif

#endif /* IPC_CUSTOM_HEAD_HPP_ */