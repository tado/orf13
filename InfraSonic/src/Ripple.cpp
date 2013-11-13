#include "Ripple.h"

void Ripple::setup(){
    leap.open();
    width = ofGetWidth() / 2;
    height = ofGetHeight() / 2;
    
    fbo.allocate(width, height);
    shader.load("shader");
    
    baseFreq = 20;
    detune = 1;
    freq[0] = freq[1] = baseFreq;
    
    ofxSuperColliderServer::init();
    
    synth = new ofxSCSynth("ripple");
    synth->create();
    
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
        detune = baseFreq * palmNormals[0].x / 2.0;
    } else {
        baseFreq = 20.0;
        detune = 1.0;
    }
    
    freq[0] = baseFreq + detune;
    freq[1] = baseFreq - detune;
    
    synth->set("freq_l", freq[0]);
    synth->set("freq_r", freq[1]);

    fbo.begin();
    shader.begin();
    shader.setUniform1f("time", time);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform1f("freq_l", freq[0]);
    shader.setUniform1f("freq_r", freq[1]);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    fbo.end();
    
    fbo.draw(0, ofGetHeight(), ofGetWidth(), -ofGetHeight());
    
    /*
     ofDrawBitmapString("freq = " + ofToString(freq[0], 0) + ", " + ofToString(freq[1], 0), 20, 20);
    if (hands.size() > 0) {
        ofDrawBitmapString("palm z = " + ofToString(hands[0].palmPosition().y, 0), 20, 40);
    }
     */
    
}

void Ripple::exit(){
    synth->free();
}

string Ripple::getName(){
    return "ripple";
}
