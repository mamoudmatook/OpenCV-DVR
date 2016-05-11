#include "opencv\highgui.h"
#include "opencv\cv.h"
#include <iostream>
#include "VideoRecorder.h"

using namespace std;
using namespace cv;

int main() 
{
	string filepath = "C:\\users\\david\\";
	string fileExtension = ".avi";
	int fcc = CV_FOURCC('D', 'X', '5', '0');

	VideoRecorder myVideo = VideoRecorder();

	myVideo.SetVideo(filepath, fcc, 20, myVideo.GetFrameSize());

	while (1) 
	{
		myVideo.Capture();

		switch (waitKey(10))
		{
			//Space Rec
		case 32:
			myVideo.IsRecording = !myVideo.IsRecording;
			if (myVideo.IsRecording) 
			{
				myVideo.Record();
			}
			break;
			//Rewind
		case 114:
			myVideo.Rewind();
			break;
			//Forward
		case 102:
			myVideo.FastForward();
			break;
			//play
		case 112:
			myVideo.Play();
			break;
			//new
		case 110:
			
			break;
			//save
		case 115:

			break;
			//esc ape
		case 27:
			return 0;
			break;
		}

		myVideo.Show();
	}
	system("pause");
	return 0;
}