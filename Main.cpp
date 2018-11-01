#include <stdio.h>
#include "ppm.hpp"

using namespace std;

int main(void)
{
	vector<uint8_t> pixels = vector<uint8_t>();
	size_t img_width, img_height;

	printf("パスを指定> ");
	char path[256];
	scanf_s("%s", path, 256);
	thinks::ppm::readRgbImage(path, &img_width, &img_height, &pixels);

	printf("出力> \n");

	printf("{\n");
	printf("\t{");
	int i = 0;
	for (auto itr = pixels.begin(); itr != pixels.end(); i++)
	{
		if (i!=0&&i%img_width==0)
			printf("},\n\t{");
		uint8_t red = *(itr++);
		uint8_t green = *(itr++);
		uint8_t blue = *(itr++);
		int code = (red & 0xff) << 16 | (green & 0xff) << 8 | (blue & 0xff) << 0;
		printf("0x%06x", code);
		if ((i+1)%img_width != 0)
			printf(", ");
	}
	printf("}\n");
	printf("};\n");

	return 0;
}