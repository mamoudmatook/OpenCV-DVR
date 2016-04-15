#include "opencv\highgui.h"
#include "opencv\cv.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>

using namespace cv;
using namespace std;

VideoWriter gWriter;
int gFps;
int gVideoHeight;
int gVideoWidth;
double gRatio;
bool gIsRecording;

string dateNow() 
{
	char buffer[80];
	time_t rawTime;
	struct tm * timeinfo;
	time(&rawTime);
	timeinfo = localtime(&rawTime);
	strftime(buffer, 80, "%d%m%Y%I%M%S", timeinfo);
	string str(buffer);
	return str;
}

bool setNewVideo(string filePath, int fcc, int fps, Size frameSize) 
{
	gWriter = VideoWriter(filePath,
		fcc,
		fps,
		frameSize);

	if (!gWriter.isOpened()) {
		cout << "Error: Opening file for write" << endl;
		return false;
	}

	return true;
}
void onChangeWidth(int, void*)
{
	cout << "Width: " << gVideoWidth <<endl;
	//gVideoHeight = gRatio * gVideoWidth;
}

void onChangeHeight(int, void*)
{
	cout << "Height: " << gVideoHeight << endl;
	//gVideoWidth = gRatio * gVideoHeight;
}

void onChangeFps(int, void*)
{
	cout << "FPS: " << gFps << endl;
}
void onClickRec(int, void*)
{
	gIsRecording = true;
	cout << "Recording" << endl;
}
void onClickPause(int, void*)
{
	gIsRecording = false;
	cout << "Paused" << endl;
}
void onClickSave(int, void*)
{

}

int main()
{
	VideoCapture cap(0);
	Mat frame;
	Mat resized;
	IplImage* image;
	gFps = 10;
	gIsRecording = false;

	try {
		
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

		if (!cap.isOpened()) {
			cout << "Error: Video capture" << endl;
			system("pause");
			return -1;
		}

		double frameWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
		double frameHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
		//Size frameSize((int)frameWidth, (int)frameHeight);

		gRatio = frameHeight / frameWidth;
		gVideoHeight = frameHeight;
		gVideoWidth = frameWidth;

		char* windowName = "Video Recorder";
		namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	
		namedWindow("Video Settings", CV_WINDOW_AUTOSIZE);
		createTrackbar("Width", "Video Settings", &gVideoWidth, gVideoWidth, onChangeWidth);
		createTrackbar("Height", "Video Settings", &gVideoHeight, gVideoHeight, onChangeWidth);
		createTrackbar("Fps", "Video Settings", &gFps, 60, onChangeFps);
		//createButton("Rec", onClickRec);
		//createButton("Pause", onClickPause);
		//createButton("Save", onClickSave);
		image = cvCreateImage(cvSize(frameWidth, 10), IPL_DEPTH_8U, 3);
		Mat guiFrame(image);

		while (1) {

			if (!cap.read(frame))
			{
				cout << "Error: Reading frame from camera feed" << endl;
				break;
			}

			resize(frame, resized, Size(gVideoWidth, gVideoHeight));
			imshow(windowName, resized);
			
			imshow("Video Settings", guiFrame);

			switch (waitKey(10))
			{
			case 27:
				return 0;
				break;
			}
		}

		cap.release();
	}
	catch (Exception ex) {
		if (cap.isOpened()) {
			cap.release();
		}
	}

	system("pause");
	return 0;
}