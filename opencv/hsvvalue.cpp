//#include <iostream>
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//
//using namespace cv;
//using namespace std;
//
//
//
//int main( int argc, char** argv )
//{
//
//    
//    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
//    
//    int iLowH = 0;
//    int iHighH = 179;
//    
//    int iLowS = 0;
//    int iHighS = 255;
//    
//    int iLowV = 0;
//    int iHighV = 255;
//    
//    
//    //Create trackbars in "Control" window
//    cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
//    cvCreateTrackbar("HighH", "Control", &iHighH, 179);
//    
//    cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
//    cvCreateTrackbar("HighS", "Control", &iHighS, 255);
//    
//    cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
//    cvCreateTrackbar("HighV", "Control", &iHighV, 255);
//    
//    while (true)
//    {
//        Mat imgOriginal;
//        imgOriginal=imread("purple.jpeg");
//        
//        
//        Mat imgHSV;
//        
//        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
//        
//        Mat imgThresholded;
//        Mat opening;
//        Mat closing;
//        
//        resize(imgOriginal, imgThresholded, cv::Size(), 0.1, 0.1);
//        
//        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
//        
//        
//        
//        //morphological opening (remove small objects from the foreground)
//        erode(imgThresholded, opening, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
//        dilate( opening, opening, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
//        
//        //morphological closing (fill small holes in the foreground)
//        dilate( opening, closing, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
//        erode(closing, closing, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
//        
//        imshow("Opening",opening);
//        imshow("Closing",closing);
//        imshow("Thresholded Image", imgThresholded); //show the thresholded image
//        imshow("Original", imgOriginal); //show the original image
//        
//        
//        std::cout << "High Hue" << iHighH;
//        std::cout << "Low Hue" << iLowH<<endl;
//        std::cout << "High Saturation" << iHighS;
//        std::cout << "Low Saturation" << iLowS<<endl;
//        std::cout << "High V" << iHighV;
//        std::cout << "Low V" << iLowV<<endl;
//        
//        
//        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
//        {
//            cout << "esc key is pressed by user" << endl;
//            break;
//        }
//    }
//    
//    return 0;
//    
//}
