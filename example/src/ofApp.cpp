#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	cout << "Started the ofxGiantImage test app" << endl;
    
	giantImage.loadImage("map.jpg");
	cout << "loaded the image" << endl;
	
	bDrawTileBounds = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	FPS = ofGetFrameRate();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
	float x = mousePos.x;
	float y = mousePos.y;
	float w = ofGetWidth();
	float h = ofGetHeight();
	
	// draw the giant image
	ofSetColor(255, 255, 255);
	giantImage.draw(x, y, w, w);
	
	// draw the overview of tiles (only for debugging
	if(bDrawTileBounds){
		ofSetColor(0, 0, 255);
		giantImage.drawBounds(x, y, w, w);
	}
    
	ofSetColor(0, 0, 0);
	ofDrawBitmapString("Press a key to toggle the demo view.\nFrame rate: "+ofToString(FPS,0)+" fps.\nThe image shown is "+ofToString(giantImage.width,0)+ " by "+ofToString(giantImage.height)+" pixels.", 10, 10);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	bDrawTileBounds=!bDrawTileBounds;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    x = (giantImage.width - ofGetWidth()) * (float) x / (float) ofGetWidth();
	y = (giantImage.height - ofGetHeight()) * (float) y / (float) ofGetHeight();
	
	// zeno the mouseposition, for smooth motion
	mousePos.x += (x - mousePos.x)/5;
	mousePos.y += (y - mousePos.y)/5;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}