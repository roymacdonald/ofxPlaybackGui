//
//  ofxPlaybackGui.hpp
//  playback widget
//
//  Created by Roy Macdonald on 12-06-22.
//

#pragma once

#include "ofParameter.h"
#include "ofxBaseGui.h"
#include "ofxMiniGui.h"

class ofxPlaybackGui: public ofxBaseGui{
public:
    ofxPlaybackGui(){}
    ~ofxPlaybackGui(){}
    
    ofxPlaybackGui* setup(float x = 10, float y = 10);
    
    std::unique_ptr<ofxMiniButton> fwdButton = nullptr;//  forwards
    std::unique_ptr<ofxMiniButton> backButton = nullptr;//  backwards
    std::unique_ptr<ofxMiniButton> stopButton = nullptr;
    std::unique_ptr<ofxMiniPlayPause> playPauseButton = nullptr;
    
    
    void add(ofxBaseGui * element);
    

    virtual void sizeChangedCB();

    virtual bool mouseMoved(ofMouseEventArgs & args);
    virtual bool mousePressed(ofMouseEventArgs & args);
    virtual bool mouseDragged(ofMouseEventArgs & args);
    virtual bool mouseReleased(ofMouseEventArgs & args);
    virtual bool mouseScrolled(ofMouseEventArgs & args);


    virtual ofAbstractParameter & getParameter();

    virtual void setPosition(const glm::vec3& p);
    virtual void setPosition(float x, float y);
    
    
protected:

    void updateChildrenPositions(bool bUpdateWidth = false);
    
    

    virtual void render();
    virtual bool setValue(float mx, float my, bool bCheck);
    
    virtual void generateDraw();

    ofParameterGroup parameters;


    bool bGuiActive = false;

    ofPath border;
    


private:
    std::vector<ofxBaseGui*> collection;
};
