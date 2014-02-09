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
 *  messed with by Joel Gethin Lewis on 9/2/2014.
 */

#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCvOpticalFlowLK.h"
#include "ofxXmlGui.h"
#include "ofxCv.h"

class Vision {
	
public:
	void setup();
	void setupGui(xmlgui::SimpleGui &gui);
	
	
	void update();
	void draw();
	ofxCvOpticalFlowLK &getOpticalFlow();
    ofxCv::ContourFinder &getContourFinder();

private:
	bool flipHorizontal;
	
    void trackColours();
	void computeOpticalFlow();
	
	ofVideoGrabber grabber;
	
	ofxCvColorImage frame;
	ofxCvGrayscaleImage grey;
	
	
	ofxCvGrayscaleImage greyCurr;
	ofxCvGrayscaleImage greyPrev;
	
	ofxCvOpticalFlowLK flow;
	int flowSize;
    
    ofxCv::ContourFinder contourFinder;
	float threshold;
	ofxCv::TrackingColorMode trackingColorMode;
	ofColor targetColour;
    ofFloatColor pickedColour;
    bool pickColour;
    bool drawTracker;
};
