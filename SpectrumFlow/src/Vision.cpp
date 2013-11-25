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
	greyCurr.allocate(VISION_WIDTH, VISION_HEIGHT);
	greyPrev.allocate(VISION_WIDTH, VISION_HEIGHT);
	
	flow.allocate(VISION_WIDTH, VISION_HEIGHT);
	flowSize = 3;
	flipHorizontal = true;
}



void Vision::setupGui(xmlgui::SimpleGui &gui) {
	gui.addToggle("flip horizontal", flipHorizontal);
}
void Vision::update() {
	grabber.update();
	if(grabber.isFrameNew()) {
		computeOpticalFlow();
	}
}

void Vision::computeOpticalFlow() {
	frame.setFromPixels(grabber.getPixels(), grabber.getWidth(), grabber.getHeight());
	if(flipHorizontal) frame.mirror(false, true);
	greyCurr = frame;
	
	flow.calc(greyPrev, greyCurr, flowSize);
	flow.blur(2);
	greyPrev = greyCurr;
}


void Vision::draw(bool debug) {
	frame.draw(0, 0, WIDTH, HEIGHT);
	if(debug) {
		flow.draw(0, 0, WIDTH, HEIGHT);
	}
}

ofxCvOpticalFlowLK &Vision::getOpticalFlow() {
	return flow;

}


