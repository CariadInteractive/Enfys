/**
 *  Palette.cpp
 *
 *  Created by Marek Bereza on 25/11/2013.
 */

#include "Palette.h"

// to find a colour, pass in a number from 0 to 1
ofColor Palette::lookupColor(float pos) {
	int index = pos * colorLookup.size();
	if(index>=0 && index<colorLookup.size()) {
		return colorLookup[index];
	} else {
		ofLogError() << "Colour lookup out of bounds (" << pos << ") !!";
		return ofColor(255, 255, 255);
	}
}


void Palette::loadPaletteImage(string path) {
	
	colorLookup.clear();
	
	image.loadImage(path);
	unsigned char *pix = image.getPixels();
	float w = image.getWidth();
	float h = image.getHeight();
	int n = image.getPixelsRef().getNumChannels();
	if(n<3) {
		ofLogError() << "Palette image doesn't have enough colour channels (it's got " << n		<< ")!!";
		return;
	}
	for(int i = 0; i < h; i++) {
		int pos = w * i * n;
		colorLookup.push_back(ofColor(pix[pos], pix[pos+1], pix[pos+2]));
	}
}


void Palette::draw(float x, float y, float w, float h) {
	image.draw(x, y, w, h);
}
