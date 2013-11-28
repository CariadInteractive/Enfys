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
#include "ofxXmlGui.h"




class Vision {
	
public:
	void setup();
	void setupGui(xmlgui::SimpleGui &gui);
	
	
	void update();
	void draw(bool debug);
	ofxCvOpticalFlowLK &getOpticalFlow();

private:
	bool flipHorizontal;
	
	void computeOpticalFlow();
	
	ofVideoGrabber grabber;
	
	ofxCvColorImage frame;
	ofxCvGrayscaleImage grey;
	
	
	ofxCvGrayscaleImage greyCurr;
	ofxCvGrayscaleImage greyPrev;
	
	ofxCvOpticalFlowLK flow;
	int flowSize;
};
