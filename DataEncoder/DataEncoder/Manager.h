#pragma once
#include "Header.h"
#include "Image.h"


class Manager
{
	private:	
		int _bit;
		


	public:
		Manager();
		~Manager();

		unsigned long int ReadFile(string path);
		void Decode(string path, unsigned long int count);

};

