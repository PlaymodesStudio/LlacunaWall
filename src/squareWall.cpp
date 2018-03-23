//
//  squareWall.cpp
//  LLacuna_pattern_generator
//
//  Created by Eduard Frigola Bagué on 23/03/2018.
//

#include "squareWall.h"
#include "ofMath.h"

squareWall::squareWall(int _width, int _height) : width(_width), height(_height){

}

void squareWall::computeNewWall(){
    modules.clear();
    createRectangle();
}

void squareWall::draw(int x, int y){
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(x, y);
    ofScale(1, 1);
    ofSetColor(255);
    ofDrawRectangle(0, 0, width, height);
    ofPopMatrix();
    for(auto module : modules){
        ofPushMatrix();
        ofTranslate(module.x + x, module.y + y);
        ofScale(1, 1);
//        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(255, 0, 0);
        ofDrawRectangle(0, 0, module.width, module.height);
        ofPopMatrix();
    }
    ofPopStyle();
}

void squareWall::createRectangle(){
    int notFoundAccumulate = 0;
    while(notFoundAccumulate < density){
        float margin = moduleSize + ofRandom((1-borderAlign) * moduleSize);
        float x = int(ofRandom((pow(ofRandom(1-borderAlign), 0.3)*16) + 2, (width/moduleSize) - 2 - (pow(ofRandom(1-borderAlign), 0.3)*8))) * moduleSize;
        float y = int(ofRandom((pow(ofRandom(1-borderAlign), 0.3)*16) + 2, (height/moduleSize)- 2 - (pow(ofRandom(1-borderAlign), 0.3)*8))) * moduleSize;
        float m_width = moduleSize;
        float m_height = moduleSize;
        if(ofRandom(1) < bigModuleProbability){
            if(ofRandom(1) < .5){
                m_width = moduleSize * bigModuleNumReplicate;
                x = int(ofRandom((pow(ofRandom(1-borderAlign), 0.3)*16) + 3, (width/moduleSize) - 3 - (pow(ofRandom(1-borderAlign), 0.3)*8))) * moduleSize;
                if(x < width/2){
                    x = x + (moduleSize /2);
                }else{
                    x = x - (moduleSize /2);
                }
            }else{
                m_height = moduleSize * bigModuleNumReplicate;
                y = int(ofRandom((pow(ofRandom(1-borderAlign), 0.3)*16) + 3, (height/moduleSize)- 3 - (pow(ofRandom(1-borderAlign), 0.3)*8))) * moduleSize;
                if(y < height/2){
                    y = y + (moduleSize /2);
                }else{
                    y = y - (moduleSize /2);
                }
            }
        }
        ofRectangle possibleModule;
        possibleModule.setFromCenter(x, y, m_width, m_height);
        ofRectangle possibleModuleWithMargins;
        possibleModuleWithMargins.setFromCenter(x, y, m_width+spacing, m_height+spacing);
        bool canBeConstructed = true;
        for(auto module : modules){
            ofRectangle rect;
            rect.setFromCenter(module.getCenter().x, module.getCenter().y, module.width+spacing, module.height+spacing);
            if(possibleModuleWithMargins.intersects(rect)){
                canBeConstructed = false;
                break;
            }
        }
        if(canBeConstructed){
            modules.push_back(possibleModule);
            notFoundAccumulate = 0;
        }else{
            notFoundAccumulate++;
        }
    }
//    if(modules.size() < density){
//        createRectangle();
//    }else{
//        return;
//    }
}
