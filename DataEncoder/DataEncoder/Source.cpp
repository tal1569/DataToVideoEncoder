#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/mat.hpp>
#include "iostream"


#include "Header.h"

int showImage() {
	std::string path = "test.png";
	cv::Mat img = cv::imread(path);
	
	//testing - get color in specipic point
	cv::Vec3b color = img.at<cv::Vec3b>(cv::Point(10, 10));

	cout << color << endl;

	//set point with color
	img.at<cv::Vec3b>(cv::Point(100, 100)) = cv::Vec3b('255', '255', '255');

	imshow("Portrait", img);
	cv::waitKey(0);
	return 0;
}


int main(int, char**) {
	showImage();
}