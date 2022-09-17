#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(3);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	int span = 5;
	ofColor color;

	ofMesh line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	
	for (int hue = 0; hue < 255; hue += 42) {

		color.setHsb(hue, 255, 255);
		auto noise_seed = ofRandom(1000);
		auto scale = ofRandom(0.0005, 0.0035);

		for (int start_x = 30; start_x < ofGetWindowWidth(); start_x += 120) {

			for (int x = start_x; x < start_x + 90; x += span) {

				auto y = ofMap(ofNoise(noise_seed, x * scale + ofGetFrameNum() * 0.01), 0, 1, 100, ofGetWindowHeight() - 100);
				line.addVertex(glm::vec3(x, y, 0));
				line.addColor(color);

				if (x > start_x) {

					line.addIndex(line.getNumVertices() - 1);
					line.addIndex(line.getNumVertices() - 2);
				}
				else {

					ofSetColor(color);
					ofDrawCircle(line.getVertex(line.getNumVertices() - 1), 5);
				}
			}

			ofSetColor(color);
			ofDrawCircle(line.getVertex(line.getNumVertices() - 1), 5);
		}
	}

	line.drawVertices();
	line.drawWireframe();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}