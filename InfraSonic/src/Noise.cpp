#include "Noise.h"


void Noise::stateEnter(){
    synth->create();
}


void Noise::stateExit(){
    synth->free();
}

void Noise::setup(){
    gui.setup();
    gui.add(freqScale.setup("Freq scale", 0.5, 0.0001, 1.0));
    gui.add(outLevel.setup("Audio Level", 0.5, 0, 1.0));
    gui.loadFromFile("settings.xml");
    
    width = ofGetWidth() / 2;
    height = ofGetHeight() / 2;
    
    fbo.allocate(width, height);
    shader.load("noise");
    
    baseFreq = interpBaseFreq = 20;
    synth = new ofxSCSynth("noise");
}

void Noise::update(){
    hands = getSharedData().leap.getLeapHands();
}

void Noise::draw(){
    ofBackground(0);
    if (hands.size() > 0) {
        baseFreq = hands[0].palmPosition().y * freqScale;
        rq = ofMap(hands[0].palmNormal().y, -1, 1, 0.001, 0.5);
        delay = ofMap(hands[0].palmNormal().x, -1, 1, 0.05, 2.0);

        amp = 1.0;

    } else {
        baseFreq = 20;
        rq = 1.0;
        amp = 0.1;
    }
    interpBaseFreq += (baseFreq - interpBaseFreq) / 20.0;
    interpAmp += (amp - interpAmp) / 20.0;
    synth->set("freq", baseFreq);
    synth->set("rq", rq);
    synth->set("amp", outLevel);
    synth->set("delay", delay);

    
    float resolution[] = {width, height};
    float time = ofGetElapsedTimef() / 10.0;
    
    fbo.begin();
    shader.begin();
    shader.setUniform1f("time", time);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform1f("freq", baseFreq * 10);
    shader.setUniform1f("rq", rq);
    shader.setUniform1f("amp", interpAmp);

    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    fbo.end();
    fbo.draw(0, ofGetHeight(), ofGetWidth(), -ofGetHeight());
    
    if (getSharedData().showGui) {
        gui.draw();
    }
}

void Noise::exit(){
    synth->free();
}

void Noise::mouseReleased(int x, int y, int button){
    if(getSharedData().showGui){
        getSharedData().showGui = false;
        ofHideCursor();
    }else{
        getSharedData().showGui = true;
        ofShowCursor();
    }
}

string Noise::getName(){
    return "noise";
}