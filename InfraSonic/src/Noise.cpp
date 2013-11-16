#include "Noise.h"


void Noise::stateEnter(){
    synth->create();
}


void Noise::stateExit(){
    synth->free();
}

void Noise::setup(){
    showGui = false;
    gui.setup();
    gui.loadFromFile("settings.xml");
    
    width = ofGetWidth() / 2;
    height = ofGetHeight() / 2;
    
    fbo.allocate(width, height);
    shader.load("noise");
    
    baseFreq = interpBaseFreq = 20;
    synth = new ofxSCSynth("noise");
    synth->set("delay", 0.1);
}

void Noise::update(){
    hands = getSharedData().leap.getLeapHands();
}

void Noise::draw(){
    ofBackground(0);
    if (hands.size() > 0) {
        baseFreq = hands[0].palmPosition().y / 3.0;
        rq = ofMap(hands[0].palmNormal().y, -1, 1, 0.001, 1.7);
        amp = 1.0;

    } else {
        baseFreq = 20;
        rq = 1.0;
        amp = 0.1;
    }
    interpBaseFreq += (baseFreq - interpBaseFreq) / 3.0;
    interpAmp += (amp - interpAmp) / 20.0;
    synth->set("freq", baseFreq);
    synth->set("rq", rq);
    
    float resolution[] = {width, height};
    float time = ofGetElapsedTimef() / 10.0;
    
    fbo.begin();
    shader.begin();
    shader.setUniform1f("time", time);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform1f("freq", baseFreq);
    shader.setUniform1f("rq", rq);
    shader.setUniform1f("amp", interpAmp);

    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    fbo.end();
    
    fbo.draw(0, ofGetHeight(), ofGetWidth(), -ofGetHeight());
}

void Noise::exit(){
    synth->free();
}

void Noise::mouseReleased(int x, int y, int button){
    showGui? showGui = false : showGui = true;
    showGui? ofShowCursor() : ofHideCursor();
}

string Noise::getName(){
    return "noise";
}