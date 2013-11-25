/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice, this list of
 *     conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of
 *     conditions and the following disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * Centerer.h
 *
 * Centers and scales opengl content within an area to fill
 * the screen. (letterbox)
 *
 * You set this up with your desired resolution, then you
 * do your drawing between begin() and end(). You also send
 * all your
 *
 * Created by Marek Bereza on 19/07/2011.
 * Updated by Marek Bereza on 25/11/2013.
 *
 */
#include "ofMain.h"

#pragma once

class Centerer {
public:
	
	void setup(float screenWidth, float screenHeight) {
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
		resize(ofGetWidth(), ofGetHeight());
		ofAddListener(ofEvents().windowResized, this, &Centerer::windowResized);
	}
	
	
	
	void windowResized(ofResizeEventArgs &args) {
		resize(args.width, args.height);
	}
	
	
	void resize(float width, float height) {
		
		fakeGameModeScale = (float)height/screenHeight;
		resizedScreenWidth = (float)width/fakeGameModeScale;
		moveRightBy = (resizedScreenWidth - screenWidth)/2;
	}
	
	
	void begin() {
		// do a fake OF_GAME_MODE - the real one locks up the computer when it crashes
		glPushMatrix();
		glScalef(fakeGameModeScale, fakeGameModeScale, fakeGameModeScale);
		glTranslatef(moveRightBy, 0, 0);
	}
	
	void end() {
		ofSetHexColor(0);
		// letterbox
		ofRect(-1000, 0, 1000, screenHeight);
		ofRect(screenWidth, 0, 1000, screenHeight);
		glPopMatrix();
	}
	
	
	void transformMouse(float &x, float &y) {
		x /= fakeGameModeScale;
		y /= fakeGameModeScale;
		x -= moveRightBy;
	}
	
	
	
	
private:
	float screenWidth;
	float screenHeight;
	float fakeGameModeScale;
	float resizedScreenWidth;
	float moveRightBy;
	
};
