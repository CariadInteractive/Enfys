#include "testApp.h"

using namespace ofxCv;
using namespace cv;

void testApp::setup() {
	cam.initGrabber(640, 480);
//	contourFinder.setMinAreaRadius(10);
//	contourFinder.setMaxAreaRadius(200);
//	trackingColorMode = TRACK_COLOR_HSV;
    
    dinFont.loadFont("DIN.otf", 24);
    
    currentColour = ofColor::red;
    
    targetColours.push_back(ofColor::red);
    targetColours.push_back(ofColor::orange);
    targetColours.push_back(ofColor::yellow);
    targetColours.push_back(ofColor::green);
    targetColours.push_back(ofColor::blue);
    targetColours.push_back(ofColor::indigo);
    targetColours.push_back(ofColor::violet);
    
    previousMousePosition = ofVec3f(ofGetWidth()/2.f, ofGetHeight()/2.f, 0.f);
    
    mouseVelocity = ofVec3f(0.f,0.f,0.f);
    
    mouseLine.setFeather(2);
    //mouseLine.enableFeatherAtCore();
    mouseLine.setJointType(OFX_FATLINE_JOINT_BEVEL);
    mouseLine.setCapType(OFX_FATLINE_CAP_ROUND);
}

void testApp::update() {
	cam.update();
//	if(cam.isFrameNew()) {
//		threshold = ofMap(mouseX, 0, ofGetWidth(), 0, 255);
//		contourFinder.setThreshold(threshold);
//		contourFinder.findContours(cam);
//	}
    
	ofColor cameraCentreColour = cam.getPixelsRef().getColor(cam.getWidth()/2.f, cam.getHeight()/2.f);
	//contourFinder.setTargetColor(targetColor, trackingColorMode);
    currentColour = cameraCentreColour;
    
    float absHueDifference = 1000.f;
    ofColor heroColour = ofColor::black;
    
    for(int i=0; i < targetColours.size(); i++){
        float currentHueDifference = abs(cameraCentreColour.getHue()-targetColours[i].getHue());
        
        if(currentHueDifference < absHueDifference){
            absHueDifference = currentHueDifference;
            heroColour = targetColours[i];
        }
    }
    
    if(ofGetKeyPressed()){ //if you press the key you get the snapped colour
        currentColour = heroColour;
    }
}

void testApp::draw() {
    ofBackground(ofColor::white);

    //video and contour finder
	ofSetColor(255);
	cam.draw(0, 0, ofGetWidth(),ofGetHeight());
//	contourFinder.draw();
    
    
    //line
    if(mouseLine.size() > 0){
        //draw em if you got em
        mouseLine.draw();
        //mouseLine.drawDebug();
    }

    
//	drawHighlightString(ofToString((int) ofGetFrameRate()) + " fps", 10, 20);
//	drawHighlightString(ofToString((int) threshold) + " threshold", 10, 40);
//	drawHighlightString(trackingColorMode == TRACK_COLOR_HSV ? "HSV tracking" : "RGB tracking", 10, 60);
    
    ofSetColor(ofColor::black);
    dinFont.drawString("Enfys Prototype:\nMouse Camera Colour Tracer",50, 200);
    
	ofTranslate(8, 8);
	ofFill();
	ofSetColor(0);
	ofRect(-3, -3, 64+6, 64+6);
	ofSetColor(currentColour);
	ofRect(0, 0, 64, 64);
}

void testApp::mouseMoved(int x, int y){
}

void testApp::mousePressed(int x, int y, int button) {
    mouseLine.clear();
    
    ofVec3f mousePosition = ofVec3f(x,y,0.f);
    ofFloatColor mouseColour = ofFloatColor((float)currentColour.r/255.f, (float)currentColour.g/255.f, (float)currentColour.b/255.f);
    double mouseWeight = 1;//mouseVelocity.length();
    
    mouseLine.add(mousePosition, mouseColour, mouseWeight);
}

void testApp::mouseDragged(int x, int y, int button){
    ofVec3f mousePosition = ofVec3f(x,y,0.f);
    
    mouseVelocity = mousePosition - previousMousePosition;
    
    ofFloatColor mouseColour = ofFloatColor((float)currentColour.r/255.f, (float)currentColour.g/255.f, (float)currentColour.b/255.f);
    double mouseWeight = mouseVelocity.length()/6.f;
    
    mouseLine.add(mousePosition, mouseColour, mouseWeight);
    
    previousMousePosition = mousePosition;
}

void testApp::keyPressed(int key) {
//	if(key == 'h') {
//		trackingColorMode = TRACK_COLOR_HSV;
//	}
//	if(key == 'r') {
//		trackingColorMode = TRACK_COLOR_RGB;
//	}
//	contourFinder.setTargetColor(targetColor, trackingColorMode);
}