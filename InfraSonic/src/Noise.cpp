#include "Noise.h"


void Noise::stateEnter(){
    synth->create();
}

void Noise::stateExit(){
    synth->free();
    ofSleepMillis(1000);
}

void Noise::setup(){
    gui.setup();
    gui.add(freqScale.setup("Freq Noise", 0.5, 0.0001, 1.0));
    gui.add(outLevel.setup("Level Noise", 0.5, 0, 1.0));
    gui.add(showLog.setup("Show Log", false));
    gui.loadFromFile("settings.xml");

    width = ofGetWidth() / 2;
    height = ofGetHeight() / 2;
    
    fbo.allocate(width, height);
    shader.load("noise");
    synth = new ofxSCSynth("noise");
}

void Noise::update(){    
    hands = getSharedData().leap.getLeapHands();
    
    switch (getSharedData().leap.iGestures){
        case 3:
        case 4:
            ofBackground(0);
            changeState("ripple");
            break;
    }
}

void Noise::draw(){
    ofBackground(0);
    if (hands.size() > 0) {
        baseFreq = hands[0].palmPosition().y * freqScale;
        rq = ofMap(abs(hands[0].palmNormal().x), 0, 1, 0.0, 0.5);
        delay = ofMap(abs(hands[0].palmNormal().x), 0, 1, 2.0, 0.1);
        amp = 1.0;
    } else {
        baseFreq = 10;
        rq = 1.0;
        amp = 0.1;
    }

    interpBaseFreq += (baseFreq - interpBaseFreq) / 10.0;
    interpAmp += (amp - interpAmp) / 10.0;
    
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

    ofSetColor(255);
    fbo.draw(0, ofGetHeight(), ofGetWidth(), -ofGetHeight());
    
    if (showLog) {
        ofDrawBitmapString("freq = " + ofToString(interpBaseFreq, 0)
                           + ", rq = " + ofToString(rq, 4)
                           + ", amp = " + ofToString(amp, 4)
                           , 20, 20);

        if (hands.size() > 0) {
            ofDrawBitmapString("palm normal = ("
                               + ofToString(hands[0].palmNormal().x, 4) + ", "
                               + ofToString(hands[0].palmNormal().y, 4) + ", "
                               + ofToString(hands[0].palmNormal().z, 4) + ", "
                               + ")",
                               20, 40);

        }
    }
    
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