#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "squareWall.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxPanel gui;
    ofParameterGroup parameters;
    ofParameter<glm::vec2>    wallSize;
    ofParameter<float> moduleSize;
    ofParameter<int>    bigModuleNumReplicate;
    ofParameter<glm::vec2> offset;
    ofParameter<float>  bigModuleProbability;
    ofParameter<float>  bigModuleOrientation;
    ofParameter<float>  density;
    ofParameter<float>  borderAlign;
    ofParameter<bool>   applyProbMap;
    ofParameter<bool>   applyBigProbMap;
    ofParameter<bool>   drawProbMap;
    ofParameter<bool>   drawBigProbMap;
    ofParameter<void>   button;
    ofParameter<void>   saveTrigger;
    ofParameter<void>   randomizeParams;
    
    ofParameter<string> probabilityMapString;
    ofParameter<string> bigProbabilityMapString;
    
    vector<ofEventListener> eventListeners;
    
    vector<squareWall> walls;
};
