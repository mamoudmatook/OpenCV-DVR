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
	string fileName = "test";
	int fcc = CV_FOURCC('D', 'X', '5', '0');

	VideoRecorder myVideo = VideoRecorder();

	myVideo.SetVideo(filepath+fileName+fileExtension, fcc, 20, myVideo.GetFrameSize());

	while (1) 
	{
		if (myVideo.Command == myVideo.eRecord || myVideo.Command == myVideo.eNothing) {
			myVideo.Capture();
		}

		switch (waitKey(10))
		{
			//Space Rec
		case 32:
			if (myVideo.Command == myVideo.eRecord) {
				myVideo.Command = myVideo.eNothing;
			}
			else{
				myVideo.Command = myVideo.eRecord;
			}
			break;
			//Rewind
		case 114:
			myVideo.Command = myVideo.eRewind;
			break;
			//Forward
		case 102:
			myVideo.Command = myVideo.eForward;
			break;
			//play
		case 112:
			myVideo.Command = myVideo.ePlay;
			break;
			//q
		case 113:
			myVideo.ChangeSize(myVideo.VideoWidth / 2, myVideo.VideoHeight / 2);
			break;
		case 99:
			myVideo.IsColored = !myVideo.IsColored;
			break;
		case 101:
			myVideo.IsEqualized = !myVideo.IsEqualized;
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

		switch (myVideo.Command)
		{
			case myVideo.eRecord:
				myVideo.Record();
			break;
			case myVideo.eRewind:
				myVideo.Rewind();
			break;
			case myVideo.eForward:
				myVideo.FastForward();
			break;
			case myVideo.ePlay:
				myVideo.Play();
			break;
			default:
			break;
		}

		myVideo.Show();
	}
	system("pause");
	return 0;
}