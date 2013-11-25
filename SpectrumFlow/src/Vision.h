/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  Vision.h, created by Marek Bereza on 25/11/2013.
 */

#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCvOpticalFlowLK.h"


#define VISION_WIDTH 640
#define VISION_HEIGHT 480


class Vision {
	
public:
	void setup();
	void update();
	void draw();
	
private:
	
	void computeOpticalFlow();
	
	ofVideoGrabber grabber;
	
	ofxCvColorImage frame;
	ofxCvGrayscaleImage greyCurr;
	ofxCvGrayscaleImage greyPrev;
	
	ofxCvOpticalFlowLK flow;
	int flowSize;
};
