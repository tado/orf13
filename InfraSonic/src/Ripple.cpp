#include "Ripple.h"

void Ripple::stateEnter(){
    synth->create();
}

void Ripple::stateExit(){
    synth->free();
    interpBaseFreq = baseFreq = 10;
    ofSleepMillis(1000);
}

void Ripple::setup(){
    gui.setup();
    gui.add(initFreq.setup("Init Frequency", 50, 10, 100));
    gui.add(waveLength.setup("Wave Length", 200, 0, 800));
    gui.add(waveSpeed.setup("Wave Speed", 100, 0, 200));
    gui.add(interp.setup("Interpolate", 100, 1, 800));
    gui.add(detuneScale.setup("Detune Scale", 10, 1, 20));
    gui.add(outLevel.setup("Level Ripple", 0.5, 0, 1.0));
    gui.add(showLog.setup("Show Log", false));
    gui.loadFromFile("settings.xml");
    
    width = ofGetWidth() / 2;
    height = ofGetHeight() / 2;
    
    fbo.allocate(width, height);
    shader.load("ripple");
    
    baseFreq = interpBaseFreq = initFreq;
    detune = 0;
    freq[0] = freq[1] = baseFreq;
    
    synth = new ofxSCSynth("ripple");   
}

void Ripple::update(){
    hands = getSharedData().leap.getLeapHands();
    
    switch (getSharedData().leap.iGestures){
        case 3:
        case 4:
            changeState("harmony");
            break;
    }
}

void Ripple::draw(){
    if (hands.size() > 0) {
        baseFreq = hands[0].palmPosition().y / 6.0;
        detune = baseFreq * hands[0].palmNormal().x / detuneScale;
    } else {
        baseFreq = initFreq;
        detune = 0.0;
    }
    
    interpBaseFreq += (baseFreq - interpBaseFreq) / 10.0;
    
    freq[0] = interpBaseFreq + detune;
    freq[1] = interpBaseFreq - detune;
    
    synth->set("freq_l", freq[0]);
    synth->set("freq_r", freq[1]);
    synth->set("amp", outLevel);
    
    float resolution[] = {width, height};
    float time = ofGetElapsedTimef();
    
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

    ofSetColor(255);
    fbo.draw(0, ofGetHeight(), ofGetWidth(), -ofGetHeight());
    
    if (showLog) {
        ofDrawBitmapString("freq = " + ofToString(freq[0], 0) + ", " + ofToString(freq[1], 0), 20, 20);
        if (hands.size() > 0) {
            ofDrawBitmapString("palm z = " + ofToString(hands[0].palmPosition().y, 0), 20, 40);
        }
    }
    
    if (getSharedData().showGui) {
        gui.draw();
    }
}

void Ripple::exit(){
    synth->free();
}

void Ripple::mouseReleased(int x, int y, int button){
    if(getSharedData().showGui){
        getSharedData().showGui = false;
        ofHideCursor();
    }else{
        getSharedData().showGui = true;
        ofShowCursor();
    }
}

string Ripple::getName(){
    return "ripple";
}
