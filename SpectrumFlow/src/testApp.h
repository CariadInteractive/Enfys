#pragma once

#include "ofMain.h"
#include "ofxXmlGui.h"
#include "Vision.h"

class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	
private:

	ofxXmlGui gui;
	
	// the camera
	Vision vision;
	
	// the image that 
	ofImage palette;
};
