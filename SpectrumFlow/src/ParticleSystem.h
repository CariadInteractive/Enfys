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
#include "Particle.h"


class ParticleSystem {
public:
	void setup();
	
	// spawns a particle at this position.
	void spawn(ofVec2f p, ofVec2f v);
	void setupGui(xmlgui::SimpleGui &gui);
	void update(ofxCvOpticalFlowLK &flow, float volume);
	void draw();
	list<Particle> particles;
	int MAX_NUM_PARTICLES;
	float sensitivity;
	ofVboMesh vbo;
	float volume;
	ofImage circle;
	float lastFrameTime;
};
