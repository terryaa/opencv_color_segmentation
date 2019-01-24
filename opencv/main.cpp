#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <chrono>
#include "Header.h"


using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    VideoCapture cap(0); //capture the video from web cam
    
    auto start1 = std::chrono::high_resolution_clock::now();
    auto start2 = std::chrono::high_resolution_clock::now();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed1;
    std::chrono::duration<double> elapsed2;
    
    
    
    if ( !cap.isOpened() )  // if not success, exit program
    {
        cout << "Cannot open the web cam" << endl;
        return -1;
    }
    
    //Create a trackbar of HSV value.
    //used for gaining HSV value of an image
//    createTrackBar();
//    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
    
    //In case of reading saved image from filesystem.
//    readFromImage("gree.jpeg");
    
   
    
    while(true){
        
       
        
        bSuccess = cap.read(imgOriginal); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }
        
    
        

        //Record Start
        start2 = std::chrono::high_resolution_clock::now();
        
        
        //Raspicam's Image is too big to process.
        //Resizing the captured image to reduce processing time
        resize(imgOriginal, resizedImg, cv::Size(), 0.5, 0.5);
        
        //Convert the captured frame from BGR to HSV
        cvtColor(resizedImg, imgHSV, COLOR_BGR2HSV);
        
    
        
        //cenvert image through a threshold to a prevailing color.
        thresholdImage();
        
        //decide which color's thresholded image has most whitespace.
        colorSegmentation();
        
        
        //Show original image(Cam)
        imshow("Original", imgOriginal);
        imshow("Threshold",imgThresholded);
        imshow("Purple",purple_imgThresholded);
        imshow("Blue",blue_imgThresholded);
        imshow("Red",red_imgThresholded);
        imshow("Green",green_imgThresholded);
        imshow("Yellow",yellow_imgThresholded);
        
        
        
        
        //Record End
        auto finish = std::chrono::high_resolution_clock::now();
        //Calculate Time Elapsed per Frame.
        elapsed2 = finish - start2;
        std::cout << "Elapsed time: " << elapsed2.count() << " s\n";
        
        elapsed1= finish -start1;
        
        if(elapsed1.count()>1.5){
            displayColor();
            initCount();
            cout<<"Elapsed Time:"<<elapsed1.count()<<"s\n";
            start1 = std::chrono::high_resolution_clock::now();
        }
        
        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }
    
 }
    
}

void createTrackBar(){
    //Create trackbars in "Control" window
    cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    cvCreateTrackbar("HighH", "Control", &iHighH, 179);
    
    cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);
    
    cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);
}

void readFromImage(char path[]){
    
    imgOriginal=imread(path);
    
}
void thresholdImage(){
    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
    
    //purple
    inRange(imgHSV, Scalar(purple_iLowH, purple_iLowS, purple_iLowV), Scalar(purple_iHighH, purple_iHighS, purple_iHighV), purple_imgThresholded);
    
    //blue
    inRange(imgHSV, Scalar(blue_iLowH, blue_iLowS, blue_iLowV), Scalar(blue_iHighH, blue_iHighS, blue_iHighV), blue_imgThresholded);
    
    //        //red
    inRange(imgHSV, Scalar(red_iLowH, red_iLowS, red_iLowV), Scalar(red_iHighH, red_iHighS, red_iHighV), red_imgThresholded);
    //        //green
    inRange(imgHSV, Scalar(green_iLowH, green_iLowS,green_iLowV), Scalar(green_iHighH, green_iHighS, green_iHighV), green_imgThresholded);
    //        //yellow
    inRange(imgHSV, Scalar(yellow_iLowH, yellow_iLowS, yellow_iLowV), Scalar(yellow_iHighH, yellow_iHighS, yellow_iHighV), yellow_imgThresholded);
    
}
void morphologicalProcess(Mat *imgThresholded,Mat *imgMorphological){
    //morphological opening (remove small objects from the foreground)
    cv::erode(*imgThresholded, *imgMorphological, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    cv::dilate( *imgThresholded, *imgMorphological, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    
    //morphological closing (fill small holes in the foreground)
    cv::dilate( *imgThresholded, *imgMorphological, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    cv::erode(*imgThresholded, *imgMorphological, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
}

void printHSV(){
    
    std::cout << "High Hue" << iHighH;
    std::cout << "Low Hue" << iLowH;
    std::cout << "High Saturation" << iHighS;
    std::cout << "Low Saturation" << iLowS;
    std::cout << "High V" << iHighV;
    std::cout << "Low V" << iLowV;
    
}

void colorSegmentation(){
    
    dArea = moments(imgThresholded).m00;
    purple_dArea = moments(purple_imgThresholded).m00;
    blue_dArea = moments(blue_imgThresholded).m00;
    red_dArea =moments(red_imgThresholded).m00;
    green_dArea = moments(green_imgThresholded).m00;
    yellow_dArea = moments(yellow_imgThresholded).m00;
    
    
//    if(dArea>10000000)
//    {
//        cout<<"not recognizable"<<endl;
//    }
    if(purple_dArea>10000){
        morphologicalProcess(&purple_imgThresholded,&purple_imgThresholded);
        purple_dArea = moments(purple_imgThresholded).m00;
        if(purple_dArea>10000){
            ++color_count[0];
        }
    }
    
    if(blue_dArea>10000)
    {
        morphologicalProcess(&blue_imgThresholded,&blue_imgThresholded);
        blue_dArea = moments(blue_imgThresholded).m00;
        if(blue_dArea>10000){
            ++color_count[1];
        }
    }
    if(red_dArea>10000)
    {
        morphologicalProcess(&red_imgThresholded,&red_imgThresholded);
        red_dArea =moments(red_imgThresholded).m00;
        if(red_dArea>100000){
            ++color_count[2];
        }
    }
    if(green_dArea>10000)
    {
        morphologicalProcess(&green_imgThresholded,&green_imgThresholded);
        green_dArea = moments(green_imgThresholded).m00;
        if(green_dArea>10000){
            ++color_count[3];
        }
    }
    if(yellow_dArea>10000)
    {
        morphologicalProcess(&yellow_imgThresholded,&yellow_imgThresholded);
        yellow_dArea = moments(yellow_imgThresholded).m00;
        if(yellow_dArea>10000){
            ++color_count[4];
        }
    }
}

void initCount(){
    color_count[0]=0;
     color_count[1]=0;
     color_count[2]=0;
     color_count[3]=0;
     color_count[4]=0;
}

void displayColor(){
    int bestColor;
    color_count[0]>color_count[1] ? bestColor=0 : bestColor=1;
    if( color_count[bestColor]<color_count[2])
        bestColor=2;
    if( color_count[bestColor]<color_count[3])
        bestColor=3;
    if( color_count[bestColor]<color_count[4])
        bestColor=4;
    if(color_count[bestColor]>0)
        switch(bestColor){
        case 0:
            
            cout<<"PURPLE"<<color_count[0]<<endl;
            break;
        case 1:
            cout<<"BLUE"<<endl;
            break;
        case 2:
            cout<<"RED"<<endl;
            break;
        case 3:
            cout<<"GREEN"<<endl;
            break;
        case 4:
            cout<<"YELLOW"<<endl;
            break;
    }
}
