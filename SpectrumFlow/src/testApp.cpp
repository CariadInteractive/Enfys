#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){
	vision.setup();
	palette.loadImage("palette.png");

	ofSetFrameRate(60);
	ofSetVerticalSync(true);

}

//--------------------------------------------------------------
void testApp::update(){
	vision.update();
}



//--------------------------------------------------------------
void testApp::draw(){
	const float paletteWidth = 20;
	
	
	ofBackground(0);
	ofSetColor(255);
	vision.draw();

	palette.draw(ofGetWidth(), 0, -paletteWidth, ofGetHeight());
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='f') {
		ofToggleFullscreen();
	}
}
