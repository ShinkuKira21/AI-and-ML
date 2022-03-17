
// reading a text file
#define WIDTH 11
#define HEIGHT 11

#include <iostream>
#include <fstream>
#include <string>

void OpenFile(const char* filename, char* text)
{	
	std::string row;
	std::ifstream file(filename);
	if (file.is_open())
	{
		for(int i = 0; getline(file, row); i++)
			row.copy(&text[WIDTH * i], WIDTH, 0);

		file.close();
	}
	else std::cout << "Unable to open file";

}

void DisplayContent(const char* text)
{	
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			std::cout << text[WIDTH * i + j];
		}
		std::cout << std::endl;
	}
}

void Search(char* text)
{	
	bool bStart = false;
	for(int i = 0; i < HEIGHT; i++)
	{	
		for(int j = 0; j < WIDTH; j++)
		{
			if(text[WIDTH * i + j] == 'S')
			{
				std::cout << "Started|";
				bStart = !bStart;
			}

			if(text[WIDTH * i + j] == 'F')
			{
				std::cout << "Finished\n";
				bStart = !bStart;
			}
				
			if(bStart)
			{	
				if(text[WIDTH * i + j] == '*')
					std::cout << "Wall|";

				if(text[WIDTH * i + j] == ' ')
					std::cout << "Corridor|";

				if(text[WIDTH * i + j] > 64 && text[WIDTH * i + j] < 91 && text[WIDTH * i + j] != 83)
					std::cout << "Object|";
			}
			
		}
	}
}

// parameter search
void Search(char* text, int x, int y)
{
	std::cout << std::endl << text[WIDTH * x + y];
	std::cout << std::endl;
}

int main() {
	char text[WIDTH * HEIGHT];
	
	OpenFile("m1.txt", text);
	DisplayContent(text);
	Search(text);
	Search(text, 1, 1);

	return 0;
}