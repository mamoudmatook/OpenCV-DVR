#pragma once
#include "opencv\highgui.h"
#include "opencv\cv.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <algorithm>

class VideoRecorder
{
public:
	VideoRecorder();
	~VideoRecorder();

	enum Action
	{
		eNothing, eRecord, ePlay, eForward, eRewind
	};

	Action Command;
	cv::VideoCapture Cap;
	cv::VideoWriter Writer;
	int FPS;
	int VideoHeight;
	int VideoWidth;
	double Ratio;
	bool IsColored;
	bool IsEqualized;

	cv::Size GetFrameSize();
	bool SetVideo(std::string filePath, int fps, cv::Size frameSize);
	void Capture();
	void Show();
	void ChangeSize(int width, int height);
	void ChangeFPS(int fps);
	void Play();
	void Record();
	void Rewind(int x = 2);
	void FastForward(int x = 2);
	
private:
	void ProcessBuffer();
	void Resize();
	void ToGray();
	void Equalize();
	int FrameNumber;
	std::string DateNow();
	cv::Mat Frame;
	cv::Mat Buffer;
	std::vector<cv::Mat> InMemoryVideo;
	IplImage* Image;
	std::string Filepath;
	std::string FileExtension;
	int FCC;
	double FrameWidth;
	double FrameHeight;
	char* WindowName;
};