//
//  squareWall.h
//  LLacuna_pattern_generator
//
//  Created by Eduard Frigola Bagué on 23/03/2018.
//

#ifndef squareWall_h
#define squareWall_h

#include "ofMain.h"
#include "ofxVectorGraphics.h"

class squareWall{
public:
    squareWall(int _width, int _height);
    ~squareWall(){};
    
    void computeNewWall();
    void draw(ofRectangle drawRect);
    
    void save(string filename);
    
    void createRectangle();
    void textureChanged();
    bool checkCanBeRecatngle(ofRectangle rect);
    
    void randomizeSizeAndOrientation(float bigProbability, float orientationParam);
    
    float moduleSize;
    int    bigModuleNumReplicate;
    float  spacing;
    float  bigModuleProbability;
    float  density;
    float  borderAlign;
    float  bigModuleOrientation;
    bool   applyProbMap;
    bool   applyBigProbMap;
    bool   drawProbMap;
    bool   drawBigProbMap;

    
    int width, height;
    
    vector<ofRectangle> modules;
    vector<ofColor> colors;
    
    ofImage probabilityMap;
    ofImage bigProbabilityMap;
    
    vector<glm::vec2> orderedOrientations;
    vector<int> orderedSizes;

    ofxVectorGraphics eps;
    
    ofTrueTypeFont font;
};

#endif /* squareWall_h */
