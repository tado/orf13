#include "testApp.h"
#include "Ripple.h"
#include "Noise.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofxSuperColliderServer::init();
    ofHideCursor();
    
    //Leap init
    stateMachine.getSharedData().leap.open();
    stateMachine.getSharedData().leap.setupGestures();

	// initialise state machine
	stateMachine.addState<Ripple>();
    stateMachine.addState<Noise>();
    
    stateMachine.changeState("ripple");
    //stateMachine.changeState("noise");
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
        stateMachine.changeState("noise");
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
