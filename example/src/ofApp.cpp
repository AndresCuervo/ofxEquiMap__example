#include "ofMain.h"
#include "ofxEquiMap.h"

class ofApp : public ofBaseApp, public ofxEquiMap::Scene{
    ofxEquiMap::Renderer em;
    ofxEquiMap::CustomFboRenderer em2;
    
    ofVboMesh m;
    ofBoxPrimitive box;
public:
    void setup()
    {
        ofSetVerticalSync(true);
        ofSetFrameRate(60);
        em.setup(1024, this);
        em2.setup(1024, this, GL_RGB, 4);
        ofSpherePrimitive p(1000, 24);
        m = p.getMesh();
        
        box.set( 80 );
    }
    
    void drawEquiScene()
    {
        ofPushStyle();
        ofSetLineWidth(3);
        ofSetColor(192);
        m.drawWireframe();
        
        box.setPosition(ofGetWidth()*.5 * (ofGetFrameNum() % 50) * 0.02, ofGetHeight()*.5, 0);
        int spin = ofGetFrameNum() % 360;
        
        box.rotate(spin, 1.0, 0.0, 0.0);
        box.rotate(spin, 0, 1.0, 0.0);

        
        
        for (int y = -3; y < 9; y += 3) {
            ofPushMatrix();
            
            ofTranslate(-10, y);
            box.draw();
            ofTranslate(-3, 0);
            box.draw();
            ofTranslate(6, 0);
            box.draw();
            ofTranslate(3, 0);
            box.draw();
            
            ofPopMatrix();
        }
        
        ofPopStyle();
    }
    
    void update() {
        em.render();
        em2.render();
    }
    
    bool show_text = false;
    
    void draw() {
        ofClear(0);
        if (ofGetKeyPressed(' ')) {
            em.draw(0, 0, ofGetWidth(), ofGetHeight());
            if (show_text) ofDrawBitmapStringHighlight("Renderer", 10, 40);
        } else {
            em2.draw(0, 0, ofGetWidth(), ofGetHeight());
            if (show_text) ofDrawBitmapStringHighlight("CustomFboRenderer", 10, 40);
        }
        
        if (show_text) ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 20);
        ofSaveScreen(ofToString(ofGetFrameNum(), 6, '0')+".png"); // save frame!
        if (ofGetFrameNum() >= 1200) {
            ofExit();
        }
        
//        ofExit();
    }
};

//========================================================================
int main( ){
    ofSetupOpenGL(1280,640,OF_WINDOW);            // <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
    
}
