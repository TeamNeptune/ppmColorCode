#include <stdio.h>
#include "ppm.hpp"

#include <direct.h>
#include <string>
#include <shlwapi.h>
#pragma comment( lib , "shlwapi.lib" )

using namespace std;

static bool CheckExistenceOfFolder(const std::string folder_name);

static bool CheckExistenceOfFolder(const std::string folder_name)
{
	if (_mkdir(folder_name.c_str()) == 0) {
		return true;
	}
	else {
		return false;
	}
}


int main(void)
{
	vector<uint8_t> pixels = vector<uint8_t>();
	size_t img_width, img_height;

	printf("Input Path> ");
	char path[256];
	scanf_s("%s", path, 256);
	thinks::ppm::readRgbImage(path, &img_width, &img_height, &pixels);

	if (CheckExistenceOfFolder("ColorData"))
	{
		_mkdir("ColorData");
	}

	FILE *fp;
	fopen_s(&fp, "ColorData/data.dat", "w");

	printf("Output Started\n");
	
	printf("{\n");
	fprintf_s(fp, "{\n");
	printf("\t{");
	fprintf_s(fp, "\t{");

	int i = 0;
	for (auto itr = pixels.begin(); itr != pixels.end(); i++)
	{
		if (i != 0 && i%img_width == 0)
		{
			printf("},\n\t{");
			fprintf_s(fp, "},\n\t{");
		}
		uint8_t red = *(itr++);
		uint8_t green = *(itr++);
		uint8_t blue = *(itr++);
		int code = (red & 0xff) << 16 | (green & 0xff) << 8 | (blue & 0xff) << 0;
		printf("0x%06x", code);
		fprintf_s(fp, "0x%06x",code);
		if ((i + 1) % img_width != 0)
		{
			printf(", ");
			fprintf_s(fp, ", ");
		}
	}
	printf("}\n");
	fprintf_s(fp, "}\n");
	printf("};\n");
	fprintf_s(fp, "};\n");

	fclose(fp);

	printf("Output Finished!\n");

	return 0;
}