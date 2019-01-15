#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <chrono>


using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    
    
    
    
    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

    
    
   
    
//PURPLE HUV value
    
    int purple_iLowH=135;
    int purple_iHighH=144;
    
    int purple_iHighS=246;
    int purple_iLowS=43;
    
    int purple_iHighV=241;
    int purple_iLowV=161;
//BLUE HUV value
    int blue_iLowH=100;
    int blue_iHighH=110;
    
    int blue_iHighS=191;
    int blue_iLowS=60;
    
    int blue_iHighV=255;
    int blue_iLowV=3;
    
    
//Yellow HUV value

    int yellow_iLowH = 15;
    int yellow_iHighH = 35;

    int yellow_iLowS = 190;
    int yellow_iHighS = 255;

    int yellow_iLowV = 190;
    int yellow_iHighV = 255;
    
// GREEN HUV value
    int green_iLowH = 38;
    int green_iHighH = 65;

    int green_iLowS = 80;
    int green_iHighS = 180;

    int green_iLowV = 75;
    int green_iHighV = 250;
    
//RED HUV value
    int red_iLowH = 0;
    int red_iHighH = 18;
    
    int red_iLowS = 100;
    int red_iHighS = 255;
    
    int red_iLowV = 170;
    int red_iHighV = 250;
    
    
    
//default HUV value for trackbar.
    int iLowH = 0;
    int iHighH = 179;
    
    int iLowS = 0;
    int iHighS = 255;
    
    int iLowV = 0;
    int iHighV = 255;
    
    //Create trackbars in "Control" window
    cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    cvCreateTrackbar("HighH", "Control", &iHighH, 179);

    cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);

    cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);
    
    
    //Downloaded image of lighters from web
    //Mat imgOriginal=imread("download.jpeg");
    
    //Image taken by Raspi Cam.
    //Lighters are not the acutal lighters
    //red,blue,green
    //Mat imgOriginal=imread("together.jpg");
    //green image
    //Mat imgOriginal=imread("green.jpg");
    //red image
    //Mat imgOriginal=imread("red2.jpg");
    //blue image
    Mat imgOriginal=imread("purple_blue.jpg");
    while(true){
        
        
    
        Mat resizedImg;
    cv::resize(imgOriginal, resizedImg, cv::Size(), 0.5, 0.5);
    //

        //Record Start
        auto start = std::chrono::high_resolution_clock::now();
        Mat imgHSV;
        
        cvtColor(resizedImg, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
        
        Mat imgThresholded;
        Mat purple_imgThresholded;
        Mat blue_imgThresholded;
        Mat red_imgThresholded;
        Mat green_imgThresholded;
        Mat yellow_imgThresholded;
        
        Mat purple_imgMorphological;
        Mat purple_imgMorphological2;
        
        
        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
        
        //purple
           inRange(imgHSV, Scalar(purple_iLowH, purple_iLowS, purple_iLowV), Scalar(purple_iHighH, purple_iHighS, purple_iHighV), purple_imgThresholded);
        
        //blue
        inRange(imgHSV, Scalar(blue_iLowH, blue_iLowS, blue_iLowV), Scalar(blue_iHighH, blue_iHighS, blue_iHighV), blue_imgThresholded);
        
//        //red
//        inRange(imgHSV, Scalar(red_iLowH, red_iLowS, red_iLowV), Scalar(red_iHighH, red_iHighS, red_iHighV), red_imgThresholded);
//        //green
//        inRange(imgHSV, Scalar(green_iLowH, green_iLowS,green_iLowV), Scalar(green_iHighH, green_iHighS, green_iHighV), green_imgThresholded);
//        //yellow
//        inRange(imgHSV, Scalar(yellow_iLowH, yellow_iLowS, yellow_iLowV), Scalar(yellow_iHighH, yellow_iHighS, yellow_iHighV), yellow_imgThresholded);
    
        //morphological opening (remove small objects from the foreground)
               erode(purple_imgThresholded, purple_imgMorphological, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                dilate( purple_imgMorphological, purple_imgMorphological, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        
                //morphological closing (fill small holes in the foreground)
                dilate( purple_imgMorphological, purple_imgMorphological2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                erode(purple_imgMorphological2, purple_imgMorphological2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        
        
        
        //morphological opening (remove small objects from the foreground)
//        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
//        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
//
//        //morphological closing (fill small holes in the foreground)
//        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
//        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        
        
        
        
        Moments oMoments = moments(imgThresholded);
        Moments purple_oMoments = moments(purple_imgThresholded);
        Moments blue_oMoments = moments(blue_imgThresholded);
         Moments red_oMoments = moments(red_imgThresholded);
         Moments green_oMoments = moments(green_imgThresholded);
         Moments yellow_oMoments = moments(yellow_imgThresholded);
        
        
        
        double dArea = oMoments.m00;
        double purple_dArea = purple_oMoments.m00;
        double blue_dArea = blue_oMoments.m00;
         double red_dArea = red_oMoments.m00;
         double green_dArea = green_oMoments.m00;
         double yellow_dArea = yellow_oMoments.m00;

        if(dArea>100000)
        {
            cout<<"not recognizable"<<endl;
        }
        if(purple_dArea>1000000)
        {
            cout<<"purple"<<endl;
        }
        if(blue_dArea>1000000)
        {
            cout<<"blue"<<endl;
        }
        if(red_dArea>1000000)
        {
            cout<<"red"<<endl;
        }
        if(green_dArea>1000000)
        {
            cout<<"green"<<endl;
        }
        if(yellow_dArea>1000000)
        {
            cout<<"yellow"<<endl;
        }
        
        
        imshow("erodsion", purple_imgMorphological);
        imshow("dilate", purple_imgMorphological2);

        //ThreshHolded Images
        imshow("Thresholded Image", imgThresholded); //show the thresholded image
        
        //purple
        imshow("Purple_Thresholded Image", purple_imgThresholded);
        //blue
        //imshow("Blue_Thresholded Image", blue_imgThresholded);
        //red
        //imshow("Red_Thresholded Image", red_imgThresholded);
        //green
        //imshow("Green_Thresholded Image", green_imgThresholded);
        //yellow
        //imshow("Yellow_Thresholded Image", yellow_imgThresholded);
        
        
        
    imshow("Original", imgOriginal); //show the original image
        
        
        
        //Record End
        auto finish = std::chrono::high_resolution_clock::now();
        //Calculate Time Elapsed per Frame.
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << "Elapsed time: " << elapsed.count() << " s\n";
        std::cout << "High Hue" << iHighH;
        std::cout << "Low Hue" << iLowH;
        std::cout << "High Saturation" << iHighS;
        std::cout << "Low Saturation" << iLowS;
        std::cout << "High V" << iHighV;
        std::cout << "Low V" << iLowV;
        
        
        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }
    
 }
    
}

