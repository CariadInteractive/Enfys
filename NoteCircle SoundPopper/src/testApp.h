#ifndef _TEST_APP
#define _TEST_APP



#include "ofMain.h"
#include "ofxAubioAnalyzer.h"

class testApp : public ofSimpleApp{
	
	public:
				
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();		
		void audioReceived		(float * input, int bufferSize, int nChannels);
    string noteFromIndex(int index);
    string justNoteFromIndex(int index);
    string noteFromFrequency(float frequency);
    string midiToString(int aMidiNote);
    int snapFreqToMIDI(float frequency);
    int circleIndexToFillFromMidiNoteIndexed(int index); //given 0..11, give back 0..6, picking one of 7 colours for circles....
    ofColor colourForNoteIndex(int index); //pick a colour on one of 7 note indexes
    string stringForNoteIndex(int index); //not letter based on 0..7
		
    float * left;
    float * right;

    ofxAubioAnalyzer AA;

    ofTrueTypeFont dinFont;
    
//    vector <string> noteStrings;
    
    vector <float> midiNotes;
    vector <string> midiNames;
    vector <float> circleFillValues;
	
};

#endif	

