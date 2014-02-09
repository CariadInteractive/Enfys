#include "testApp.h"
#include "stdio.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofBackground(255,255,255);
	
	// 0 output channels,
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	
	//setup of sound input
	ofSoundStreamSetup(0, 2, this, 44100, 256, 4);
	left = new float[256];
	right = new float[256];
	
	AA.setup();
	
	dinFont.loadFont("DIN.otf", 24);
    
    float a = 440.f; // a is 440 hz...
    int currentNoteIndex = 0;
    int currentOctave = 1;
    
    for (int x = 0; x < 127; ++x)
    {
        //http://subsynth.sourceforge.net/midinote2freq.html
        midiNotes.push_back((a / 32.f) * (2 ^ ((x - 9) / 12)));
        
        string currentMidiNoteAsString;
        ostringstream convert;   // stream used for the conversion
        
        convert << noteFromIndex(currentNoteIndex) << currentOctave;
        
        currentMidiNoteAsString = convert.str(); // set 'currentOctaveAsString' to the contents of the stream
        
        midiNames.push_back(currentMidiNoteAsString);
        
        currentNoteIndex++;
        
        if(currentNoteIndex > 11){ //12 notes in midi index of notes
            currentNoteIndex = 0;
            currentOctave++;
        }
    }
    
    
//    //populate the noteStrings...
//	noteStrings.push_back("C");
//    noteStrings.push_back("C#");
//    noteStrings.push_back("D");
//    noteStrings.push_back("D#");
//    noteStrings.push_back("E");
//    noteStrings.push_back("F");
//    noteStrings.push_back("F#");
//    noteStrings.push_back("G");
//    noteStrings.push_back("G#");
//    noteStrings.push_back("A");
//    noteStrings.push_back("A#");
//    noteStrings.push_back("B");
    
    circleFillValues.resize(7, 0.f); //7 circles, all with a value of 0.f
}

string testApp::noteFromIndex(int index){
    string result = "C";
    
    switch  (index){
        case 0 :
        {
            result = "C";
        }
            break;
        case 1 :
        {
            result = "C#";
        }
            break;
        case 2 :
        {
            result = "D";
        }
            break;
        case 3 :
        {
            result = "D#";
        }
            break;
        case 4 :
        {
            result = "E";
        }
            break;
        case 5 :
        {
            result = "F";
        }
            break;
        case 6 :
        {
            result = "F#";
        }
            break;
        case 7 :
        {
            result = "G";
        }
            break;
        case 8 :
        {
            result = "G#";
        }
            break;
        case 9 :
        {
            result = "A";
        }
            break;
        case 10:
        {
            result = "A#";
        }
            break;
        case 11:
        {
            result = "B";
        }
            break;
    }
    
    return result;
}

string testApp::justNoteFromIndex(int index){
    string result = "C";
    
    switch  (index){
        case 0 :
        {
            result = "C";
        }
            break;
        case 1 :
        {
            result = "C";
        }
            break;
        case 2 :
        {
            result = "D";
        }
            break;
        case 3 :
        {
            result = "D";
        }
            break;
        case 4 :
        {
            result = "E";
        }
            break;
        case 5 :
        {
            result = "F";
        }
            break;
        case 6 :
        {
            result = "F";
        }
            break;
        case 7 :
        {
            result = "G";
        }
            break;
        case 8 :
        {
            result = "G";
        }
            break;
        case 9 :
        {
            result = "A";
        }
            break;
        case 10:
        {
            result = "A";
        }
            break;
        case 11:
        {
            result = "B";
        }
            break;
    }
    
    return result;
}

int testApp::circleIndexToFillFromMidiNoteIndexed(int index){
    int result = 0;
    
    switch(index){
        case 0 :
        {
            result = 0;
        }
            break;
        case 1 :
        {
            result = 0;
        }
            break;
        case 2 :
        {
            result = 1;
        }
            break;
        case 3 :
        {
            result = 1;
        }
            break;
        case 4 :
        {
            result = 2;
        }
            break;
        case 5 :
        {
            result = 3;
        }
            break;
        case 6 :
        {
            result = 3;
        }
            break;
        case 7 :
        {
            result = 4;
        }
            break;
        case 8 :
        {
            result = 4;
        }
            break;
        case 9 :
        {
            result = 5;
        }
            break;
        case 10:
        {
            result = 5;
        }
            break;
        case 11:
        {
            result = 6;
        }
            break;
    }
    
    return result;
}

