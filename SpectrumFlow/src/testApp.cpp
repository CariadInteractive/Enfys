#include "testApp.h"
#include "constants.h"

// NOTE!! Do not use ofGetWidth() and ofGetHeight() - in order for the screen centring thing
// to work (i.e. the letterbox when you go fullscreen) you need to use WIDTH and HEIGHT
// as defined in constants.h

//--------------------------------------------------------------
void testApp::setup(){
	vision.setup();
	Particle::loadPalette();


	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	centerer.setup(WIDTH, HEIGHT);
	
	micInputGain = 0.75;
	volume = 0;
	drawOpticalFlow = false;
	

	
	setupGui();

	
	ofSoundStreamSetup(0, 1, this, 44100, 256, 1);
}


void testApp::setupGui() {
	
	gui.addTitle("Audio");
	gui.addSlider("mic input gain", micInputGain, 0, 5);
	gui.addMeter("mic volume", volume)->vertical = false;
	
	gui.addTitle("Computer Vision");
	gui.addToggle("draw optical flow", drawOpticalFlow);
	vision.setupGui(gui);
	particles.setupGui(gui);

	gui.loadSettings("settings.xml");
	gui.setEnabled(false);
}

//--------------------------------------------------------------
void testApp::update(){
	vision.update();
	particles.update(vision.getOpticalFlow());
}


void testApp::audioIn( float * input, int bufferSize, int nChannels ) {
	static float rawVolume = 0;
	for(int i = 0; i < bufferSize*nChannels; i++) {
		float inp = ABS(input[i]);
		if(inp>rawVolume) {
			rawVolume = inp;
		} else {
			rawVolume *= 0.9999;
		}
		if(rawVolume>1) rawVolume = 1;
	}
	volume = rawVolume * micInputGain;
	if(volume>1) volume = 1;
}

//--------------------------------------------------------------
void testApp::draw(){
	const float paletteWidth = 20;
	
	centerer.begin();
	ofBackground(0);
	ofSetColor(255);
	vision.draw(drawOpticalFlow);

	Particle::palette.draw(WIDTH, 0, -paletteWidth, HEIGHT);
	particles.draw();
	centerer.end();
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='f') {
		ofToggleFullscreen();
	}
	if(key==' ') {
		gui.toggle();
	}
}
