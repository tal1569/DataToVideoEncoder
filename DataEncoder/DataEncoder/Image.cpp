#include "Image.h"


/*
	The constractor of Image
	Input: height and width of the image
	Output: none
*/
Image::Image(int height, int width)
{
	this->_img = cv::Mat(height, width, CV_8UC3);
	//cv::cvtColor(this->_img, this->_img, cv::COLOR_BGR2RGB);
	this->_point = Point(0, 0);
	this->_width = width;
	this->_height = height;
}

/*
	The d'tor of Image
	Input: none
	Output: none
*/
Image::~Image() { }

/*
	The function get the color of the pixel in point
	Input: point
	Output: color in the point
*/
Vec3b Image::getPixle(Point point)
{
	return this->_img.at<Vec3b>(point);
}

/*
	The function set the color of the pixel at point
	Input: color and point to update
	Output: none
*/
void Image::setPixle(Vec3b color)
{
	this->_img.at<Vec3b>(this->_point) = color;
	this->_point.x++;
	if (this->_point.x == this->_width)
	{
		this->_point.x = 0;
		this->_point.y++;
	}
}

void Image::exportImage()
{
	/*//convert to rgb
	cout << this->_img.at<Vec3b>(0, 0) << endl;
	cout << this->_img.at<Vec3b>(0, 1) << endl;*/


	//crop the image and save
	cv::imwrite("out_file.png", this->_img(cv::Range(0, this->_point.y + 1), cv::Range(0, this->_width)));
}