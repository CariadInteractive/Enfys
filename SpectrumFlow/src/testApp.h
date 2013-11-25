#pragma once

#include "ofMain.h"
#include "ofxXmlGui.h"
#include "Vision.h"
#include "Centerer.h"
#include "ParticleSystem.h"

class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void audioIn( float * input, int bufferSize, int nChannels );

private:

	xmlgui::SimpleGui gui;
	
	void setupGui();
	
	// the camera
	Vision vision;
	
	// the image that 
	ofImage palette;
	
	// makes the picture sit in the centre.
	Centerer centerer;
	
	float micInputGain;
	
	// this is the volume of sound
	// coming from the microphone
	float volume;

	ParticleSystem particles;
	
	
	// whether to draw optical flow
	bool drawOpticalFlow;
};
