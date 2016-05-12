#pragma once

class VideoRecorder
{
public:
	VideoRecorder();
	~VideoRecorder();

	enum Action
	{
		eNothing, eRecord, ePlay, eForward, eRewind, ePause
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
	bool SetVideo(std::string filePath, int fps, int width, int height);
	bool Capture();
	void Show();
	void ChangeSize(int width, int height);
	void ChangeFPS(int fps);
	void Play(bool pause = false);
	void Record();
	void Rewind(int x = 2);
	void FastForward(int x = 2);

	std::string Timestamp();

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