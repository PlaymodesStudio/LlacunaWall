//
//  squareWall.h
//  LLacuna_pattern_generator
//
//  Created by Eduard Frigola Bagué on 23/03/2018.
//

#ifndef squareWall_h
#define squareWall_h

#include "ofMain.h"

class squareWall{
public:
    squareWall(int _width, int _height);
    ~squareWall(){};
    
    void computeNewWall();
    void draw(int x, int y);
    
    void createRectangle();
    
    float moduleSize;
    int    bigModuleNumReplicate;
    float  spacing;
    float  bigModuleProbability;
    float  density;
    float  borderAlign;
    
    int width, height;
    
    vector<ofRectangle> modules;
};

#endif /* squareWall_h */
