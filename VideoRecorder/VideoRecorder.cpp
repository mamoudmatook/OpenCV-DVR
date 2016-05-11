#include "VideoRecorder.h"


VideoRecorder::VideoRecorder()
{
	IsRecording = false;
	IsColored = true;
	IsEqualized = false;
	FrameNumber = 0;

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	Cap.open(1);

	if (!Cap.isOpened()) {
		std::cerr << "Can't read camera feed" << std::endl;
	}

	FrameWidth = Cap.get(CV_CAP_PROP_FRAME_WIDTH);
	FrameHeight = Cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	Ratio = FrameHeight / FrameWidth;
	WindowName = "Video Recorder";
}

VideoRecorder::~VideoRecorder()
{
	Writer.release();
}

std::string VideoRecorder::DateNow() 
{
	char buffer[80];
	time_t rawTime;
	struct tm * timeinfo;
	time(&rawTime);
	timeinfo = localtime(&rawTime);
	strftime(buffer, 80, "%d%m%Y%I%M%S", timeinfo);
	std:: string str(buffer);
	return str;
}

cv::Size VideoRecorder::GetFrameSize()
{
	return cv::Size(FrameWidth, FrameHeight);
}

bool VideoRecorder::SetVideo(std::string filePath, int fcc, int fps, cv::Size frameSize)
{
	Writer = cv::VideoWriter(filePath, fcc, fps, frameSize);

	if (!Writer.isOpened()) 
	{
		std::cerr << "Error opening file for write" << std::endl;
		return false;
	}
	return true;
}

void VideoRecorder::ToGray() 
{
	cv::cvtColor(Buffer, Buffer, CV_BGR2GRAY);
}

void VideoRecorder::Resize()
{
	if (FrameHeight != VideoHeight || FrameWidth != VideoWidth) 
	{
		cv::resize(Buffer, Buffer, cv::Size(VideoWidth, VideoHeight));
	}
}

//Procesa el Buffer y lo manda a Frame
void VideoRecorder::ProcessBuffer() 
{
	if (!Buffer.empty()) {
		cv::putText(Buffer, DateNow(), cv::Point(5, 5), 1, 1, cv::Scalar(255, 255, 255), 2, 7, true);

		Resize();

		if (!IsColored) 
		{
			ToGray();
		}

		if (IsEqualized) 
		{
			if (IsColored) {
				ToGray();
			}
			cv::equalizeHist(Buffer, Buffer);
		}

		Buffer.copyTo(Frame);
	}
}

void VideoRecorder::Capture() 
{
	//Lee al buffer
	if (!Cap.read(Buffer))
	{
		std::cerr << "Error reading frame from camera feed" << std::endl;
	}

	ProcessBuffer();
}

void VideoRecorder::Record()
{
	Writer.write(Frame);
	InMemoryVideo.push_back(Frame);
	cv::putText(Frame, "REC", cv::Point(5, 20), 1, 1, cv::Scalar(0, 0, 255), 2, 7);
}

void VideoRecorder::Play() 
{
	IsRecording = false;
	InMemoryVideo[FrameNumber].copyTo(Frame);
	if (InMemoryVideo.size() > FrameNumber)
	{
		FrameNumber++;
	}
}

void VideoRecorder::Rewind(int x)
{
	IsRecording = false;
	if (FrameNumber > 0) 
	{
		FrameNumber -= 1 * x;
		InMemoryVideo[FrameNumber].copyTo(Frame);
	}
}

void VideoRecorder::FastForward(int x) 
{
	IsRecording = false;
	if (FrameNumber < InMemoryVideo.size()) 
	{
		FrameNumber += 1 * x;
		InMemoryVideo[FrameNumber].copyTo(Frame);
	}
}

void VideoRecorder::ChangeSize(int width, int height) 
{
	VideoWidth = width;
	VideoHeight = height;
}

void VideoRecorder::Show() 
{
	cv::namedWindow(WindowName, CV_WINDOW_AUTOSIZE);
	cv::imshow(WindowName, Frame);
}