#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
// image grab ones ----
		int 				snapCounter;
		char 				snapString[255];
		ofImage 			img;
		ofTrueTypeFont		johnston;
		bool 				bSnapshot;		
		float 				phase;
		
        ofVideoGrabber 		vidGrabber;
        unsigned char * 	videoInverted;
        ofTexture			videoTexture;
        int 				camWidth;
        int 				camHeight;
        string              dateTime;
        bool                bShowSnap; //to show last frame
        bool                enableButton;
    
    
// - timer ones
        void                timerComplete(int num);
        float               startTime; // store when we start time timer
        float               endTime; // when do want to stop the timer
        bool                bTimerReached; // used as a trigger when we hit the timer

    
    
// - second timer for showing stored image
        void                SnaptimerComplete(int num);
        float               SnapstartTime; // store when we start time timer
        float               SnapendTime; // when do want to stop the timer
        bool                SnapTimerReached; // used as a trigger when we hit the timer
    
    
// Movie player    
        ofQTKitPlayer		fingerMovie;
        bool                bCountdown;
        bool                snapCountdown;
  
    
//- frame and background images etc
        ofImage             frame;
        //ofImage             bg;
    
    
};

