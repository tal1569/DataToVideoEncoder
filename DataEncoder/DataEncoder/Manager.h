#pragma once
#include "Header.h"
#include "Image.h"


class Manager
{
	private:	
		int _pixelCount;
		

	public:
		Manager();
		~Manager();

		unsigned long long int ReadFile(string path);
		void Decode(string path, unsigned long long int count);
		void testing();

};

