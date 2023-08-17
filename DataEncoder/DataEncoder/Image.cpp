#include "Image.h"


/*
	The constractor of Image
	Input: none
	Output: none
*/
Image::Image() { }

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
void Image::setPixle(Point point, Vec3b color)
{
	this->_img.at<Vec3b>(point) = color;
}

