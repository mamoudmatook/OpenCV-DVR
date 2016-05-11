//#include "opencv\highgui.h"
//#include "opencv\cv.h"
//#include <iostream>
//#include <ctime>
//#include <chrono>
//#include <thread>
//
//using namespace cv;
//using namespace std;
//
//VideoCapture gCap(1);
//VideoWriter gWriter;
//int gFps;
//int gVideoHeight;
//int gVideoWidth;
//double gRatio;
//bool gIsRecording;
//
//string dateNow() 
//{
//	char buffer[80];
//	time_t rawTime;
//	struct tm * timeinfo;
//	time(&rawTime);
//	timeinfo = localtime(&rawTime);
//	strftime(buffer, 80, "%d%m%Y%I%M%S", timeinfo);
//	string str(buffer);
//	return str;
//}
//
//bool setNewVideo(string filePath, string fileExtension, int fcc, int fps, Size frameSize) 
//{
//	string filename;
//
//	cout << "Filename: ";
//
//	cin >> filename;
//
//	gWriter = VideoWriter(filePath + filename + dateNow() + fileExtension,
//		fcc,
//		fps,
//		frameSize);
//	if (!gWriter.isOpened()) {
//		cout << "Error: Opening file for write" << endl;
//		return false;
//	}
//
//	return true;
//}
//
//void onChangeWidth(int, void*)
//{
//	if (gVideoWidth < 10) {
//		gVideoWidth = 10;
//	}
//	cout << "Width: " << gVideoWidth <<endl;
//	//gVideoHeight = gRatio * gVideoWidth;
//}
//
//void onChangeHeight(int, void*)
//{
//	if (gVideoHeight < 10) {
//		gVideoHeight = 10;
//	}
//	cout << "Height: " << gVideoHeight << endl;
//	//gVideoWidth = gRatio * gVideoHeight;
//}
//
//void onChangeFps(int, void*)
//{
//	if (gFps < 1) {
//		gFps = 1;
//	}
//	//gCap.set(CV_CAP_PROP_FPS, gFps);
//	cout << "FPS: " << gFps << endl;
//}
//
//int main()
//{
//	//VideoCapture cap(1);
//	Mat frame;
//	Mat resized;
//	IplImage* image;
//	string filepath = "C:\\users\\david\\";
//	string fileExtension = ".avi";
//	int fcc = CV_FOURCC('D', 'X', '5', '0');
//	gIsRecording = false;
//	bool isFirstRun = true;
//
//	try {
//		
//		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//
//		if (!gCap.isOpened()) {
//			cout << "Error: Video capture" << endl;
//			system("pause");
//			return -1;
//		}
//
//		double frameWidth = gCap.get(CV_CAP_PROP_FRAME_WIDTH);
//		double frameHeight = gCap.get(CV_CAP_PROP_FRAME_HEIGHT);
//		gFps = gCap.get(CV_CAP_PROP_FPS);
//		if (gFps == 0) 
//		{
//			gFps = 20;
//		}
//		//Size frameSize((int)frameWidth, (int)frameHeight);
//
//		gRatio = frameHeight / frameWidth;
//		gVideoHeight = frameHeight;
//		gVideoWidth = frameWidth;
//
//		char* windowName = "Video Recorder";
//		namedWindow(windowName, CV_WINDOW_AUTOSIZE);
//	
//		namedWindow("Video Settings", CV_WINDOW_AUTOSIZE);
//		createTrackbar("Width", "Video Settings", &gVideoWidth, gVideoWidth, onChangeWidth);
//		createTrackbar("Height", "Video Settings", &gVideoHeight, gVideoHeight, onChangeWidth);
//		createTrackbar("Fps", "Video Settings", &gFps, 60, onChangeFps);
//		image = cvCreateImage(cvSize(frameWidth, 10), IPL_DEPTH_8U, 3);
//		Mat guiFrame(image);
//
//		while (1) {
//
//			//filename = "VideoCapture" + dateNow();
//
//			if (!gCap.read(frame))
//			{
//				cout << "Error: Reading frame from camera feed" << endl;
//				break;
//			}
//
//			resize(frame, resized, Size(gVideoWidth, gVideoHeight));
//
//			if (gIsRecording) 
//			{
//				gWriter.write(resized);
//				putText(resized, "REC", Point(5, 20), 1, 1, Scalar(0, 0, 255), 2, 7);
//			}
//
//			imshow("Video Settings", guiFrame);
//
//			imshow(windowName, resized);
//			
//			switch (waitKey(10))
//			{
//				//n ew
//				case 110:
//					setNewVideo(filepath,
//						fileExtension,
//						fcc,
//						gFps,
//						Size(gVideoWidth, gVideoHeight));
//				break;
//				//s ave
//				case 115:
//
//				break;
//				//r ec
//				case 114:
//					gIsRecording = !gIsRecording;
//					if (isFirstRun) 
//					{
//						isFirstRun = false;
//						if (!setNewVideo(filepath,
//							fileExtension,
//							fcc,
//							gFps,
//							Size(gVideoWidth, gVideoHeight))) {
//							throw new exception();
//						}
//					}
//				break;
//				//esc ape
//				case 27:
//					return 0;
//				break;
//			}
//		}
//
//		gCap.release();
//	}
//	catch (Exception ex) {
//		if (gCap.isOpened()) {
//			gCap.release();
//		}
//	}
//
//	system("pause");
//	return 0;
//}