#include "Manager.h"


Manager::Manager()
{
	this->_pixelCount = 0;
}
Manager::~Manager()
{

}

unsigned long int Manager::ReadFile(string path)
{
	unsigned long int pixel_num = 0;
	int i;
	//Image img = Image(1080,1920);		//full hd
	Image img = Image(2160, 3840);		//4k

	//ToDo: Add support to multiple images for file

	std::ifstream input(path, std::ios::binary);

	//get file size
	input.seekg(0, std::ios::end);
	pixel_num = input.tellg();
	input.seekg(0, 0);
	
	if (pixel_num % 3 != 0)
		pixel_num += (3 - pixel_num % 3);
	
	//every pixel hold 3 bytes
	pixel_num = pixel_num / 3;


	//ToDo: add the data in the start of the image
	//2 first pixels use for a. counter b. number of pixels for name (last number in the second pixel)
	//the next X pixels use for name (dynamic)


	// copies all data into buffer
	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

	//set the data to the image
	for (i = 0; i + 2 < buffer.size(); i = i + 3)
		img.setPixle(Vec3b(buffer[i], buffer[i + 1], buffer[i + 2]));

	//add the last pixel
	if (buffer.size() - i == 1)
		img.setPixle(Vec3b(buffer[i], 0, 0));
	else if (buffer.size() - i == 2)
		img.setPixle(Vec3b(buffer[i], buffer[i + 1], 0));

	//save the image
	img.exportImage("out_file.png");

	return pixel_num;
}

void Manager::Decode(string path, unsigned long int pixel_num)
{
	//open new file for the data		//ToDo: dynamic file format
	std::fstream file;
	int current_pixel = 0;

	cv::Mat img = cv::imread(path);
	Point point = Point(0, 0);

	file.open("test_out.rar", std::ios::out | std::ios::binary);

	for (int i = 0; i < img.rows; i++)					// <= this->_point.y
	{
		for (int j = 0; j < img.cols; j++)				// < this->_width
		{
			//stop at the end of the data (prevent junk data)
			if (pixel_num == current_pixel)
				break;

			//read the data from the image and write to the file
			for (int k = 0; k < 3; k++)		
				file << img.at<Vec3b>(i, j)[k];

			current_pixel++;
		}
	}

	//close the file for saving
	file.close();
}