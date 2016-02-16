//============================================================================
// Name        : testcascade.cpp
// Author      : Tao Wang
// Version     :
// Copyright   : NICTA
// Description : Hello World in C++, Ansi-style
//============================================================================

/**
 * @file objectDetection.cpp
 * @author A. Huaman ( based in the classic facedetect.cpp in samples/c )
 * @brief A simplified version of facedetect.cpp, show how to load a cascade classifier and how to find objects (Face + eyes) in a video stream
 */
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
//-- Note, either copy these two files from opencv/data/haarscascades to your current folder, or change these locations
String cascade_name = "/home/twang/workspace/traincascade/Debug/classifier/cascade.xml";
CascadeClassifier my_cascade;
string window_name = "Capture - cascade detection";
RNG rng(12345);

/**
 * @function main
 */
int main( int argc, const char** argv )
{
  Mat frame;

  // The following codes call any function from cv.lib before calling cvLoad to avoid error
  //IplImage* image= cvLoadImage("/home/twang/Desktop/1.png");
  //cvErode(image,image,0,3);
  //cvReleaseImage(&image);

  //-- 1. Load the cascades
  if( !my_cascade.load( cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

  //-- 2. Read the image and detect
  frame = imread("/home/twang/dataset/test/image.png");
  //imshow(window_name,frame);
  detectAndDisplay(frame);

  char key = waitKey( 0 );


  return 0;
}

/**
 * @function detectAndDisplay
 */
void detectAndDisplay( Mat frame )
{
   std::vector<Rect> hits;
   Mat frame_gray;

   cvtColor( frame, frame_gray, CV_BGR2GRAY );
   equalizeHist( frame_gray, frame_gray );
   //-- Detect faces
   my_cascade.detectMultiScale( frame_gray, hits, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(15, 15) );

   for( int i = 0; i < hits.size(); i++ )
    {
      //Point center( hits[i].x + hits[i].width*0.5, hits[i].y + hits[i].height*0.5 );
      //ellipse( frame, center, Size( hits[i].width*0.5, hits[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 2, 8, 0 );
	   Point upleft( hits[i].x, hits[i].y);
	   Point lwrite( hits[i].x+hits[i].width, hits[i].y+hits[i].height);
	   rectangle(frame, upleft, lwrite, Scalar(255,0,255), 2, 8, 0);
    }
   //-- Show what you got
   imshow( window_name, frame );
   imwrite("/home/twang/Desktop/1.png", frame);
}
