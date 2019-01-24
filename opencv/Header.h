//
//  Header.h
//  opencv
//
//  Created by younghoon kim on 20/01/2019.
//  Copyright © 2019 younghoon kim. All rights reserved.
//
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <chrono>

using namespace cv;
using namespace std;

#ifndef Header_h
#define Header_h


#endif /* Header_h */


//*******Color HUE values
//PURPLE HSV value

int purple_iLowH=142;
int purple_iHighH=159;

int purple_iHighS=255;
int purple_iLowS=91;

int purple_iHighV=182;
int purple_iLowV=69;


//BLUE HUV value
//int blue_iLowH=100;
//int blue_iHighH=107;
//
//int blue_iHighS=255;
//int blue_iLowS=74;
//
//int blue_iHighV=218;
//int blue_iLowV=98;
//BLUE HUV value latter

int blue_iLowH=87;
int blue_iHighH=107;

int blue_iHighS=255;
int blue_iLowS=83;

int blue_iHighV=234;
int blue_iLowV=91;


//Yellow HSV value

int yellow_iLowH = 27;
int yellow_iHighH = 35;

int yellow_iLowS = 153;
int yellow_iHighS = 255;

int yellow_iLowV = 123;
int yellow_iHighV = 223;


// GREEN HSV value
//int green_iLowH = 48;
//int green_iHighH = 60;
//
//int green_iLowS = 76;
//int green_iHighS = 186;
//
//int green_iLowV = 75;
//int green_iHighV = 250;

//Green latter value


int green_iLowH = 46;
int green_iHighH = 66;

int green_iLowS = 86;
int green_iHighS = 231;

int green_iLowV = 95;
int green_iHighV = 231;

//RED HSV value
//int red_iLowH = 0;
//int red_iHighH = 18;
//
//int red_iLowS = 100;
//int red_iHighS = 255;
//
//int red_iLowV = 170;
//int red_iHighV = 250;
//RED HSV value latter
int red_iLowH = 169;
int red_iHighH = 179;

int red_iLowS = 103;
int red_iHighS = 255;

int red_iLowV = 60;
int red_iHighV = 185;

//default HSV value for trackbar.
int iLowH = 0;
int iHighH = 179;

int iLowS = 0;
int iHighS = 255;

int iLowV = 0;
int iHighV = 255;

bool bSuccess;
int color_count[]={0,0,0,0,0};

std::chrono::duration<double> elapsed1;
std::chrono::duration<double> elapsed2;

Mat imgOriginal;
Mat imgThresholded;
Mat resizedImg;
Mat imgHSV;

Mat purple_imgThresholded;
Mat blue_imgThresholded;
Mat red_imgThresholded;
Mat green_imgThresholded;
Mat yellow_imgThresholded;


Mat purple_imgMorphological;
Mat purple_imgMorphological2;


double dArea;
double purple_dArea;
double blue_dArea;
double red_dArea;
double green_dArea;
double yellow_dArea;



void createTrackBar();
void readFromImage(char path[]);
void thresholdImage();
void morphologicalProcess(Mat *imgThresholded,Mat *imgMorphological);
void printHSV();
void colorSegmentation();
void initCount();
void displayColor();
