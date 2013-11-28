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
 *  Description: Really simple class for looking up colours from a PNG.
 *				 The colours must be vertically distributed in the png (i.e.
				 you'll use a tall narrow image, not a short wide one.)
 *  Palette.h, created by Marek Bereza on 25/11/2013.
 */

#pragma once

#include "ofMain.h"


class Palette {
public:
	

	// to find a colour, pass in a number from 0 to 1
	ofColor lookupColor(float pos);
	ofFloatColor lookupFloatColor(float pos); // float colour version
	void loadPaletteImage(string path);
	
	void draw(float x, float y, float w, float h);
	
private:
	ofImage image;
	vector<ofColor> colorLookup;
	
};