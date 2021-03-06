#include "ofApp.h"
#include <random>

//--------------------------------------------------------------
void ofApp::setup(){
    
    walls.push_back(move(squareWall(500, 330)));
//    walls.push_back(move(squareWall(500, 330)));
//    walls.push_back(move(squareWall(600, 330)));
    
    parameters.add(randomizeParams.set("Randomize Params"));
    parameters.add(wallSize.set("WallSize", glm::vec2(500,330), glm::vec2(100,100), glm::vec2(1000,1000)));
    parameters.add(offset.set("Offset", glm::vec2(0, 0), glm::vec2(-10, -10), glm::vec2(10, 10)));
    parameters.add(moduleSize.set("Module Size", 7, 1, 20));
    parameters.add(bigModuleProbability.set("Big Probability", 0.2, 0, 1));
    parameters.add(bigModuleOrientation.set("Big orient H - V", 0.5, 0, 1));
    parameters.add(density.set("Density", 0.5, 0, 1));
    parameters.add(applyProbMap.set("Apply Prob Map", true));
    parameters.add(probabilityMapStrength.set("Prob.Map Strength",1.0,0.0,1.0));
    parameters.add(applyBigProbMap.set("Apply Big Prob Map", true));
    parameters.add(probabilityBigMapStrength.set("Prob.Map.Big Str.",1.0,0.0,1.0));
    parameters.add(drawProbMap.set("Draw Prob Map", false));
    parameters.add(drawBigProbMap.set("Draw Big Prob Map", false));
    parameters.add(button.set("New layout (space)"));
    parameters.add(saveTrigger.set("Save Presset ('s')"));

    for(auto &wall : walls) wall.moduleSize = moduleSize;
    for(auto &wall : walls) wall.bigModuleProbability = bigModuleProbability;
    for(auto &wall : walls) wall.bigModuleOrientation = bigModuleOrientation;
    for(auto &wall : walls) wall.density = density;
    for(auto &wall : walls) wall.applyProbMap = applyProbMap;
    for(auto &wall : walls) wall.applyBigProbMap = applyBigProbMap;

    
    eventListeners.push(wallSize.newListener([&](glm::vec2 &v){
        for(auto &wall : walls) wall.width = v.x;
        for(auto &wall : walls) wall.height = v.y;
        for(auto &wall : walls) wall.computeNewWall();
    }));
    eventListeners.push(offset.newListener([&](glm::vec2 &v){
        for(auto &wall : walls) wall.offset = v;
        for(auto &wall : walls) wall.computeNewWall();
    }));
    eventListeners.push(moduleSize.newListener([&](float &f){
        for(auto &wall : walls) wall.moduleSize = f;
        for(auto &wall : walls) wall.computeNewWall();
    }));
    eventListeners.push(bigModuleProbability.newListener([&](float &f){
        for(auto &wall : walls) wall.bigModuleProbability = f;
        for(auto &wall : walls) wall.computeNewWall();
    }));
    eventListeners.push(bigModuleOrientation.newListener([&](float &f){
        for(auto &wall : walls) wall.bigModuleOrientation = f;
        for(auto &wall : walls) wall.computeNewWall();
    }));
    eventListeners.push(density.newListener([&](float &f){
        for(auto &wall : walls) wall.density = f;
        for(auto &wall : walls) wall.computeNewWall();
    }));
    eventListeners.push(applyProbMap.newListener([&](bool &b){
        for(auto &wall : walls) wall.applyProbMap = b;
        for(auto &wall : walls) wall.computeNewWall();
    }));
    eventListeners.push(applyBigProbMap.newListener([&](bool &b){
        for(auto &wall : walls) wall.applyBigProbMap = b;
        for(auto &wall : walls) wall.computeNewWall();
    }));
    eventListeners.push(drawProbMap.newListener([&](bool &b){
        for(auto &wall : walls) wall.drawProbMap = b;
    }));
    eventListeners.push(drawBigProbMap.newListener([&](bool &b){
        for(auto &wall : walls) wall.drawBigProbMap = b;
    }));
    
    eventListeners.push(button.newListener([&](){
        for(auto &wall : walls) wall.computeNewWall();
    }));

    eventListeners.push(probabilityMapStrength.newListener([&](float &f){
        for(auto &wall : walls) wall.probabilityMapStrength = f;
        for(auto &wall : walls) wall.computeNewWall();
    }));

    eventListeners.push(probabilityBigMapStrength.newListener([&](float &f){
        for(auto &wall : walls) wall.probabilityBigMapStrength = f;
        for(auto &wall : walls) wall.computeNewWall();
    }));



    eventListeners.push(randomizeParams.newListener([&](){
        bigModuleProbability = ofRandom(bigModuleProbability.getMin(), bigModuleProbability.getMax());
        bigModuleOrientation = ofRandom(bigModuleOrientation.getMin(), bigModuleOrientation.getMax());
        density = ofRandom(density.getMin(), density.getMax());
        bigModuleProbability = ofRandom(bigModuleProbability.getMin(), bigModuleProbability.getMax());
        bigModuleProbability = ofRandom(bigModuleProbability.getMin(), bigModuleProbability.getMax());
        bigModuleProbability = ofRandom(bigModuleProbability.getMin(), bigModuleProbability.getMax());
        bigModuleProbability = ofRandom(bigModuleProbability.getMin(), bigModuleProbability.getMax());
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
    
    parameters.add(probabilityMapString.set("ProbabilityMap", " "));
    parameters.add(bigProbabilityMapString.set("BigProbabilityMap", " "));
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
            string timestamp = ofGetTimestampString();
            walls[i].save("Render/wall_" + timestamp +".ps");
            ofJson json;
            ofSerialize(json, parameters);
            ofSavePrettyJson("Parameters/params_" + timestamp + ".json", json);
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
        if(ofToLower(ofFilePath::getFileExt(file)) == "png"){
            if(ofStringTimesInString(file, "big") > 0){
                for(auto &wall : walls) wall.bigProbabilityMap.load(file);
                bigProbabilityMapString = file;
            }else{
                for(auto &wall : walls) wall.probabilityMap.load(file);
                probabilityMapString = file;
            }
        }else if(ofToLower(ofFilePath::getFileExt(file)) == "json"){
            ofFile jsonFile(file);
            ofJson json = ofLoadJson(jsonFile);
            ofDeserialize(json, parameters);
            for(auto &wall : walls) wall.bigProbabilityMap.load(bigProbabilityMapString.get());
            for(auto &wall : walls) wall.probabilityMap.load(probabilityMapString.get());
        }
    }
    for(auto &wall : walls) wall.computeNewWall();
}
