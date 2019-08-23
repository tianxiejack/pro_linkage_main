/*
 * ptzInterface.hpp
 *
 *  Created on: 2019年5月14日
 *      Author: d
 */

#ifndef PTZINTERFACE_HPP_
#define PTZINTERFACE_HPP_

//const float UNVALID = 2.0;

class CptzInterface
{
public:
		virtual void queryPos(){};
		virtual void queryZoom(){};
		virtual void getpos(int& pan, int& til){};
		virtual void getzoom(int& zoom){};

		virtual void ptzStop(){};
		virtual void ptzSetPos(unsigned int posx, unsigned int posy){};
		virtual void setZoomPos(unsigned int value){};
		virtual void setZoomSpeed(int speed){};
		virtual void setPanSpeed(int speed){};
		virtual void setTiltSpeed(int speed){};
		virtual void setIrisSpeed(int speed){};
		virtual void setFocusFarSpeed(int speed){};
		virtual void setFocusNearSpeed(int speed){};

		virtual int runToPrepos(int arg = 0){};
		virtual void setPrepos(int& preposx,int& preposy){};
		virtual void simpleQueryZoom(){};

		virtual void setMtdMonitorP(int value){};
		virtual void setMtdMonitorT(int value){};
		virtual void setMtdMonitorZ(int value){};


		virtual void setPltSpeed(float p,float t,float z){};
		virtual void getpos(float& pan, float& til,float& zoom){};
		virtual void setpos(float& pan, float& til,float& zoom){};
};

#endif /* PTZINTERFACE_HPP_ */
