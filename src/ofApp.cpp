#include "ofApp.h"
#include <random>

//--------------------------------------------------------------
void ofApp::setup(){
    
    walls.push_back(move(squareWall(500, 330)));
    walls.push_back(move(squareWall(500, 330)));
    walls.push_back(move(squareWall(600, 330)));
    
    eventListeners.push_back(moduleSize.newListener([&](float &f){
        for(auto &wall : walls) wall.moduleSize = f;
    }));
    eventListeners.push_back(bigModuleNumReplicate.newListener([&](int &f){
        for(auto &wall : walls) wall.bigModuleNumReplicate = f;
    }));
    eventListeners.push_back(spacing.newListener([&](float &f){
        for(auto &wall : walls) wall.spacing = f;
    }));
    eventListeners.push_back(bigModuleProbability.newListener([&](float &f){
        for(auto &wall : walls) wall.bigModuleProbability = f;
    }));
    eventListeners.push_back(bigModuleOrientation.newListener([&](float &f){
        for(auto &wall : walls) wall.bigModuleOrientation = f;
    }));
    eventListeners.push_back(density.newListener([&](float &f){
        for(auto &wall : walls) wall.density = f;
    }));
    eventListeners.push_back(borderAlign.newListener([&](float &f){
        for(auto &wall : walls) wall.borderAlign = f;
    }));
    eventListeners.push_back(applyProbMap.newListener([&](bool &b){
        for(auto &wall : walls) wall.applyProbMap = b;
    }));
    eventListeners.push_back(applyBigProbMap.newListener([&](bool &b){
        for(auto &wall : walls) wall.applyBigProbMap = b;
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
    
    parameters.add(moduleSize.set("Module Size", 7, 1, 20));
    parameters.add(bigModuleNumReplicate.set("Big Module x", 2, 2, 5));
    parameters.add(spacing.set("Spacing", 7, 0, 20));
    parameters.add(bigModuleProbability.set("Big Probability", 0.2, 0.001, .999));
    parameters.add(bigModuleOrientation.set("Big orient H - V", 0.5, .001, .999));
    parameters.add(density.set("Density", 0.5, 0, 1));
    parameters.add(borderAlign.set("Border Align", 0.5, 0, 1));
    parameters.add(button.set("Trigger"));
    parameters.add(applyProbMap.set("Apply Prob Map", true));
    parameters.add(applyBigProbMap.set("Apply Big Prob Map", true));
    parameters.add(drawProbMap.set("Draw Prob Map", false));
    parameters.add(drawBigProbMap.set("Draw Big Prob Map", false));
    
    
    moduleSize = moduleSize;
    bigModuleNumReplicate = bigModuleNumReplicate;
    spacing = spacing;
    bigModuleProbability = bigModuleProbability;
    density = density;
    
    gui.setup(parameters);
    
    eventListeners.push_back(parameters.parameterChangedE().newListener([&](ofAbstractParameter &p){
        for(auto &wall : walls) wall.computeNewWall();
    }));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    walls[0].draw(ofGetWidth() - 510, 10);
    walls[1].draw(ofGetWidth() - 510, 520);
    walls[2].draw(10, 520);
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
    if(dragInfo.files.size() == 1){
        if(ofStringTimesInString(dragInfo.files[0], "big") > 0){
            for(auto &wall : walls) wall.bigProbabilityMap.load(dragInfo.files[0]);
        }else{
            for(auto &wall : walls) wall.probabilityMap.load(dragInfo.files[0]);
        }
    }
    for(auto &wall : walls) wall.computeNewWall();
}
