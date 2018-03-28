#include "ofApp.h"
#include <random>

//--------------------------------------------------------------
void ofApp::setup(){
    
    walls.push_back(move(squareWall(500, 330)));
//    walls.push_back(move(squareWall(500, 330)));
//    walls.push_back(move(squareWall(600, 330)));
    
    parameters.add(wallSize.set("WallSize", glm::vec2(500,330), glm::vec2(100,100), glm::vec2(1000,1000)));
    parameters.add(moduleSize.set("Module Size", 7, 1, 20));
    parameters.add(bigModuleProbability.set("Big Probability", 0.2, 0.001, .999));
    parameters.add(bigModuleOrientation.set("Big orient H - V", 0.5, .001, .999));
    parameters.add(density.set("Density", 0.5, 0, 1));
    parameters.add(applyProbMap.set("Apply Prob Map", true));
    parameters.add(applyBigProbMap.set("Apply Big Prob Map", true));
    parameters.add(drawProbMap.set("Draw Prob Map", false));
    parameters.add(drawBigProbMap.set("Draw Big Prob Map", false));
    parameters.add(button.set("Press or ' ' to new layout"));
    parameters.add(saveTrigger.set("Press or 's' to save Presset"));

    
    for(auto &wall : walls) wall.moduleSize = moduleSize;
    for(auto &wall : walls) wall.bigModuleProbability = bigModuleProbability;
    for(auto &wall : walls) wall.bigModuleOrientation = bigModuleOrientation;
    for(auto &wall : walls) wall.density = density;
    for(auto &wall : walls) wall.applyProbMap = applyProbMap;
    for(auto &wall : walls) wall.applyBigProbMap = applyBigProbMap;

    
    eventListeners.push_back(wallSize.newListener([&](glm::vec2 &v){
        for(auto &wall : walls) wall.width = v.x;
        for(auto &wall : walls) wall.height = v.y;
        for(auto &wall : walls) wall.computeNewWall();

    }));
    
    eventListeners.push_back(moduleSize.newListener([&](float &f){
        for(auto &wall : walls) wall.moduleSize = f;
        for(auto &wall : walls) wall.computeNewWall();
    }));
    eventListeners.push_back(bigModuleProbability.newListener([&](float &f){
        for(auto &wall : walls) wall.bigModuleProbability = f;
        for(auto &wall : walls) wall.computeNewWall();
    }));
    eventListeners.push_back(bigModuleOrientation.newListener([&](float &f){
        for(auto &wall : walls) wall.bigModuleOrientation = f;
        for(auto &wall : walls) wall.computeNewWall();
    }));
    eventListeners.push_back(density.newListener([&](float &f){
        for(auto &wall : walls) wall.density = f;
        for(auto &wall : walls) wall.computeNewWall();
    }));
    eventListeners.push_back(applyProbMap.newListener([&](bool &b){
        for(auto &wall : walls) wall.applyProbMap = b;
        for(auto &wall : walls) wall.computeNewWall();
    }));
    eventListeners.push_back(applyBigProbMap.newListener([&](bool &b){
        for(auto &wall : walls) wall.applyBigProbMap = b;
        for(auto &wall : walls) wall.computeNewWall();
    }));
    eventListeners.push_back(drawProbMap.newListener([&](bool &b){
        for(auto &wall : walls) wall.drawProbMap = b;
    }));
    eventListeners.push_back(drawBigProbMap.newListener([&](bool &b){
        for(auto &wall : walls) wall.drawBigProbMap = b;
    }));
    
    eventListeners.push_back(button.newListener([&](){
        for(auto &wall : walls) wall.computeNewWall();
    }));
    
    
    moduleSize = moduleSize;
    bigModuleProbability = bigModuleProbability;
    density = density;
    bigModuleOrientation = bigModuleOrientation;
    applyProbMap = applyProbMap;
    applyBigProbMap = applyBigProbMap;
    drawProbMap = drawProbMap;
    drawBigProbMap = drawBigProbMap;
    
    gui.setup(parameters);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    gui.draw();
    int guiRightPoint = gui.getPosition().x + gui.getWidth();
    walls[0].draw(ofRectangle(guiRightPoint, 0, ofGetWidth()-guiRightPoint, ofGetHeight()));
    int margin = 40;
    int probabilityMapDrawY = gui.getPosition().y + gui.getHeight() + margin;
    int textureHeight = (float)walls[0].height/(float)walls[0].width * (float)gui.getWidth();
    ofPushStyle();
    ofNoFill();
    ofSetColor(255);
    ofSetLineWidth(1);
    if(walls[0].probabilityMap.isAllocated()){
        ofDrawBitmapString("Probability Map", gui.getPosition().x, probabilityMapDrawY - 5);
        ofDrawRectangle(gui.getPosition().x-1, probabilityMapDrawY, gui.getWidth()+1, textureHeight+1);
        walls[0].probabilityMap.draw(gui.getPosition().x, probabilityMapDrawY, gui.getWidth(), textureHeight);
    }
    probabilityMapDrawY += textureHeight + margin;
    if(walls[0].bigProbabilityMap.isAllocated()){
        ofDrawBitmapString("Big Probability Map", gui.getPosition().x, probabilityMapDrawY - 5);
        ofDrawRectangle(gui.getPosition().x-1, probabilityMapDrawY, gui.getWidth()+1, textureHeight+1);
        walls[0].bigProbabilityMap.draw(gui.getPosition().x, probabilityMapDrawY, gui.getWidth(), textureHeight);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's'){
        for(int i = 0; i < walls.size(); i++){
            walls[i].save("walls", i);
        }
    }else if(key == ' '){
        for(auto &wall : walls) wall.computeNewWall();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    for(auto file : dragInfo.files){
        if(ofStringTimesInString(file, "big") > 0){
            for(auto &wall : walls) wall.bigProbabilityMap.load(file);
        }else{
            for(auto &wall : walls) wall.probabilityMap.load(file);
        }
    }
    for(auto &wall : walls) wall.computeNewWall();
}
