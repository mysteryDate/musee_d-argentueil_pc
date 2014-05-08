#pragma once

// Calibration variables
// -----------------------------------
// Cropping out kinect data
#define KINECT_CROP_LEFT 	28
#define KINECT_CROP_RIGHT 	10
#define KINECT_CROP_TOP 	14
#define KINECT_CROP_BOTTOM 	27

// Transforming kinect data to fit "real" world
#define INPUT_DATA_ZOOM 2.59
#define INPUT_DATA_DX	154
#define	INPUT_DATA_DY	-36
#define INPUT_DATA_R 	0

// Transforming video data to fit maquette
#define VIDEO_X 32
#define VIDEO_Y -37
#define VIDEO_W 1875
#define VIDEO_H 1048
#define VIDEO_R 0.6

// For the contour finder
#define MIN_CONTOUR_AREA 1000

// Video frame stuff
#define ICE_START 		552
#define ALL_BROKEN 		947
#define ICE_STOP 		1103
#define RIVERS_START 	1150
// -----------------------------------

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxKinect.h"
#include "ArmContourFinder.h"
#include "ofxRipples.h"
#include "ofxBounce.h"
#include "ofxGstStandaloneVideoPlayer.h"
#include <cmath>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void transformInput();
		void fillInRiverRegions();

		void update();
		void updateRipples();
		void updateHands();

		void draw();
		void drawBeavers();
		void drawHandOverlay();
		void drawFeedback();

		void exit();

		void keyPressed(int key);

		// Input Processing
		ofxKinect 			kinect;
		ofVideoPlayer 		videoP;
		ofxGstStandaloneVideoPlayer video;
		ofFbo			frameBuffer;
		cv::Mat 			input;
		cv::Mat 			croppedInput;
		ofxCvGrayscaleImage	kinectImg;
		ofxCvGrayscaleImage kinectBackground;
		int 				nearThreshold;
		int 				farThreshold;
		int 				threshold;

		// Cv
        ArmContourFinder	contourFinder;
        struct Hand
        {
        	ofPolyline line;
        	ofPoint centroid;
        	ofPoint tip;
        	ofPoint end;
        	ofPoint boxCenter;
        	vector< ofPoint > wrists;
        	int index;
        	unsigned int label;
        	ofVec2f velocity;

        	//For sorting by label
        	bool operator < (const Hand& str) const
        	{
        		return (label < str.label);
        	}
        };
        vector< Hand >		hands;

		// Display variables
		int 	lineSmoothing;
		float 	armScaleUp;
		float	smoothingRate;


		// For defining regions
		ofPolyline			waterRegion;
		vector< ofPolyline>	riverRegions;
		const char * 		riverNames[5];


		// For water effect
		ofxRipples	ripples;
		ofxBounce 	bounce;
		ofImage 	riverMask;

		// Calibration
		float x, y, w, h, r;
		int noiseDist;
		// Feedback
		bool bFeedback;

		int PLAY_MODE;

		ofTrueTypeFont myfont;

		

		

};

