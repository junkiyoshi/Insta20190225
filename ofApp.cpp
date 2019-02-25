#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 650, true, true, true);
}
//--------------------------------------------------------------
void ofApp::update() {

	vector<string> words = { "A", "B", "C", "D", "E", "F" };
	if (ofGetFrameNum() % 60 == 0) {

		this->locations.clear();

		ofFbo fbo;
		fbo.allocate(ofGetWidth(), ofGetHeight());
		fbo.begin();
		ofClear(0);
		ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

		string word = words[(ofGetFrameNum() / 60) % words.size()];
		this->font.drawString(word, this->font.stringWidth(word) * -0.5, this->font.stringHeight(word) * 0.5);

		fbo.end();

		ofPixels pixels;
		fbo.readToPixels(pixels);

		int span = 20;
		for (int x = 0; x < fbo.getWidth(); x += span) {

			for (int y = 0; y < fbo.getHeight(); y += span) {

				if (pixels.getColor(x, y) != ofColor(0, 0)) {

					this->locations.push_back(glm::vec2(x, y));
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	for (auto& location : this->locations) {

		ofDrawCircle(location, ofMap(ofNoise(location.x * 0.003, location.y * 0.003 + ofGetFrameNum() * 0.03), 0, 1, 0, 11));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}