#include "opencv\highgui.h"
#include "opencv\cv.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>

using namespace cv;
using namespace std;

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

int main()
{
	VideoCapture cap(0);
	Mat frame;

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	if (!cap.isOpened()) {
		cout << "Error: Video capture" << endl;
		system("pause");
		return -1;
	}

	char* windowName = "Video Recorder";
	namedWindow(windowName, CV_WINDOW_AUTOSIZE);

	while (1) {

		if (!cap.read(frame))
		{
			cout << "Error: Reading frame from camera feed" << endl;
			system("pause");
			break;
		}

		imshow(windowName, frame);

		switch (waitKey(10))
		{
			case 27:
				return 0;
			break;
		}
	}

	system("pause");
	return 0;
}