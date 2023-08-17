#pragma once
#include "Header.h"

class Image
{
	private:
		cv::Mat _img;


	public:
		Image();
		~Image();

		Vec3b getPixle(Point point);
		void setPixle(Point point, Vec3b color);

};

