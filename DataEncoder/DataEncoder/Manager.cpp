#include "Manager.h"


Manager::Manager()
{

}
Manager::~Manager()
{

}

unsigned long int Manager::ReadFile(string path)
{
	unsigned long int counter = 0;
	int i;
	//Image img = Image(1080,1920);		//full hd
	Image img = Image(2160, 3840);		//4k

	std::ifstream input(path, std::ios::binary);

	// copies all data into buffer
	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

	for (i = 0; i + 2 < buffer.size(); i = i + 3)
	{		img.setPixle(Vec3b(buffer[i], buffer[i + 1], buffer[i + 2]));
		counter++;
	}

	if (buffer.size() - i == 1)
	{
		img.setPixle(Vec3b(buffer[i], 0, 0));
		counter++;
	}
	else if (buffer.size() - i == 2)
	{
		img.setPixle(Vec3b(buffer[i], buffer[i + 1], 0));
		counter++;
	}

	//ToDo: 2 first pixels use for a. counter b. number of pixels for name
	//ToDo: the next X pixels use for name (dynamic)
	//ToDo: the rest of the data go after

	img.exportImage();

	return counter;
}

void Manager::Decode(string path, unsigned long int count)
{
	/*std::fstream file;
	file.open("test_out.rar", std::ios::out | std::ios::binary);

	//open the image from the path
	cv::Mat img = cv::imread(path);
	Point point = Point(0, 0);

	//convert to rgb
	///cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
	//std::vector<unsigned char> buffer;

	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
		
			for (int k = 0; k < 3;k++)
			{
				file << img.at<Vec3b>(i, j)[k];
				//file.put(img.at<Vec3b>(j,i)[k]);
				//cout << img.at<Vec3b>(i, j) << endl;
			}

		}
	}
	cout << "done" << endl;

	file.close();*/


	//open new file for the data		//ToDo: dynamic file format
	std::fstream file;
	int temp = 0;

	cv::Mat img = cv::imread(path);
	Point point = Point(0, 0);

	file.open("test_out.rar", std::ios::out | std::ios::binary);

	for (int i = 0; i < img.rows; i++)					// <= this->_point.y
	{
		for (int j = 0; j < img.cols; j++)				// < this->_width
		{
			if (count == temp)		//stop at the end of the data (prevent junk data)
				break;

			for (int k = 0; k < 3; k++)		//read the data from the image and create a file
				file << img.at<Vec3b>(i, j)[k];

			temp++;
		}
	}

	//close the file for saving
	file.close();

}