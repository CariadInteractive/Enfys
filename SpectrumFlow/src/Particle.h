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
	void setup(ofVec2f pos, ofVec2f vel);
	void update();
	void draw();
	
	bool isDead();
	
	int age;
	
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
	
	
	// this gets changed by the volume
	static float RADIUS;
	
	static float MIN_RADIUS;
	static float MAX_RADIUS;
	
	static ofImage circle;
	
	// END: CONSTANTS
	////////////////////////////////////////////////////////////
	
	
	
private:
	
	
	// each particle's colour is constant
	ofColor color;
	
	ofVec2f pos;
	ofVec2f vel;
	bool dead;
	
};