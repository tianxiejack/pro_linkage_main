/*
 * ptz_onvif_control.cpp
 *
 *  Created on: 2019年8月20日
 *      Author: alex
 */

#include "ptz_onvif_control.hpp"
#include <stdio.h>

const float NOCHANGE = 2.0;

CPTZ_ONVIF::CPTZ_ONVIF(const char* ip,const char* username,const char* password)
{
	printf("*********onvif**************\n\n");
	printf("*** ip : %s  \n",ip);
	printf("*** username : %s  \n",username);
	printf("*** password : %s  \n",password);
	
	m_onvifHanle = IOnvif::getinstance(ip,username,password);
}

CPTZ_ONVIF::~CPTZ_ONVIF()
{
}

void CPTZ_ONVIF::ptzStop()
{
	m_onvifHanle->stop();
}

void CPTZ_ONVIF::setPltSpeed(float p,float t,float z)
{
	m_onvifHanle->continuesMove(p, t, z);
}


void CPTZ_ONVIF::getpos(float& pan, float& til,float& zoom)
{
	m_onvifHanle->getPtzStatus(pan, til, zoom);
}


void CPTZ_ONVIF::setpos(float& pan, float& til,float& zoom)
{
	m_onvifHanle->absoluteMove(pan, til, zoom, NOCHANGE,NOCHANGE,NOCHANGE);
}



