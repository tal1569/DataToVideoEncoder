#pragma once
#include "Header.h"

class Image
{
	private:
		cv::Mat _img;
		cv::Mat* _imgArray;
		int _arraySize;
		Point _point;
		int _height;
		int _width;
		int _mode;	//the resulusion of the data. 1 - 1x1 pixels, 2 - 2x2 pixels, 3 - 3x3 pixels

	public:
		Image(int height, int width, int mode);
		~Image();


		vector<int> pixelToVector(unsigned long long int pixel_num);
		Vec3b getPixle(Point point);
		void setPixle(Vec3b color);
		void exportImage(string path);
		void dataToImage(string data);
		void dataToImage(vector<unsigned char> data);
		void addImage();
		bool isEnoughSpace(unsigned long long int pixel_num);
		unsigned long long int freePixels();

};

