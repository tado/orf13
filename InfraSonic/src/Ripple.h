#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "ofxLeapMotion.h"
#include "ofxSuperCollider.h"
#include "ofxSuperColliderServer.h"

class Ripple : public itg::ofxState<SharedData> {
    void setup();
    void update();
    void draw();
    void exit();
    
    string getName();
    
    ofxLeapMotion leap;
    vector <ofxLeapMotionSimpleHand> simpleHands;
    ofEasyCam cam;
    ofLight light;
    vector <ofVec3f> palmNormals;
    vector <Hand> hands;
    
    ofFbo fbo;
    ofShader shader;
    float width, height;
    float baseFreq;
    float detune;
    float freq[2];
    
    ofxSCSynth *synth;
};