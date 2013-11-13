#include "Ripple.h"

void Ripple::setup(){
    leap.open();
    width = ofGetWidth() / 2;
    height = ofGetHeight() / 2;
    
    fbo.allocate(width, height);
    shader.load("shader");
    
    baseFreq = interpBaseFreq = 20;
    detune = 1;
    freq[0] = freq[1] = baseFreq;
    
    ofxSuperColliderServer::init();
    
    synth = new ofxSCSynth("ripple");
    synth->create();
    
    showGui = false;
    ofHideCursor();
    gui.setup();
    gui.add(waveLength.setup("Wave Length", 200, 0, 800));
    gui.add(waveSpeed.setup("Wave Speed", 100, 0, 200));
    gui.add(interp.setup("Interpolate", 100, 1, 800));
    gui.add(detuneScale.setup("Detune Scale", 10, 1, 20));
    gui.add(showLog.setup("Show Log", false));
}

void Ripple::update(){
    hands = leap.getLeapHands();
    if( leap.isFrameNew() && hands.size() ){
        palmNormals.clear();
        for(int i = 0; i < hands.size(); i++){
            ofVec3f norm = ofVec3f(hands[i].palmNormal().x, hands[i].palmNormal().y, hands[i].palmNormal().z);
            palmNormals.push_back(norm);
        }
    }
}

void Ripple::draw(){
    ofSetColor(255);
    float resolution[] = {width, height};
    float time = ofGetElapsedTimef();
    if (hands.size() > 0) {
        baseFreq = hands[0].palmPosition().y / 6.0;
        detune = baseFreq * palmNormals[0].x / detuneScale;
    } else {
        baseFreq = 20.0;
        detune = 1.0;
    }
    
    interpBaseFreq += (baseFreq - interpBaseFreq) / 10.0;
    
    freq[0] = interpBaseFreq + detune;
    freq[1] = interpBaseFreq - detune;
    
    synth->set("freq_l", freq[0]);
    synth->set("freq_r", freq[1]);

    fbo.begin();
    shader.begin();
    shader.setUniform1f("time", time);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform1f("freq_l", freq[0]);
    shader.setUniform1f("freq_r", freq[1]);
    shader.setUniform1f("waveLength", waveLength);
    shader.setUniform1f("speed", waveSpeed);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    fbo.end();
    
    fbo.draw(0, ofGetHeight(), ofGetWidth(), -ofGetHeight());
    
    if (showLog) {
        ofDrawBitmapString("freq = " + ofToString(freq[0], 0) + ", " + ofToString(freq[1], 0), 20, 20);
        if (hands.size() > 0) {
            ofDrawBitmapString("palm z = " + ofToString(hands[0].palmPosition().y, 0), 20, 40);
        }
    }
    
    if (showGui) {
        gui.draw();
    }
}

void Ripple::exit(){
    synth->free();
}

void Ripple::mouseReleased(int x, int y, int button){
    showGui? showGui = false : showGui = true;
    showGui? ofShowCursor() : ofHideCursor();
}

string Ripple::getName(){
    return "ripple";
}
