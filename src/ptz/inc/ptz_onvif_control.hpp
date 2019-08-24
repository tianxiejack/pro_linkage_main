/*
 * ptz_onvif_control.hpp
 *
 *  Created on: 2019年8月20日
 *      Author: alex
 */

#ifndef PTZ_ONVIF_CONTROL_HPP_
#define PTZ_ONVIF_CONTROL_HPP_

#include "ptzInterface.hpp"
#include "onvifInterface.hpp"

class CPTZ_ONVIF : public CptzInterface
{
	public:
		CPTZ_ONVIF(const char* ip,const char* username,const char* password);
		virtual ~CPTZ_ONVIF();
	
	public:  //interface

		void getpos(float& pan, float& til,float& zoom);
		void setpos(float& pan, float& til,float& zoom);
		void setPltSpeed(float p,float t,float z);
		void ptzStop();
		

	private:
		IOnvif* m_onvifHanle;
	
};



#endif /* PTZ_ONVIF_CONTROL_HPP_ */
