/**
 *  ParticleSystem.cpp
 *
 *  Created by Marek Bereza on 25/11/2013.
 */

#include "ParticleSystem.h"
#include "constants.h"


Palette Particle::palette;

void Particle::loadPalette() {
	palette.loadPaletteImage("palette.png");
}




void Particle::setup(ofVec2f pos, ofVec2f vel) {
	this->pos = pos;
	this->vel = vel;
	dead = false;
	
	color = palette.lookupColor(pos.y/HEIGHT);
}



void Particle::update() {
	pos += vel;
	
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

	ofSetColor(color);
	ofCircle(pos, 5);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleSystem::spawn(ofVec2f p) {
	
	
	ofVec2f vel(ofRandom(2, 5), 0);
	vel.rotate(ofRandom(0, 360));
	
	particles.push_back(Particle());
	particles.back().setup(p, vel);
	while(particles.size()>MAX_NUM_PARTICLES) {
		particles.pop_front();
	}
}

void ParticleSystem::setupGui(xmlgui::SimpleGui &gui) {
	MAX_NUM_PARTICLES = 5000;
	sensitivity = 0.5;
	gui.addTitle("Particles");
	gui.addSlider("max num particles", MAX_NUM_PARTICLES, 1000, 10000);
	gui.addSlider("sensitivity", sensitivity);
}

void ParticleSystem::update(ofxCvOpticalFlowLK &flow) {
	float step = 5;
	float dx = 0, dy = 0;
	
	ofVec2f visionToScreenScale(
							(float)WIDTH/flow.getWidth(),
							(float)HEIGHT/flow.getHeight()
	);
	
	float sens = 10 + (1 - sensitivity)*15;
	sens = sens*sens;
	for(float i = 0; i < flow.getWidth(); i+=step) {
		for(float j = 0; j < flow.getHeight(); j+=step) {
			flow.forceAtPos(i, j, dx, dy);
			if(dx*dx + dy*dy>sens) {
				spawn(ofVec2f(i, j)*visionToScreenScale);
			}
		}
	}
	
	for(int i = 0; i < particles.size(); i++) {
		particles[i].update();
		if(particles[i].isDead()) {
			particles.erase(particles.begin() + i);
			i--;
		}
	}
}


void ParticleSystem::draw() {
	for(int i = 0; i < particles.size(); i++) {
		particles[i].draw();
	}
}