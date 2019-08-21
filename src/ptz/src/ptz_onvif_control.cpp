/*
 * ptz_onvif_control.cpp
 *
 *  Created on: 2019年8月20日
 *      Author: alex
 */

#include "ptz_onvif_control.hpp"
#include <stdio.h>
CPTZ_ONVIF::CPTZ_ONVIF()
{
	m_onvifHanle = IOnvif::getinstance();
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



