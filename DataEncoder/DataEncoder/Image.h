#pragma once
#include "Header.h"

class Image
{
	private:
		cv::Mat _img;
		Point _point;
		int _height;
		int _width;

	public:
		Image(int height, int width);
		~Image();

		Vec3b getPixle(Point point);
		void setPixle(Vec3b color);
		void exportImage(string path);

};