string testApp::stringForNoteIndex(int index){
    string result = "C";
    
    switch  (index){
        case 0 :
        {
            result = "C";
        }
            break;
        case 1 :
        {
           result = "D";
        }
            break;
        case 2 :
        {
            result = "E";
        }
            break;
        case 3 :
        {
            result = "F";
        }
            break;
        case 4 :
        {
            result = "G";
        }
            break;
        case 5 :
        {
            result = "A";
        }
            break;
        case 6 :
        {
            result = "B";
        }
            break;
    }

    return result;
}

ofColor testApp::colourForNoteIndex(int index){
    ofColor result = ofColor::red;
    
    switch  (index){
        case 0 :
        {
            result = ofColor::red;
        }
            break;
        case 1 :
        {
            result = ofColor::orange;
        }
            break;
        case 2 :
        {
            result = ofColor::yellow;
        }
            break;
        case 3 :
        {
            result = ofColor::green;
        }
            break;
        case 4 :
        {
            result = ofColor::blue;
        }
            break;
        case 5 :
        {
            result = ofColor::indigo;
        }
            break;
        case 6 :
        {
            result = ofColor::violet;
        }
            break;
    }
    
    return result;
}

string testApp::noteFromFrequency(float frequency){
    string note = "C1";
    int midiIndex = 0;
    
    //stupid.....but effective....
    for(int i=0; i < midiNotes.size(); i++){
        midiIndex = i;
        if(frequency < midiNotes[i]){
            cout << "Index is" << midiIndex << endl;
            break;
        }
    }
    
    note = midiNames[midiIndex];
    
    return note;
}

int testApp::snapFreqToMIDI(float frequency){
    float referenceA = 440;
    int midiNote = (12*(log10(frequency/referenceA)/log10(2)) + 57) + 0.5;
    return midiNote;
}

string testApp::midiToString(int aMidiNote){
    return midiNames[aMidiNote];
    //return noteStrings[aMidiNote%12];
}


//--------------------------------------------------------------
void testApp::update(){
    
    int currentCircleIndex = circleIndexToFillFromMidiNoteIndexed(snapFreqToMIDI(AA.pitch)%12);
    circleFillValues[currentCircleIndex] += AA.amplitude/100.f;
    
    for(int i=0; i < circleFillValues.size(); i++){
        if(circleFillValues[i] > 1.f){
            circleFillValues[i] = 0.f;
        }
    }
}


//--------------------------------------------------------------
void testApp::draw(){
	
//    // draw the left:
//	ofSetHexColor(0x333333);
//	ofRect(0,0,256,400);
//	ofSetHexColor(0xFFFFFF);
//	for (int i = 0; i < 256; i++){
//		ofLine(i,200,i,200+left[i]*400);
//	}
    
    ofSetColor(ofColor::black);
    dinFont.drawString("Enfys Prototype: Note Circle Sound Popper",50, 200);
	
	ofSetHexColor(0x000000);
	
	dinFont.drawString( "Pitch: " + ofToString((int)AA.pitch) +
                       "\nAmplitude: " + ofToString(AA.amplitude,3) +
                       "\nOctaved note is: " + ofToString(midiToString(snapFreqToMIDI(AA.pitch)),3) +
                       "\nJust sharpend note: " + noteFromIndex(snapFreqToMIDI(AA.pitch)%12) +
                       "\nJust note: " + justNoteFromIndex(snapFreqToMIDI(AA.pitch)%12)
                       ,50,500);
	
    float maxCircleRadius = (ofGetWidth()/circleFillValues.size())/2.f;
    
    for(int i=0; i < circleFillValues.size(); i++){
        float circleXCentre = (i*maxCircleRadius*2.f)+maxCircleRadius;
        float circleYCentre = ofGetHeight()/2.f;
        
        ofSetColor(colourForNoteIndex(i));
        ofCircle(circleXCentre, circleYCentre, maxCircleRadius*circleFillValues[i]);
        
        ofSetColor(ofColor::black);
        
        string noteString = stringForNoteIndex(i);
        
        float widthOfNoteStringInUsingFont = dinFont.stringWidth(noteString);
        float heightOfNoteStringInUsingFont	= dinFont.stringHeight(noteString);
        
        dinFont.drawString(stringForNoteIndex(i), circleXCentre-widthOfNoteStringInUsingFont/2.f, circleYCentre+heightOfNoteStringInUsingFont/2.f);
    }
}


//--------------------------------------------------------------
void testApp::audioReceived (float * input, int bufferSize, int nChannels){
	
	
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		left[i] = input[i*2];
		right[i] = input[i*2+1];
	}
    
	AA.processAudio(left, bufferSize);
}



//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}


void testApp::keyReleased(int key){
	
}

void testApp::mouseMoved(int x, int y ){
	
}

void testApp::mouseDragged(int x, int y, int button){
	
}

void testApp::mousePressed(int x, int y, int button){
	
}

void testApp::mouseReleased(){
	
}

