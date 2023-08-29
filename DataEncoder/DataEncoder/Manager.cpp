#include "Manager.h"


Manager::Manager()
{
	this->_pixelCount = 0;
}
Manager::~Manager()
{

}

unsigned long long int Manager::ReadFile(string path)
{
	unsigned long long int pixel_num = 0;
	int i, file_type_size;
	Vec3b first, second;
	string file_type;
	vector<int> pixel_vector;

	//Image img = Image(720,1280,1);		// 720p
	//Image img = Image(1080,1920,1);		//full hd
	Image img = Image(2160, 3840, 1);		//4k

	//ToDo: Add support to multiple images for file

	std::ifstream input(path, std::ios::binary);

	//get file extension (type, .txt, .rar ...)
	file_type = path.substr(path.find_last_of(".") + 1);	//save the type without the dot
	file_type_size = file_type.size();
	if (file_type_size % 3 != 0)
		file_type_size += (3 - file_type_size % 3);

	//get file size
	input.seekg(0, std::ios::end);
	pixel_num = input.tellg();
	input.seekg(0, 0);
	
	if (pixel_num % 3 != 0)
		pixel_num += (3 - pixel_num % 3);
	
	//every pixel hold 3 bytes, this is the number of pixels that we need for the data
	pixel_num = pixel_num / 3;
	

	//add the file "header" to the start
	//2 first pixels use for a. counter b. number of pixels for name (last number in the second pixel)
	//the next X pixels use for name (dynamic)

	pixel_vector = img.pixelToVector(pixel_num);
	first = Vec3b(pixel_vector[0], pixel_vector[1], pixel_vector[2]);
	second = Vec3b(pixel_vector[3], pixel_vector[4], file_type_size);
	
	img.setPixle(first);
	img.setPixle(second);

	//add the file type to the image
	img.dataToImage(file_type);

	// copies all data into buffer
	vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

	/////////////////////ToDo: add option to chose the resulotion, every pixel, two or three

	//add the file data to the image
	img.dataToImage(buffer);

	/*//set the data to the image
	for (i = 0; i + 2 < buffer.size(); i = i + 3)
		img.setPixle(Vec3b(buffer[i], buffer[i + 1], buffer[i + 2]));

	//add the last pixel
	if (buffer.size() - i == 1)
		img.setPixle(Vec3b(buffer[i], 0, 0));
	else if (buffer.size() - i == 2)
		img.setPixle(Vec3b(buffer[i], buffer[i + 1], 0));*/


	//ToDo: dynamic file name for saving
	//save the image
	img.exportImage("./Output/out_file.png");

	return pixel_num;
}

void Manager::Decode(string path, unsigned long long int pixel_num)
{
	//open new file for the data
	std::fstream file;
	unsigned long long int current_pixel = 0;
	Vec3b temp;
	int i, j, k;
	bool flag = false;
	string file_type = "";

	//open the image
	cv::Mat img = cv::imread(path);

	//get the first two pixels
	temp = img.at<Vec3b>(0, 0);
	pixel_num = temp[0] * (256 * 256 * 256 * 256) + temp[1] * (256 * 256 * 256) + temp[2] * (256 * 256);

	temp = img.at<Vec3b>(0, 1);
	pixel_num = pixel_num + temp[0] * (256) + temp[1];
	

	//read the file type
	for (i = 0; i < int(temp[2]) / 3; i++)
		//read the data from the image and write to the file
		for (k = 0; k < 3; k++)
			if (img.at<Vec3b>(0, i + 2)[k] != 0)
				file_type = file_type + char(img.at<Vec3b>(0, i + 2)[k]);

	file.open("./Output/test_out." + file_type, std::ios::out | std::ios::binary);

	for (i = 0; i < img.rows; i++)				
	{
		for (int j = 0; j < img.cols; j++)			
		{
			//stop at the end of the data (prevent junk data)
			if (current_pixel == pixel_num)
				break;

			if (i == 0 && j > 1 + (temp[2] / 3))	//skip the header of the file
				flag = true;

			if (flag)
				//read the data from the image and write to the file
				for (int k = 0; k < 3; k++)		
					file << img.at<Vec3b>(i, j)[k];

			current_pixel++;
		}
	}

	//close the file
	file.close();
}

/*
	Testing function
*/
void Manager::testing()
{
	
}

