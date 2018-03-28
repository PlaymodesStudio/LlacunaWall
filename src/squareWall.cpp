//
//  squareWall.cpp
//  LLacuna_pattern_generator
//
//  Created by Eduard Frigola Bagué on 23/03/2018.
//

#include "squareWall.h"
#include "ofMath.h"
#include <random>

squareWall::squareWall(int _width, int _height) : width(_width), height(_height){
    font.load(OF_TTF_SANS, 10, true, true, true, true);
}

void squareWall::computeNewWall(){
    modules.clear();
    createRectangle();
    colors.clear();
    colors.resize(modules.size());
    for(auto &col: colors) col = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

void squareWall::draw(int x, int y){
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(x, y);
    ofScale(1, 1);
    ofSetColor(255);
    ofDrawRectangle(0, 0, width, height);
    if(probabilityMap.isAllocated() && drawProbMap){
        ofSetColor(255, 127, 127, 127);
        probabilityMap.draw(0,0, width, height);
    }
    if(bigProbabilityMap.isAllocated() && drawBigProbMap){
        ofSetColor(127, 127, 255, 127);
        bigProbabilityMap.draw(0,0, width, height);
    }
    ofPopMatrix();
    for(int i = 0; i < modules.size(); i++){
        ofPushMatrix();
        ofTranslate(modules[i].x + x, modules[i].y + y);
        ofScale(1, 1);
//        ofSetColor(colors[i]);
        ofSetColor(0);
        ofDrawRectangle(0, 0, modules[i].width, modules[i].height);
        ofPopMatrix();
    }
    ofPopStyle();
}

void squareWall::createRectangle(){
    float margin = moduleSize + spacing;
    float gridSize = moduleSize + spacing;
    int i = 0;
    int j = 0;
    for(float x = moduleSize; x < width-margin; x = x+gridSize){
        for(float y = moduleSize; y < height-margin; y = y+gridSize){
            ofRectangle possibleModule;
            bool createdRect = false;
            if(bigProbabilityMap.isAllocated() && applyBigProbMap){
                int textureX = ((float)(x+(moduleSize/2)) / (float)width) * bigProbabilityMap.getWidth();
                int textureY = ((float)(y+(moduleSize/2)) / (float)height) * bigProbabilityMap.getHeight();
                float itemBigProb = ofClamp(bigProbabilityMap.getColor(textureX, textureY).getBrightness()/255, 0.001, 0.999);
                randomizeSizeAndOrientation(itemBigProb * bigModuleProbability, bigModuleOrientation);
            }else{
                randomizeSizeAndOrientation(bigModuleProbability, bigModuleOrientation);
            }
            for(auto chooseSize: orderedSizes){
                for(auto orientation : orderedOrientations){
                    glm::vec2 size = glm::vec2(moduleSize, moduleSize) + (abs(orientation) * (chooseSize-1) * moduleSize);
                    possibleModule.setFromCenter(x+(orientation.x*floor(chooseSize/2)*moduleSize)+(moduleSize/2), y+(orientation.y*floor(chooseSize/2)*moduleSize)+(moduleSize/2), size.x, size.y);
                    if(checkCanBeRecatngle(possibleModule)){
                        createdRect = true;
                        break;
                    }
                }
                if(createdRect){
                    break;
                }
            }
            if(createdRect){
                if(probabilityMap.isAllocated() && applyProbMap){
                    int textureX = ((float)possibleModule.getCenter().x / (float)width) * probabilityMap.getWidth();
                    int textureY = ((float)possibleModule.getCenter().y / (float)height) * probabilityMap.getHeight();
                    if(ofRandom(1) < density*(probabilityMap.getColor(textureX, textureY).getBrightness()/255)){
                        modules.push_back(possibleModule);
                    }
                }else{
                    if(ofRandom(1) < density){
                        modules.push_back(possibleModule);
                    }
                }
            }
            j++;
        }
        i++;
    }
}

void squareWall::save(string path, int _id){
    string filename = path + "/wall"+ofToString(_id) + "_" + ofGetTimestampString() +".ps";
    ofFile file;
    if(file.open(filename)){
        file.create(filename);
    }
    eps.beginEPS(filename, 0, 0, width, height);
    for(auto module : modules){
        eps.rect(module.x, module.y, module.width, module.height);
    }
    
    int modulesSize1 = 0;
    int modulesSize3 = 0;
    int modulesSize5 = 0;
    for (auto module : modules) {
        int m_widht = module.getWidth();
        int m_height = module.getHeight();
        if(m_widht == moduleSize || m_height == moduleSize) modulesSize1++;
        if(m_widht == 3*moduleSize || m_height == 3*moduleSize) modulesSize3++;
        if(m_widht == 5*moduleSize || m_height == 5*moduleSize) modulesSize5++;
    }
    
    eps.beginShape();
    vector<ofPath> paths = font.getStringAsPoints("Total-> " + ofToString(modules.size()) + "  -  Size 1-> " + ofToString(modulesSize1) +"  -  Size 3-> " + ofToString(modulesSize3) + "   -   Size 5-> " + ofToString(modulesSize5));
    for(auto &pathh : paths){
        eps.beginShape();
        for(auto &vertex : pathh.getCommands()){
            if(vertex.type == ofPath::Command::close){
                eps.polyVertex(pathh.getCommands()[0].to.x + 15, pathh.getCommands()[0].to.y + 15);
            }else{
                eps.polyVertex(vertex.to.x + 15, vertex.to.y + 15);
            }
        }
        eps.endShape();
    }
    
    eps.endEPS();
}

void squareWall::textureChanged(){
//    ofPixels pix;
//    mask.readToPixels(pix);
//
//    float margin = moduleSize + spacing;
//    xRetalls.clear();
//    yRetalls.clear();
//    xRetalls.resize(width/margin);
//    yRetalls.resize(height/margin);
}

bool squareWall::checkCanBeRecatngle(ofRectangle rect){
    ofRectangle margins(moduleSize*2, moduleSize*2, width-(moduleSize*4), height - (moduleSize*4));
    if(!margins.inside(rect)){
        return false;
    }
    ofRectangle possibleModuleWithMargins;
    possibleModuleWithMargins.setFromCenter(rect.getCenter().x, rect.getCenter().y, rect.width+(spacing*2), rect.height+(spacing*2));
    for(auto module : modules){
        if(module.intersects(rect)){
            return false;
        }
    }
    return true;
}

void squareWall::randomizeSizeAndOrientation(float bigProbability, float orientationParam){
    orderedOrientations.clear();
    vector<glm::vec2> orientations{glm::vec2(1, 0), glm::vec2(0, 1), glm::vec2(-1, 0), glm::vec2(0, -1)};
    vector<bool> selectedOrientations{0,0,0,0};
    vector<float> weights{orientationParam, 1-orientationParam, orientationParam, 1-orientationParam};
    discrete_distribution<float> orderDist(weights.begin(), weights.end());
    std::mt19937 gen;
    gen.seed(ofGetElapsedTimeMicros());
    while(orientations.size() != orderedOrientations.size()){
        int chooseIndex = orderDist(gen);
        if(selectedOrientations[chooseIndex] == 0){
            glm::vec2 &choosenOrient = orientations[chooseIndex];
            selectedOrientations[chooseIndex] = 1;
            orderedOrientations.push_back(choosenOrient);
        }
    }
    
    orderedSizes.clear();
    vector<int> sizes{1, 3, 5};
     vector<bool> selectedSizes{0,0,0,0};
    vector<float> sizeWigths{1-bigProbability, bigProbability/2, bigProbability/2};
    discrete_distribution<float> sizesDist(sizeWigths.begin(), sizeWigths.end());
    vector<float> sizesWeights{bigModuleOrientation, 1-bigModuleOrientation, bigModuleOrientation, 1-bigModuleOrientation};
    while(sizes.size() != orderedSizes.size()){
        int chooseIndex = sizesDist(gen);
        if(selectedSizes[chooseIndex] == 0){
            int choosenSize = sizes[chooseIndex];
            selectedSizes[chooseIndex] = 1;
            orderedSizes.push_back(choosenSize);
        }
    }
}
