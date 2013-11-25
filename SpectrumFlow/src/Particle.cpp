/**
 *  Particle.cpp
 *
 *  Created by Marek Bereza on 25/11/2013.
 */

#include "Particle.h"
#include "constants.h"

Palette Particle::palette;

int Particle::MAX_AGE = 300;
int Particle::MAX_SPEED = 5;
float Particle::DAMPING = 0.005;
float Particle::DAMPING_COEFFICIENT = 1;
float Particle::RADIUS = 5;
float Particle::MIN_RADIUS = 5;
float Particle::MAX_RADIUS = 30;


ofImage Particle::circle;

void Particle::loadPalette() {
	palette.loadPaletteImage("palette.png");
}




void Particle::setup(ofVec2f pos, ofVec2f vel) {
	
	if(circle.getWidth()==0) {
		circle.loadImage("circle.png");
		circle.setAnchorPercent(0.5, 0.5);
	}
	
	this->pos = pos;
	this->vel = vel;
	dead = false;
	age = 0;
	color = palette.lookupColor(pos.y/HEIGHT);
}



void Particle::update() {
	pos += vel;
	age++;
	vel *= DAMPING_COEFFICIENT;
	if(age>MAX_AGE) dead = true;
	// kill myself if I'm off the screen.
	float radiusOfLargestParticle = 20; // arbitary at the mo, maybe it doesn't matter
	if(pos.x<-radiusOfLargestParticle || pos.y<-radiusOfLargestParticle
	   || pos.x+radiusOfLargestParticle> WIDTH ||
	   pos.y+radiusOfLargestParticle>HEIGHT
	   ) {
		dead = true;
	}
	
	
}

bool Particle::isDead() {
	return dead;
}


void Particle::draw() {
	// fade out the particle after it has become middle-aged
	color.a = ofMap(age, MAX_AGE/2, MAX_AGE, 255, 0, true);
	ofSetColor(color);
	//circle.draw(pos, 5, 5);
	ofCircle(pos, RADIUS);
}

