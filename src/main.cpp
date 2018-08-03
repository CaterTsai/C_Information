#include "ofMain.h"
#include "ofApp.h"
#include "ofProjectionApp.h"

//========================================================================
int main( ){

#ifdef PROJECT_MODE
	ofGLFWWindowSettings settings_;
	//Projection Window
	settings_.width = 1920;
	settings_.height = 1080;
	settings_.setPosition(ofVec2f(1920, 0));
	settings_.resizable = false;
	shared_ptr<ofAppBaseWindow> displaerWindow = ofCreateWindow(settings_);

	//View Window
	settings_.width = 1920;
	settings_.height = 1080;
	settings_.setPosition(ofVec2f(0, 0));
	settings_.shareContextWith = displaerWindow;
	shared_ptr<ofAppBaseWindow> viewWindow = ofCreateWindow(settings_);

	shared_ptr<ofProjectionApp> displayerApp(new ofProjectionApp);
	shared_ptr<ofApp> viewApp(new ofApp);

	ofRunApp(viewWindow, viewApp);
	ofRunApp(displaerWindow, displayerApp);

	ofRunMainLoop();
#else
	ofSetupOpenGL(1920, 1080, OF_WINDOW);			// <-------- setup the GL context
	ofRunApp(new ofApp());
#endif // ProjectionMode

	

}
