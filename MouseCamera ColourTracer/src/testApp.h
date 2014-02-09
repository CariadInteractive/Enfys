#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxFatLine.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void mouseMoved(int x, int y);
	void mousePressed(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
	void keyPressed(int key);
	
	ofVideoGrabber cam;	
//	ofxCv::ContourFinder contourFinder;
//	float threshold;
//	ofxCv::TrackingColorMode trackingColorMode;
//	ofColor targetColor;
    
    ofTrueTypeFont dinFont;
    
    ofColor currentColour;
    
    vector<ofColor> targetColours;
    
    ofxFatLine mouseLine;
    ofVec3f previousMousePosition;
    ofVec3f mouseVelocity;
};
