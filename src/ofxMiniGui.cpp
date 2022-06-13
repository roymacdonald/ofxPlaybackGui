//
//  ofxMiniGui.cpp
//  playback widget
//
//  Created by Roy Macdonald on 12-06-22.
//

#include "ofxMiniGui.h"
#include "ofGraphics.h"
using namespace std;

ofxMiniToggle::ofxMiniToggle(ofParameter<bool> _bVal, float width, float height){
    setup(_bVal,width,height);
}

ofxMiniToggle::~ofxMiniToggle(){
    value.removeListener(this,&ofxMiniToggle::valueChanged);
}

ofxMiniToggle * ofxMiniToggle::setup(ofParameter<bool> _bVal, float width, float height){
    b.x = 0;
    b.y = 0;
    b.width = width;
    b.height = height;
    bGuiActive = false;
    value.makeReferenceTo(_bVal);
//    checkboxRect.set(1, 1, b.height - 2, b.height - 2);

    value.addListener(this,&ofxMiniToggle::valueChanged);
    registerMouseEvents();
    setNeedsRedraw();

    return this;

}

ofxMiniToggle * ofxMiniToggle::setup(const std::string& toggleName, bool _bVal, float width, float height){
    value.set(toggleName,_bVal);
    return setup(value,width,height);
}


bool ofxMiniToggle::mouseMoved(ofMouseEventArgs & args){
    if(isGuiDrawing() && b.inside(args)){
        return true;
    }else{
        return false;
    }
}

bool ofxMiniToggle::mousePressed(ofMouseEventArgs & args){
    if(setValue(args.x, args.y, true)){
        return true;
    }else{
        return false;
    }
}

bool ofxMiniToggle::mouseDragged(ofMouseEventArgs & args){
    if(bGuiActive && b.inside(args)){
        return true;
    }else{
        return false;
    }
}

bool ofxMiniToggle::mouseReleased(ofMouseEventArgs & args){
    bool wasGuiActive = bGuiActive;
    bGuiActive = false;
    if(wasGuiActive && b.inside(args)){
        return true;
    }else{
        return false;
    }
}

void ofxMiniToggle::generateDraw(){
    bg.clear();
    bg.setFillColor(thisBackgroundColor);
    bg.rectangle(b);

    fg.clear();
        fg.setFilled(true);
        fg.setFillColor(thisFillColor);
        fg.setStrokeWidth(1);
        fg.setStrokeColor(thisBorderColor);
    
    fg.rectangle(b);

  
}

void ofxMiniToggle::render(){
    bg.draw();

    if( value ){
        fg.draw();
    }

    ofColor c = ofGetStyle().color;
    ofBlendMode blendMode = ofGetStyle().blendingMode;
    if(blendMode!=OF_BLENDMODE_ALPHA){
        ofEnableAlphaBlending();
    }
    ofSetColor(thisTextColor);

    
    icon.draw();
    

    ofSetColor(c);
    if(blendMode!=OF_BLENDMODE_ALPHA){
        ofEnableBlendMode(blendMode);
    }
}

bool ofxMiniToggle::operator=(bool v){
    value = v;
    return v;
}

ofxMiniToggle::operator const bool & (){
    return value;
}

bool ofxMiniToggle::setValue(float mx, float my, bool bCheck){
    
    if( !isGuiDrawing() ){
        bGuiActive = false;
        return false;
    }
    if( bCheck ){
        cout << "ofxMiniToggle::setValue " << getName() << "  " << value.get() << " b: " << b << " mouse: " << mx << ", " << my <<endl;
        if( b.inside(mx, my) ){
            cout << "Inside\n";
            bGuiActive = true;
        }else{
            bGuiActive = false;
        }
    }
    if( bGuiActive ){
        value = !value;
        return true;
    }
    return false;
}


ofAbstractParameter & ofxMiniToggle::getParameter(){
    return value;
}

void ofxMiniToggle::valueChanged(bool & value){
    setNeedsRedraw();
}



//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

ofxMiniButton::ofxMiniButton(){
    value.setSerializable(false);
}

ofxMiniButton::ofxMiniButton(ofParameter<void> _bVal, float width, float height){
    setup(_bVal, width, height);
}

ofxMiniButton::ofxMiniButton(const std::string& toggleName, float width, float height){
    setup(toggleName, width, height);
}

ofxMiniButton::~ofxMiniButton(){
    //
}

ofxMiniButton* ofxMiniButton::setup(ofParameter<void> _bVal, float width, float height){
    parameter = _bVal;
    
    return setup(parameter.getName(), width, height);
}

ofxMiniButton* ofxMiniButton::setup(const std::string& toggleName, float width, float height){
    setName(toggleName);
    value = false;
    b.x = 0;
    b.y = 0;
    b.width = width;
    b.height = height;
    bGuiActive = false;

    registerMouseEvents();

    value.addListener(this,&ofxMiniButton::valueChanged);

    return this;
}

bool ofxMiniButton::mouseReleased(ofMouseEventArgs & args){
    bool attended = setValue(args.x, args.y, false);
    bGuiActive = false;
    if(attended){
        return true;
    }else{
        return false;
    }
}

bool ofxMiniButton::mouseMoved(ofMouseEventArgs & args){
    return ofxMiniToggle::mouseMoved(args);
}

bool ofxMiniButton::mousePressed(ofMouseEventArgs & args){
    return ofxMiniToggle::mousePressed(args);
}

bool ofxMiniButton::mouseDragged(ofMouseEventArgs & args){
    return ofxMiniToggle::mouseDragged(args);
}

ofAbstractParameter & ofxMiniButton::getParameter(){
    return parameter;
}

void ofxMiniButton::valueChanged(bool & v){
    if(!v){
        parameter.trigger();
    }
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

ofxMiniPlayPause::ofxMiniPlayPause(ofParameter<bool> _bVal, float width, float height):
ofxMiniToggle(_bVal, width, height)
{
    
    int margin = 1;
    float w  = b.width - (2*margin);
    float rw = floor(w* 0.4 );
    ofRectangle r = {b.x + margin, b.y + margin,  rw, b.height - (2*margin)};
    iconPause.rectangle(r);
    r.x += w - rw;
    iconPause.rectangle(r);
    
    float co  = tan(ofDegToRad(30)) * w;
    float h2 = r.getCenter().y;
    icon.moveTo(margin, h2-co);
    icon.lineTo(b.getMaxX() - (2*margin), h2);
    icon.lineTo(margin, h2+co);
    icon.close();
    
    
}


void ofxMiniPlayPause::render(){
    bg.draw();

    if( value ){
        fg.draw();
    }

    ofColor c = ofGetStyle().color;
    ofBlendMode blendMode = ofGetStyle().blendingMode;
    if(blendMode!=OF_BLENDMODE_ALPHA){
        ofEnableAlphaBlending();
    }
    ofSetColor(thisTextColor);

    if( value ){
        iconPause.draw();
    }else{
        icon.draw();
    }
    

    ofSetColor(c);
    if(blendMode!=OF_BLENDMODE_ALPHA){
        ofEnableBlendMode(blendMode);
    }
}
//ofPath iconPause;
