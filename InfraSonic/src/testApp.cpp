#include "testApp.h"
#include "Ripple.h"
#include "Noise.h"
#include "Harmony.h"
#include "Pulse.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofxSuperColliderServer::init();
    ofHideCursor();
    ofEnableAlphaBlending();
    
    //Leap init
    stateMachine.getSharedData().leap.open();
    stateMachine.getSharedData().leap.setupGestures();

	// initialise state machine
	stateMachine.addState<Ripple>();
    stateMachine.addState<Noise>();
    stateMachine.addState<Harmony>();
    stateMachine.addState<Pulse>();

    // select state
    stateMachine.changeState("ripple");
}

//--------------------------------------------------------------
void testApp::update(){
    stateMachine.getSharedData().leap.updateGestures();
    stateMachine.getSharedData().leap.markFrameAsOld();
}

//--------------------------------------------------------------
void testApp::draw(){
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'f') {
        ofToggleFullscreen();
    }
    if (key == '1') {
        stateMachine.changeState("ripple");
    }
    if (key == '2') {
        stateMachine.changeState("harmony");
    }
    if (key == '3') {
        stateMachine.changeState("noise");
    }
    if (key == '4') {
        stateMachine.changeState("pulse");
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}

//--------------------------------------------------------------
void testApp::exit(){

}
