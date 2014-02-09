/**
 *  Vision.cpp
 *
 *  Created by Marek Bereza on 25/11/2013.
 */

#include "Vision.h"
#include "constants.h"

void Vision::setup() {
	grabber.initGrabber(VISION_WIDTH, VISION_HEIGHT);
	
	frame.allocate(VISION_WIDTH, VISION_HEIGHT);
	grey.allocate(VISION_WIDTH, VISION_HEIGHT);
	
	greyCurr.allocate(VISION_WIDTH/2, VISION_HEIGHT/2);
	greyPrev.allocate(VISION_WIDTH/2, VISION_HEIGHT/2);
	
	flow.allocate(VISION_WIDTH/2, VISION_HEIGHT/2);
	flowSize = 3;
	flipHorizontal = true;
    
    contourFinder.setMinAreaRadius(10);
	contourFinder.setMaxAreaRadius(200);
	trackingColorMode = ofxCv::TRACK_COLOR_HSV;
    threshold = 10;
    pickColour = false;
    drawTracker = false;
}

void Vision::setupGui(xmlgui::SimpleGui &gui) {
    gui.addToggle("draw tracker", drawTracker);
	gui.addToggle("flip horizontal", flipHorizontal);
    gui.addColorPicker("tracking colour", pickedColour);
    gui.addToggle("pick colour", pickColour);
    gui.addSlider("tracking threshold", threshold, 0,255);
}
void Vision::update() {
    if(ofGetMousePressed() && pickColour){
        int scaledMouseX = ((float)ofGetMouseX()/(float)WIDTH)*VISION_WIDTH;
        int scaledMouseY = ((float)ofGetMouseY()/(float)HEIGHT)*VISION_HEIGHT;
        
        pickedColour = grabber.getPixelsRef().getColor(scaledMouseX, scaledMouseY);
    }

    contourFinder.setTargetColor(pickedColour);
    
	grabber.update();
	if(grabber.isFrameNew()) {
        trackColours();
		computeOpticalFlow();
	}
}

void Vision::trackColours(){
    //threshold = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 255);
    contourFinder.setThreshold(threshold);
    contourFinder.findContours(grabber);
}

void Vision::computeOpticalFlow() {
	frame.setFromPixels(grabber.getPixels(), grabber.getWidth(), grabber.getHeight());
	if(flipHorizontal) frame.mirror(false, true);
	grey = frame;
	greyCurr.scaleIntoMe(grey);
	
	
	flow.calc(greyPrev, greyCurr, flowSize);
	flow.blur(2);
	greyPrev = greyCurr;
}


void Vision::draw() {
	frame.draw(0, 0, WIDTH, HEIGHT);
	if(drawTracker) {
        ofPushStyle();
        ofPushMatrix();
        ofSetColor(255);
        grabber.draw(0, 0);
        contourFinder.draw();
        ofDrawBitmapStringHighlight(ofToString((int) ofGetFrameRate()) + " fps", ofGetWidth()/2.f, 20);
        ofDrawBitmapStringHighlight(ofToString((int) threshold) + " threshold", ofGetWidth()/2.f, 40);
        ofDrawBitmapStringHighlight(trackingColorMode == ofxCv::TRACK_COLOR_HSV ? "HSV tracking" : "RGB tracking", ofGetWidth()/2.f, 60);
        
        ofTranslate(ofGetWidth()/2.f, 75);
        ofFill();
        ofSetColor(0);
        ofRect(-3, -3, 64+6, 64+6);
        //ofSetColor(targetColour);
        ofSetColor(pickedColour);
        ofRect(0, 0, 64, 64);
        ofPopStyle();
        ofPopMatrix();
	}
}

ofxCvOpticalFlowLK &Vision::getOpticalFlow() {
	return flow;
}

ofxCv::ContourFinder &Vision::getContourFinder(){
    return contourFinder;
}

