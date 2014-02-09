/**
 *  ParticleSystem.cpp
 *
 *  Created by Marek Bereza on 25/11/2013.
 */

#include "ParticleSystem.h"
#include "constants.h"


void ParticleSystem::setup() {
	circle.loadImage("circle.png");
	lastFrameTime = ofGetElapsedTimef();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleSystem::spawn(ofVec2f p, ofVec2f v) {
	
	
	ofVec2f vel = v.normalize();
	vel *= ofRandom(Particle::MAX_SPEED*0.4, Particle::MAX_SPEED);
	
	
	// we want to jitter the location of the particle
	// slightly because the optical flow is quantized
	ofVec2f jitter(ofRandom(-7, 7), ofRandom(-7, 7));
	particles.push_back(Particle());
	particles.back().setup(p+jitter, vel, volume);

	
	while(Particle::count>MAX_NUM_PARTICLES) {

		particles.pop_front();
	}

}

void ParticleSystem::setupGui(xmlgui::SimpleGui &gui) {
	MAX_NUM_PARTICLES = 5000;
	sensitivity = 0.5;
	gui.addTitle("Particles");
	gui.addSlider("max num particles", MAX_NUM_PARTICLES, 1000, 40000);
	gui.addSlider("sensitivity", sensitivity, 0.0f,20.f);
	gui.addSlider("max age (in frames)", Particle::MAX_AGE, 0, 1000);
	gui.addSlider("particle speed", Particle::MAX_SPEED, 0.1, 20);
	gui.addSlider("movement damping", Particle::DAMPING, 3, 0.7);
	gui.addSlider("min radius", Particle::MIN_RADIUS, 1, 100);
	gui.addSlider("max radius", Particle::MAX_RADIUS, 1, 200);
	gui.addSlider2D("gravity", Particle::gravity, -10, 10, -10, 10);
	
}


void ParticleSystem::update(ofxCvOpticalFlowLK &flow, float volume) {
	this->volume = volume;
	float step = 5;
	float dx = 0, dy = 0;
	
	
	// this turns the range [3-0.7] to a range of somethign like [0.9-0.999999]
	// (some sort of log mapping.
	Particle::DAMPING_COEFFICIENT = 1 - powf(10.f, -Particle::DAMPING);
	
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
				spawn(ofVec2f(i, j)*visionToScreenScale, ofVec2f(dx, dy));
			}
		}
	}
	
	// rather than having a delta in seconds, this is a delta normalized
	// to the desired frame duration
	float delta = ofGetElapsedTimef() - lastFrameTime;
	delta *= 30.f;
	lastFrameTime = ofGetElapsedTimef();
	
//	for(int i = 0; i < particles.size(); i++) {
	for(list<Particle>::iterator it = particles.begin(); it != particles.end();) {
		(*it).update(delta);
		if((*it).isDead()) {
			it = particles.erase(it);
		} else {
			it++;
		}
	}
}

void ParticleSystem::updateWithContourFinder(ofxCv::ContourFinder &contourFinder, float volume) {
	this->volume = volume;
	
	
	// this turns the range [3-0.7] to a range of somethign like [0.9-0.999999]
	// (some sort of log mapping.
	Particle::DAMPING_COEFFICIENT = 1 - powf(10.f, -Particle::DAMPING);
	
	ofVec2f visionToScreenScale(
                                (float)WIDTH/VISION_WIDTH,
                                (float)HEIGHT/VISION_HEIGHT
                                );

    float sens = sensitivity;
    
    for(int i = 0; i < contourFinder.size(); i++) {
        ofPoint centre = ofxCv::toOf(contourFinder.getCenter(i));
        ofVec2f velocity = ofxCv::toOf(contourFinder.getVelocity(i));
        int label = contourFinder.getLabel(i);
        int age = contourFinder.getTracker().getAge(label);
        
        float speed = velocity.length();
        //cout << "Speed of " << i << "is " << velocity.length() << endl;
        
        if(speed > sens){
            spawn(ofVec2f(centre.x, centre.y)*visionToScreenScale, velocity);
        }
    }
	
	// rather than having a delta in seconds, this is a delta normalized
	// to the desired frame duration
	float delta = ofGetElapsedTimef() - lastFrameTime;
	delta *= 30.f;
	lastFrameTime = ofGetElapsedTimef();
	
    //	for(int i = 0; i < particles.size(); i++) {
	for(list<Particle>::iterator it = particles.begin(); it != particles.end();) {
		(*it).update(delta);
		if((*it).isDead()) {
			it = particles.erase(it);
		} else {
			it++;
		}
	}
}


void ParticleSystem::draw() {
	vbo.clear();
	vbo.setMode(OF_PRIMITIVE_TRIANGLES);
	for(list<Particle>::iterator it = particles.begin(); it != particles.end(); it++) {
		(*it).addToVbo(vbo);
//		particles[i].draw();
	}
	

	circle.bind();
	vbo.draw();
	circle.unbind();
	
}