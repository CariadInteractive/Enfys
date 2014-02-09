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
 *  Particle.h, created by Marek Bereza on 25/11/2013.
 */

#pragma once
#include "ofMain.h"

#include "Palette.h"

class Particle {
public:
	Particle();
	~Particle();
	
	void setup(const ofVec2f &pos, const ofVec2f &vel, float volume);
	
	// delta is normalized frame duration
	void update(const float &delta);
	void draw();
	
	// call this to add a quad to a vbo instead of
	// drawing immediately with draw()
	void addToVbo(ofVboMesh &vbo);
	
	
	bool isDead();
	
	float age;
	
	float radius;
	
	// this is for loading the image that
	// holds the colour palette.
	static void loadPalette();
	static Palette palette;
	
	////////////////////////////////////////////////////////////
	// BEGIN: CONSTANTS
	
	// how old a particle can get before it dies
	static int MAX_AGE;
	
	// how far it can move in a frame
	static int MAX_SPEED;
	
	// how much to slow the velocity by each frame (like friction)
	static float DAMPING;
	
	static float DAMPING_COEFFICIENT;
	
	
	static int count;
	
	static float MIN_RADIUS;
	static float MAX_RADIUS;
	static ofVec2f gravity;
	
	
	// END: CONSTANTS
	////////////////////////////////////////////////////////////
	ofVec3f points[5];
	
	vector<ofVec2f> texCoords;
private:
	
	
	// each particle's colour is constant
	ofFloatColor color;
	vector<ofFloatColor> colors;
	ofVec2f pos;
	ofVec2f vel;
	bool dead;
	
};