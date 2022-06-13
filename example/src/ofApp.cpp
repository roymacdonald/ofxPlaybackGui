#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    

    playback.setup();
    
    gui.setup();
    gui.add(&playback);
    

    
    // create listeners for the buttons
    listeners.push(playback.forwards.newListener([&](){
        cout << "Forwards pressed\n";
    }));

    listeners.push(playback.backwards.newListener([&](){
        cout << "Backwards pressed\n";
    }));
        
    listeners.push(playback.rec.newListener([&](){
        cout << "Rec pressed\n";
    }));
    
    listeners.push(playback.stop.newListener([&](){
        cout << "Stop pressed\n";
    }));

    // Notice that the play listener needs a function with a 'bool &' argument.
    // That argument will be true when playing and false when not playing
    listeners.push(playback.play.newListener([&](bool& play){
        //std::boolalpha is used so it prints true or false, instead of 1 and 0 when passing a bool to cout;
        cout << "Play Paused pressed. Playing "<< std::boolalpha << play <<"\n";
    }));

    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
