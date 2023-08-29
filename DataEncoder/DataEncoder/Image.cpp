#include "Image.h"


/*
	The constractor of Image
	Input: height and width of the image
	Output: none
*/
Image::Image(int height, int width, int mode)
{
	this->_img = cv::Mat(height, width, CV_8UC3);
	//cv::cvtColor(this->_img, this->_img, cv::COLOR_BGR2RGB);
	this->_point = Point(0, 0);
	this->_width = width;
	this->_height = height;
	this->_mode = mode;	//defult mode

	this->_imgArray = (cv::Mat*)malloc(sizeof(cv::Mat));
	if (this->_imgArray == NULL)
	{
		//error
		cout << "Error!\nProblem with memory allocation" << endl;
		exit(1);
	}
	this->_arraySize = 1;
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

/*
	The function save the image in the given path
	Input: path to save the image to
	Output: none
*/
void Image::exportImage(string path)
{
	//crop the image and save
	///cv::imwrite(path, this->_img(cv::Range(0, this->_point.y + 1), cv::Range(0, this->_width)));

	//save the image
	cv::imwrite(path, this->_img);
}

/*
	The function get pixel number and translate it to vector of int
	Input: pixel num
	Output: vector of int
*/
vector<int> Image::pixelToVector(unsigned long long int pixel_num)
{
	vector<int> result;
	unsigned long long int temp = 0;

	temp = 4294967296;		//256*256*256*256
	result.push_back(pixel_num / temp);
	pixel_num = pixel_num % temp;

	temp = temp / 256;		//256*256*256
	result.push_back(pixel_num / temp);
	pixel_num = pixel_num % temp;

	temp = temp / 256;		//256*256
	result.push_back(pixel_num / temp);
	pixel_num = pixel_num % temp;

	temp = temp / 256;		//256
	result.push_back(pixel_num / temp);
	pixel_num = pixel_num % temp;

	result.push_back(pixel_num);

	return result;
}

/*
	The function get data and add translate it to the image
	Input: string
	Output: none
*/
void Image::dataToImage(string data)
{
	int i;
	//ToDo: check if there are enough space in the image

	//write the data to the image
	for (i = 0; i + 2 < data.size(); i = i + 3)
		setPixle(Vec3b(data[i], data[i + 1], data[i + 2]));

	//add the last pixel
	if (data.size() - i == 1)
		setPixle(Vec3b(data[i], 0, 0));
	else if (data.size() - i == 2)
		setPixle(Vec3b(data[i], data[i + 1], 0));
}

/*
	The function get data and add translate it to the image
	Input: vector of unsigned char
	Output: none
*/
void Image::dataToImage(vector<unsigned char> data)
{
	int i;
	//ToDo: check if there are enough space in the image

	//write the data to the image
	for (i = 0; i + 2 < data.size(); i = i + 3)
		setPixle(Vec3b(data[i], data[i + 1], data[i + 2]));

	//add the last pixel
	if (data.size() - i == 1)
		setPixle(Vec3b(data[i], 0, 0));
	else if (data.size() - i == 2)
		setPixle(Vec3b(data[i], data[i + 1], 0));
}

/*
	The function add imgae to the image array and save the current image to the array
	Input: none
	Output: none
*/
void Image::addImage()			//ToDo: test if work
{
	cv::Mat* temp = NULL;

	this->_imgArray[this->_arraySize - 1] = this->_img;

	temp = (cv::Mat*)realloc(this->_imgArray, sizeof(cv::Mat) * (this->_arraySize + 1));
	if (temp == NULL)
	{
		//error
		cout << "Error!\nProblem with memory reallocation" << endl;
		//free the array
		free(this->_imgArray);
		exit(1);
	}
	this->_imgArray = temp;
	this->_arraySize++;
	//create new image int this->_img
	this->_img = cv::Mat(this->_height, this->_width, CV_8UC3);

	//move the point to the start
	this->_point = Point(0, 0);
}

/*
	The function get the pixel_num that wanted to be added and retun if there are enough space
	Input: number of pixels
	Output: True if there are enough space, else False
*/
bool Image::isEnoughSpace(unsigned long long int pixel_num)
{
	//ToDo: write
	return true;
}

/*
	The function return the number of free pixels to write (with the mode) in the image
*/
unsigned long long int Image::freePixels()
{
	//ToDo: write
	return 0;
}