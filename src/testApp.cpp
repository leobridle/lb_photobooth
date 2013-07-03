#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    
    //CAMERA ======
    dateTime = ofGetTimestampString();
	snapCounter = 0;
	bSnapshot = false;
	phase = 0;
	memset(snapString, 0, 255);		// clear the string by setting all chars to 0
    
    
    
	camWidth 		= 1280 ;	// try to grab at this size.
	camHeight 		= 720   ;
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
   
    
    
    // Timer =====
    bTimerReached = false;
    
    SnapTimerReached = false;
    
    SnapendTime = 5000; // in milliseconds - how long stored image is shown for
    
    

    //movie===================
    
    
    // Uncomment this to show movies with alpha channels
	fingerMovie.setPixelFormat(OF_PIXELS_RGBA);
    
    
    ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
    
    
	fingerMovie.loadMovie("assets/countdownAnim.mov", decodeMode);
    fingerMovie.setFrame(0);
	fingerMovie.stop();
    
    bCountdown = false;
    bShowSnap = false;
    bSnapshot = false;
    SnapTimerReached = false;
    
    frame.setImageType(OF_IMAGE_COLOR_ALPHA);
    frame.loadImage("assets/frameoverlay.png");
    
    //bg.loadImage("backdrop.png");

    enableButton=true;
    
}






//--------------------------------------------------------------
void testApp::update(){
	ofBackground(0, 78, 78);
    
    dateTime = ofGetTimestampString();
    
    vidGrabber.update();
	
	if (vidGrabber.isFrameNew()){
		int totalPixels = camWidth*camHeight*3;
		unsigned char * pixels = vidGrabber.getPixels();

	}
    
    fingerMovie.update();


}


//--------------------------------------------------------------
void testApp::draw(){
    
    //bg.draw(0,0);

    	ofSetHexColor(0xFFFFFF);
        vidGrabber.draw(320,170,camWidth,camHeight);
    
    
	if (bSnapshot == true){
        // grab a rectangle at 200,200, width and height of 300,180
        img.grabScreen(320,170,camWidth,camHeight);
        
        string fileName = "img_"+ofToString(dateTime)+".png";
        img.saveImage(fileName);
        sprintf(snapString, "saved %s", fileName.c_str());
        snapCounter++;
        bSnapshot = false;
	}
    
    
// play and stop movie based on updating bContdown boolean

    if (bCountdown == true){
        //draw the movie in the right place while the countdown is going
        fingerMovie.draw(800, 400);
        fingerMovie.play();
        
	} else {
        
        fingerMovie.draw(-500, -700);
        fingerMovie.stop();
    }
    
    // Writes the name of the last snapshot on the screen
	//ofDrawBitmapString(snapString, 600,460);


    

    
    
// - timer code ================
    
    // update the timer this frame
    float timer = ofGetElapsedTimeMillis() - startTime;
    float timer2 = ofGetElapsedTimeMillis() - SnapstartTime;
    
// Put what happens at the end of the timer in here! ==========
    
    if(timer >= endTime && !bTimerReached) {
        bTimerReached = true;
        cout << "end timer" << endl;
        
        bSnapshot = true;
        
        fingerMovie.play();
        //flash!
        ofRect(320,170,camWidth,camHeight);
        fingerMovie.stop();   
        fingerMovie.setFrame(0);
        
        bCountdown = false;
        
        //timer2
        SnapstartTime = ofGetElapsedTimeMillis();  // get the start time (initiate timer??)
        
                }
    
    // conditions to show or hide stored image based on snapendtime and timer2
    
    if(timer2 >= SnapendTime) {
        //hides saved image
        
        ofSetHexColor(0xFFFFFF);
        img.draw(-2000,-2000,48,27);
        enableButton=true;

    } if (timer2< SnapendTime && snapCounter>1){
        
        //shows saved image
        
       ofSetHexColor(0xFFFFFF);
         img.draw(300,170,camWidth,camHeight);
        enableButton=false;
    
    }

    
    
    

    

    
    // the timer was reached :)
    if(bTimerReached) {
        //ofSetColor(20);
        //ofDrawBitmapString("Timer Reached!", (ofGetWidth()-100)/2, (ofGetHeight()/2)+70);
        //timerComplete(1);
    }
    
//    // some information about the timer
//    string  info  = "FPS:        "+ofToString(ofGetFrameRate(),0)+"\n";
//    info += "Start Time: "+ofToString(startTime, 1)+"\n";
//    info += "End Time:   "+ofToString(endTime/1000.0, 1)+" seconds\n";
//    info += "SnapStart Time: "+ofToString(SnapstartTime, 1)+"\n";
//    info += "SnapEnd Time:   "+ofToString(SnapendTime/1000.0, 1)+" seconds\n";
//    info += "Timer:      "+ofToString(timer/1000.0, 1)+" seconds\n";
//    
//    info += "Timer2:    " +ofToString(timer2);
//    ///ofSetColor(0);
//    ofDrawBitmapString(info, 20, 20);
    
    
    
    
   // draw countdown! ==========
    
    ofEnableAlphaBlending();

    fingerMovie.draw(-400,-200);
    

    //frame
    frame.draw(0, 0,1920,1080);

}



//--------------------------------------------------------------
void testApp::keyPressed  (int key){

    if(key == 'x') {

    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    if(key == ' ' && enableButton==true) {
        bTimerReached = false;                     // reset the timer
        startTime = ofGetElapsedTimeMillis();  // get the start time (initiate timer??)
        endTime = 3000; // in milliseconds
        fingerMovie.setFrame(0);

        bCountdown = true;
    }
}

//--------------------------------------------------------------
void testApp::timerComplete(int num){
// yeah probs don't need this one.

    


}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    cout << "Got the message: " + msg.message << endl;
     
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
