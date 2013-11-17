#include "Harmony.h"

void Harmony::stateEnter(){
    synth->create();
}


void Harmony::stateExit(){
    synth->free();
    ofSleepMillis(500);
}

void Harmony::setup(){
    gui.setup();
    gui.add(freqScale.setup("Freq Harmoy", 0.5, 0.0001, 2.0));
    gui.add(speed.setup("Line speed", 2.0, 0.0, 4.0));
    gui.add(outLevel.setup("Level Harmony", 1.0, 0, 5.0));
    gui.add(showLog.setup("Show Log", false));
    gui.loadFromFile("settings.xml");
    
    width = ofGetWidth() / 2;
    height = ofGetHeight() / 2;
    
    fbo.allocate(width, height);
    shader.load("lines");
    synth = new ofxSCSynth("harmony");
}

void Harmony::update(){
    hands = getSharedData().leap.getLeapHands();
    
    switch (getSharedData().leap.iGestures){
        case 3:
        case 4:
        ofBackground(0);
        changeState("noise");
        break;
    }
}

void Harmony::draw(){
    ofBackground(0);
    if (hands.size() > 0) {
        baseFreq = hands[0].palmPosition().y * 0.4;
    } else {
        baseFreq = 10;
    }
    
    interpBaseFreq += (baseFreq - interpBaseFreq) / 20.0;
    synth->set("lpf", interpBaseFreq * freqScale);
    synth->set("rq", 0.5);
    synth->set("amp", outLevel);

    float resolution[] = {width, height};
    float time = ofGetElapsedTimef() / 10.0;
    
    float level = ofMap(interpBaseFreq, 0, 800, 1.0, 0.9);
    
    fbo.begin();
    shader.begin();
    shader.setUniform1f("time", time * speed);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform1f("level", level);
    
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

void Harmony::exit(){
    synth->free();
}

void Harmony::mouseReleased(int x, int y, int button){
    if(getSharedData().showGui){
        getSharedData().showGui = false;
        ofHideCursor();
    }else{
        getSharedData().showGui = true;
        ofShowCursor();
    }
}

string Harmony::getName(){
    return "harmony";
}