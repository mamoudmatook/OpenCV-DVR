#include "stdafx.h"
#include "VideoRecorder.h"

VideoRecorder::VideoRecorder()
{
	IsColored = true;
	IsEqualized = false;
	FrameNumber = 0;
	Command = Action::eNothing;

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	Cap.open(1);

	if (!Cap.isOpened()) {
		std::cerr << "Can't read camera feed" << std::endl;
	} 
	else
	{
		FrameWidth = Cap.get(CV_CAP_PROP_FRAME_WIDTH);
		FrameHeight = Cap.get(CV_CAP_PROP_FRAME_HEIGHT);
		VideoWidth = FrameWidth;
		VideoHeight = FrameHeight;
		Ratio = FrameHeight / FrameWidth;
		WindowName = "Video Recorder";
	}
}

VideoRecorder::~VideoRecorder()
{
	Writer.release();
}

std::string VideoRecorder::DateNow()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

std::string VideoRecorder::Timestamp()
{
	char buffer[80];
	time_t rawTime;
	struct tm * timeinfo;
	time(&rawTime);
	timeinfo = localtime(&rawTime);
	strftime(buffer, 80, "%d%m%Y%I%M%S", timeinfo);
	std::string str(buffer);
	return str;
}

cv::Size VideoRecorder::GetFrameSize()
{
	return cv::Size(FrameWidth, FrameHeight);
}

bool VideoRecorder::SetVideo(std::string filePath, int fps, int width, int height)
{
	//int fcc = CV_FOURCC('D', 'X', '5', '0');
	int fcc = CV_FOURCC('M', 'J', 'P', 'G');
	Writer = cv::VideoWriter(filePath, fcc, fps, cv::Size(width, height));

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
		Resize();

		cv::putText(Buffer, DateNow(), cv::Point((VideoWidth*0.02), VideoHeight - (VideoHeight * 0.02)), 1, 1, cv::Scalar(255, 255, 255), 2, 7);

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

bool VideoRecorder::Capture()
{
	//Lee al buffer
	if (!Cap.read(Buffer))
	{
		std::cerr << "Error reading frame from camera feed" << std::endl;
		return false;
	}

	ProcessBuffer();
	return true;
}

void VideoRecorder::Record()
{
	Writer.write(Frame);
	InMemoryVideo.push_back(Frame.clone());
	cv::putText(Frame, "REC", cv::Point(5, 20), 1, 1, cv::Scalar(0, 0, 255), 2, 7);
}

void VideoRecorder::Play()
{
	if (FrameNumber >= InMemoryVideo.size())
	{
		FrameNumber = 0;
	}

	InMemoryVideo[FrameNumber].copyTo(Frame);
	if (InMemoryVideo.size() > FrameNumber)
	{
		FrameNumber++;
	}
}

void VideoRecorder::Rewind(int x)
{
	if (FrameNumber > 0)
	{
		FrameNumber -= 1 * x;
		InMemoryVideo[std::max(FrameNumber, 0)].copyTo(Frame);
		cv::putText(Frame, "<<", cv::Point(VideoWidth/2, VideoHeight/2), 1, 3, cv::Scalar(255, 255, 255), 2, 7);
	}
	/*else
	{
	FrameNumber = InMemoryVideo.size();
	}*/
}

void VideoRecorder::FastForward(int x)
{
	if (FrameNumber < InMemoryVideo.size() -1)
	{
		FrameNumber += 1 * x;
		InMemoryVideo[std::min(FrameNumber, (int)InMemoryVideo.size() - 1)].copyTo(Frame);
		cv::putText(Frame, ">>", cv::Point(VideoWidth / 2, VideoHeight / 2), 1, 3, cv::Scalar(255, 255, 255), 2, 7);
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