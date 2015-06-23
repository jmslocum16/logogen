#ifdef __APPLE__
#include <stdlib.h>
#endif
#include "bitmap.h"

#include <stdio.h>
#include <string.h>
 
// options
int imageWidth = 640;
int imageHeight = 640;

char* outname = NULL;
char* maskname = NULL;
char* blackname = NULL;
char* whitename = NULL;

//writeBMP(outname + ".bmp", windowWidth, windowHeight, imageBuffer);

void printUsage() {
	printf("gradient r1 g1 b1 r2 g2 b2 r3 g3 b3 r4 g4 b4 <output>\n");
	printf("all color values range from 0 to 255");
	printf("mask <mask image> <black image> <white image> <output>\n");
}

 
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	char* arg = argv[1];
	if (!strcmp("gradient", arg)) {
		int i = 1;
		int r1 = atoi(argv[++i]);
		int g1 = atoi(argv[++i]);
		int b1 = atoi(argv[++i]);
		int r2 = atoi(argv[++i]);
		int g2 = atoi(argv[++i]);	
		int b2 = atoi(argv[++i]);
		int r3 = atoi(argv[++i]);
		int g3 = atoi(argv[++i]);
		int b3 = atoi(argv[++i]);
		int r4 = atoi(argv[++i]);
		int g4 = atoi(argv[++i]);
		int b4 = atoi(argv[++i]);
		outname = argv[++i];
		unsigned char* newimage = new unsigned char[3 * imageWidth * imageHeight];
		for (int i = 0; i < imageHeight; i++) {
			float dy = (i + 0.5) / imageHeight;
			for (int j = 0; j < imageWidth; j++) {
				float dx = (j + 0.5) / imageWidth;
				// bilinear interpoation n shit
				newimage[3*(i*imageWidth+j) + 0] = (unsigned char)(r1 * (1-dx)*(1-dy) + r2 *dx*(1-dy) + r3*(1-dx)*dy + r4*dx*dy); 
				newimage[3*(i*imageWidth+j) + 1] = (unsigned char)(g1 * (1-dx)*(1-dy) + g2 *dx*(1-dy) + g3*(1-dx)*dy + g4*dx*dy); 
				newimage[3*(i*imageWidth+j) + 2] = (unsigned char)(b1 * (1-dx)*(1-dy) + b2 *dx*(1-dy) + b3*(1-dx)*dy + b4*dx*dy); 
			}
		}

		
    	char* fname = new char[80];
    	snprintf(fname, 80, "%s.bmp", outname);
		writeBMP(fname, imageWidth, imageHeight, newimage);
		delete newimage;
		delete fname;
	} else if (!strcmp("mask", arg)) {
		maskname = argv[2];
		blackname = argv[3];
		whitename = argv[4];
		outname = argv[5];
		int width, height;
		unsigned char* maskimage = readBMP(maskname, width, height);
		if (width != imageWidth || height != imageHeight) {
			printf("invalid image size\n");
			return 1;
		}
		unsigned char* blackimage = readBMP(blackname, width, height);
		if (width != imageWidth || height != imageHeight) {
			printf("invalid image size\n");
			return 1;
		}
		unsigned char* whiteimage = readBMP(whitename, width, height);
		if (width != imageWidth || height != imageHeight) {
			printf("invalid image size\n");
			return 1;
		}
		for (int i = 0; i < imageHeight; i++) {
			for (int j = 0; j < imageWidth; j++) {
				for (int k = 0; k < 3; k++) {
					float pct = (maskimage[3*(i*imageWidth+j) + k])/255.0;
					maskimage[3*(i*imageWidth+j) + k] = (unsigned char) (pct * whiteimage[3*(i*imageWidth+j)+k] + (1-pct) * blackimage[3*(i*imageWidth+j) + k]);
				}
			}
		}
	
    	char* fname = new char[80];
    	snprintf(fname, 80, "%s.bmp", outname);		

		writeBMP(fname, imageWidth, imageHeight, maskimage);
		delete maskimage;
		delete blackimage;
		delete whiteimage;
		delete fname;
	} else {
		printUsage();
		return 1;	
	}
	return 0;
}
