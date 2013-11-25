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
 *  ParticleSystem.h, created by Marek Bereza on 25/11/2013.
 */

#pragma once

#include "ofMain.h"
#include "ofxCvOpticalFlowLK.h"
#include "ofxXmlGui.h"
#include "Palette.h"

class Particle {
public:
	void setup(ofVec2f pos, ofVec2f vel);
	void update();
	void draw();
	
	bool isDead();
	
	// this is for loading the image that
	// holds the colour palette.
	static void loadPalette();
	static Palette palette;

	// each particle's colour is constant
	ofColor color;
	
private:
	
	
	
	ofVec2f pos;
	ofVec2f vel;
	bool dead;

};

class ParticleSystem {
public:
	
	// spawns a particle at this position.
	void spawn(ofVec2f p);
	void setupGui(xmlgui::SimpleGui &gui);
	void update(ofxCvOpticalFlowLK &flow);
	void draw();
	deque<Particle> particles;
	int MAX_NUM_PARTICLES;
	float sensitivity;
};
