//
//  ofxPlaybackGui.cpp
//  playback widget
//
//  Created by Roy Macdonald on 12-06-22.
//

#include "ofxPlaybackGui.hpp"

#include "ofGraphics.h"
#include "ofxGuiGroup.h"

using namespace std;


void ofxPlaybackGui::add(ofxBaseGui * element){
    collection.push_back(element);

    element->unregisterMouseEvents();

    element->setParent(this);

    // updateChild(...) could be called instead of updateChildrenPositions(...), here but the latter ensures that all the elements are placed properly.
    updateChildrenPositions(true);
    parameters.add(element->getParameter());
    setNeedsRedraw();
}


bool ofxPlaybackGui::mouseMoved(ofMouseEventArgs & args){
    if(!isGuiDrawing())return false;
    ofMouseEventArgs a = args;
    for(std::size_t i = 0; i < collection.size(); i++){
        if(collection[i]->mouseMoved(a)){
            return true;
        }
    }
    if(b.inside(args)){
        return true;
    }else{
        return false;
    }
}

bool ofxPlaybackGui::mousePressed(ofMouseEventArgs & args){
    if(!isGuiDrawing())return false;
    
    if(setValue(args.x, args.y, true)){
        return true;
    }
    auto attended = false;
    ofMouseEventArgs a = args;
    for(std::size_t i = 0; i < collection.size(); i++){
        if(collection[i]->mousePressed(a)){
            attended = true;
        }
    }
    return attended || b.inside(args);
}

bool ofxPlaybackGui::mouseDragged(ofMouseEventArgs & args){
    if(!isGuiDrawing())return false;
    if(bGuiActive){
        if(setValue(args.x, args.y, false)){
            return true;
        }
        ofMouseEventArgs a = args;
        for(std::size_t i = 0; i < collection.size(); i++){
            if(collection[i]->mouseDragged(a)){
                return true;
            }
        }
    }
    return false;
}

bool ofxPlaybackGui::mouseReleased(ofMouseEventArgs & args){
    if(!isGuiDrawing()){
        bGuiActive = false;
        return false;
    }
    if(bGuiActive){
        bGuiActive = false;
        for(std::size_t k = 0; k < collection.size(); k++){
            ofMouseEventArgs a = args;
            if(collection[k]->mouseReleased(a)){
                return true;
            }
        }
        if(b.inside(ofPoint(args.x, args.y))){
            return true;
        }else{
            return false;
        }
    }
    return false;
}

bool ofxPlaybackGui::mouseScrolled(ofMouseEventArgs & args){
    if(!isGuiDrawing())return false;
    ofMouseEventArgs a = args;
    for(std::size_t i = 0; i < collection.size(); i++){
        if(collection[i]->mouseScrolled(a)){
            return true;
        }
    }
    if(b.inside(args)){
        return true;
    }else{
        return false;
    }
}

void ofxPlaybackGui::generateDraw(){
    border.clear();
//    border.setFillColor(thisBorderColor);
    border.setFillColor(ofColor::red);
    border.setFilled(true);
    border.rectangle(b);

}

void ofxPlaybackGui::render(){
    
    border.draw();
    
    ofBlendMode blendMode = ofGetStyle().blendingMode;
    if(blendMode != OF_BLENDMODE_ALPHA){
        ofEnableAlphaBlending();
    }
    for(std::size_t i = 0; i < collection.size(); i++){
        collection[i]->draw();
    }

    if(blendMode != OF_BLENDMODE_ALPHA){
        ofEnableBlendMode(blendMode);
    }
}


bool ofxPlaybackGui::setValue(float mx, float my, bool bCheck){

    if(!isGuiDrawing()){
        bGuiActive = false;
        return false;
    }


    if(bCheck){
        if(b.inside(mx, my)){
            bGuiActive = true;
            return true;
        }
    }

    return false;
}


void ofxPlaybackGui::updateChildrenPositions(bool bUpdateWidth){
    

    float x = b.x;
    float w = b.width;
    
    if(parent){//if the group has no parent dont indent the children. it just looks better
        x += ofxGuiGroup::childrenLeftIndent;
        w -= ofxGuiGroup::childrenLeftIndent + ofxGuiGroup::childrenRightIndent;
    }

    float elems_w = 0;
    for(auto e: collection){
        if(e){
            elems_w += e->getShape().width;
        }
    }

    x += (w - ((collection.size() -1)*ofxGuiGroup::elementSpacing) - elems_w)/2;

    backButton->setPosition(x, b.y);
    x += stopButton->getShape().width + ofxGuiGroup::elementSpacing;
    
    playPauseButton->setPosition(x, b.y);
    x += playPauseButton->getShape().width + ofxGuiGroup::elementSpacing;
    
    fwdButton->setPosition(x, b.y);
    x += fwdButton->getShape().width + ofxGuiGroup::elementSpacing;
    stopButton->setPosition(x, b.y);
    
    
    
}

void ofxPlaybackGui::sizeChangedCB(){
    updateChildrenPositions(true);
    if(parent){
        parent->sizeChangedCB();
    }
    setNeedsRedraw();
}


ofAbstractParameter & ofxPlaybackGui::getParameter(){
    return parameters;
}

void ofxPlaybackGui::setPosition(const glm::vec3& p){
    b.setPosition(p);
    updateChildrenPositions(false);
    setNeedsRedraw();
}

void ofxPlaybackGui::setPosition(float x, float y){
    setPosition({x, y, 0});
}



//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

ofxPlaybackGui* ofxPlaybackGui::setup(float x, float y){
    b.x = x;
    b.y = y;
    b.height = defaultHeight;
    if(parent != nullptr){
        b.width = parent->getWidth();
    }else{
        b.width = defaultWidth;
    }
    
    bGuiActive = false;

    
    fwdButton = make_unique<ofxMiniButton> ("fwd");
    backButton = make_unique<ofxMiniButton> ("back");
    stopButton = make_unique<ofxMiniButton> ("stop");
    playPauseButton = make_unique<ofxMiniPlayPause>(" playPause");
    parameters.setName("Playback gui");
    
    this->add(backButton.get());
    this->add(playPauseButton.get());
    this->add(fwdButton.get());
    this->add(stopButton.get());

    updateChildrenPositions(true);
    registerMouseEvents();

    setNeedsRedraw();

    return this;
}


