#include "Pulse.h"

void Pulse::stateEnter(){
    synth->create();
}

void Pulse::stateExit(){
    synth->free();
    ofSleepMillis(500);
}

void Pulse::setup(){
    gui.setup();
    gui.add(pulseSpeed.setup("Pulse Speed", 0.01, 0.0001, 0.04));
    gui.add(grainFreq.setup("Grain Freq", 30.0, 5, 100));
    gui.add(outLevel.setup("Level Pulse", 1.0, 0, 5.0));
    gui.add(showLog.setup("Show Log", false));
    gui.loadFromFile("settings.xml");
    
    width = ofGetWidth() / 2;
    height = ofGetHeight() / 2;
    
    fbo.allocate(width, height);
    shader.load("pulse");
    synth = new ofxSCSynth("pulse");
    
    pulseFreq[0] = pulseFreq[1] = pulseFreq[2] = 20;
}

void Pulse::update(){
    hands = getSharedData().leap.getLeapHands();
    
    switch (getSharedData().leap.iGestures){
        case 3:
        case 4:
            ofBackground(0);
            changeState("noise");
            break;
    }
}

void Pulse::draw(){
    ofBackground(0);
    if (hands.size() > 0) {
        float freq = hands[0].palmPosition().y * pulseSpeed + 4.0;
        float detune = freq * hands[0].palmNormal().x / 1000.0;
        pulseFreq[0] = freq - detune;
        pulseFreq[1] = 0;
        pulseFreq[2] = freq + detune;
    } else {
        pulseFreq[0] = pulseFreq[1] = pulseFreq[2] = 4.0;
    }

    synth->set("freq", grainFreq);
    synth->set("pulse_l", pulseFreq[0]);
    synth->set("pulse_r", pulseFreq[2]);
    synth->set("allAmp", outLevel);
    
    float resolution[] = {width, height};
    float time = ofGetElapsedTimef();
    
    fbo.begin();
    shader.begin();
    shader.setUniform1f("time", time);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform3fv("pulseFreq", pulseFreq);

    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    fbo.end();
    
    ofSetColor(255);
    fbo.draw(0, ofGetHeight(), ofGetWidth(), -ofGetHeight());
    
    if (showLog) {
        
    }
    
    if (getSharedData().showGui) {
        gui.draw();
    }
}

void Pulse::exit(){
    synth->free();
}

void Pulse::mouseReleased(int x, int y, int button){
    if(getSharedData().showGui){
        getSharedData().showGui = false;
        ofHideCursor();
    }else{
        getSharedData().showGui = true;
        ofShowCursor();
    }
}

string Pulse::getName(){
    return "pulse";
}