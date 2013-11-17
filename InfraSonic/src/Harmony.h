#pragma once

#include "ofxState.h"
#include "SharedData.h"
#include "ofxLeapMotion.h"
#include "ofxSuperCollider.h"
#include "ofxSuperColliderServer.h"
#include "ofxGui.h"

class Harmony : public itg::ofxState<SharedData> {
public:
    void stateEnter();
    void stateExit();
    
    void setup();
    void update();
    void draw();
    void mouseReleased(int x, int y, int button);
    void exit();
    
    string getName();
    
    vector <ofxLeapMotionSimpleHand> simpleHands;
    vector <ofVec3f> palmNormals;
    vector <Hand> hands;
    
    ofFbo fbo;
    ofShader shader;
    float width, height;
    
    float baseFreq;
    float interpBaseFreq;
    float rq;
    
    ofxPanel gui;
    ofxFloatSlider freqScale;
    ofxFloatSlider speed;
    ofxFloatSlider outLevel;
    ofxToggle showLog;
    
    ofxSCSynth *synth;
};