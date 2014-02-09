/**
 *  Particle.cpp
 *
 *  Created by Marek Bereza on 25/11/2013.
 */

#include "Particle.h"
#include "constants.h"

Palette Particle::palette;
int Particle::count = 0;

int Particle::MAX_AGE = 300;
int Particle::MAX_SPEED = 5;
float Particle::DAMPING = 0.005;
float Particle::DAMPING_COEFFICIENT = 1;
float Particle::MIN_RADIUS = 5;
float Particle::MAX_RADIUS = 30;
ofVec2f Particle::gravity;


void Particle::loadPalette() {
	palette.loadPaletteImage("palette.png");
}
Particle::Particle() {
	count++;
}

Particle::~Particle() {
	count--;
}



void Particle::setup(const ofVec2f &pos, const ofVec2f &vel, float volume) {
	
	this->radius = ofMap(volume, 0, 1, MIN_RADIUS, MAX_RADIUS, true);
	this->pos = pos;
	this->vel = vel;
	dead = false;
	age = 0;
	color = palette.lookupFloatColor(pos.y/HEIGHT);
	for(int i =0 ; i < 6; i++) colors.push_back(color);
	
	float w = 256;
	float h = 256;
	
	texCoords.push_back(ofVec2f(0, 0));
	texCoords.push_back(ofVec2f(w, 0));
	texCoords.push_back(ofVec2f(w, h));

	texCoords.push_back(ofVec2f(w, h));
	texCoords.push_back(ofVec2f(0, h));
	texCoords.push_back(ofVec2f(0, 0));


	
	
	
}



void Particle::update(const float &delta) {
	pos += vel*delta;
	pos += gravity*delta;
	age+=delta;
	vel *= DAMPING_COEFFICIENT;
	if(age>MAX_AGE) dead = true;
	// kill myself if I'm off the screen.
	float radiusOfLargestParticle = radius; // arbitary at the mo, maybe it doesn't matter
	if(pos.x<-radiusOfLargestParticle || pos.y<radiusOfLargestParticle
	   || pos.x-radiusOfLargestParticle> WIDTH ||
	   pos.y-radiusOfLargestParticle>HEIGHT
	   ) {
		dead = true;
	}
	
	
}

bool Particle::isDead() {
	return dead;
}


void Particle::draw() {
	// fade out the particle after it has become middle-aged
	
	ofSetColor(color);
	ofCircle(pos, radius);
}


void Particle::addToVbo(ofVboMesh &vbo) {
	ofRectangle r;

	color.a = ofMap(age, MAX_AGE/2, MAX_AGE, 1, 0, true);
	color.a = powf(color.a, 0.333);	
	float rad = color.a * radius;
	r.setFromCenter(pos.x, pos.y, rad, rad);
	
	
	points[0] = r.getTopLeft();
	points[1] = r.getTopRight();
	points[2] = r.getBottomRight();
	points[3] = r.getBottomLeft();
	points[4] = points[0];
	vbo.addVertices(points, 3);
	vbo.addVertices(&points[2], 3);
	vbo.addTexCoords(texCoords);
	/*
	
	vbo.addVertex(r.getTopLeft());
	vbo.addVertex(r.getTopRight());
	vbo.addVertex(r.getBottomRight());
	
	vbo.addVertex(r.getBottomRight());
	vbo.addVertex(r.getBottomLeft());
	vbo.addVertex(r.getTopLeft());
	*/
	for(int i = 0; i < colors.size(); i++) {
		colors[i].a = color.a;
	}
	vbo.addColors(colors);	
}
