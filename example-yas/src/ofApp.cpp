#include "ofMain.h"
#include "ofxYas.h"

struct BaseClass{
    std::uint32_t x;
    ofVec3f y;
    
    BaseClass()
    :x(0)
    {}
    
    OFX_YAS_DEFINE(x,y)
    
    bool operator==(BaseClass& b) {
        return x == b.x && y == b.y;
    }
    bool operator!=(BaseClass& b) {
        return x != b.x || y != b.y;
    }
};


class ofApp : public ofBaseApp{
    BaseClass b, bb, bbb;
public:
    void setup()
    {
        b.x = 50;
        b.y = ofVec3f(1,2,3);
        
        ofBuffer buff;
        ofxYas::serialize(b, buff);
        ofxYas::deserialize(bb, buff);

        ofBuffer buff2;
        ofxYas::serializeCompacted(b, buff2);
        ofxYas::deserializeCompacted(bbb, buff2);
        
        ofLog() << "serialize : " << buff.size();
        ofLog() << "compacted : " << buff2.size();
        
        if (b != bb || b != bbb) {
            throw new std::exception();
        } else {
            ofLog() << "it works";
        }
    }
    
    void update()
    {
    }
    
    void draw()
    {
        ofClear(0);
    }
    
    void keyPressed(int key)
    {
        if (key == 'f') {
            ofToggleFullscreen();
        }
    }
    
    void keyReleased(int key) {}
    void mouseMoved(int x, int y ) {}
    void mouseDragged(int x, int y, int button) {}
    void mousePressed(int x, int y, int button) {}
    void mouseReleased(int x, int y, int button) {}
    void windowResized(int w, int h) {}
    void dragEvent(ofDragInfo dragInfo) {}
    void gotMessage(ofMessage msg) {}
    
};

//========================================================================
int main( ){
    ofSetupOpenGL(1280,720,OF_WINDOW);            // <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
    
}
