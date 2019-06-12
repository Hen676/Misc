#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <thread>
#include <string>
#include "Image.h"

Image readPPM(const char* file);
int readWidth(const char *file);
int readHeight(const char *file);
void outputPPM(const Image &img, const char* file);
Image mean13(const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image);
Image median13(const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image);
Image sClippedMean13(const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image);
Image mean10(const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image);
Image median10(const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image);
Image sClippedMean10(const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image, const Image);


int main()
{
	std::string selection;
	std::cout << "************************************" << std::endl;
	std::cout << "Image Stacker / Image Scaler" << std::endl;
	std::cout << "************************************" << std::endl;
	std::cout << "1:Image Stacker" << std::endl;
	std::cout << "2:Image Scaler" << std::endl;
	std::getline(std::cin,selection);


	if (selection.compare("1") == 0 || selection.compare("Image Stacker") == 0 || selection.compare("Stacker") == 0 || selection.compare("image stacker") == 0 || selection.compare("stacker") == 0)
	{
		system("CLS");

		std::cout << "************************************" << std::endl;
		std::cout << "Amount of Images" << std::endl;
		std::cout << "************************************" << std::endl;
		std::cout << "Images must be loacted in the images folder 'Images / ImageStacker_set1 / IMG_1.ppm'." << std::endl;
		std::cout << "With the names IMG_1.ppm , IMG_2.ppm , IMG_3.ppm , etc." << std::endl;
		std::cout << "1:10" << std::endl;
		std::cout << "2:13" << std::endl;
		std::getline(std::cin, selection);

		//10 images
		if (selection.compare("1") == 0 || selection.compare("10") == 0)
		{
			int w = readWidth("Images/ImageStacker_set1/IMG_1.ppm");
			int h = readHeight("Images/ImageStacker_set1/IMG_1.ppm");
			
			Image *img1 = new Image(w, h);
			Image *img2 = new Image(w, h);
			Image *img3 = new Image(w, h);
			Image *img4 = new Image(w, h);
			Image *img5 = new Image(w, h);
			Image *img6 = new Image(w, h);
			Image *img7 = new Image(w, h);
			Image *img8 = new Image(w, h);
			Image *img9 = new Image(w, h);
			Image *img10 = new Image(w, h);

			*img1 = readPPM("Images/ImageStacker_set1/IMG_1.ppm");
			*img2 = readPPM("Images/ImageStacker_set1/IMG_2.ppm");
			*img3 = readPPM("Images/ImageStacker_set1/IMG_3.ppm");
			*img4 = readPPM("Images/ImageStacker_set1/IMG_4.ppm");
			*img5 = readPPM("Images/ImageStacker_set1/IMG_5.ppm");
			*img6 = readPPM("Images/ImageStacker_set1/IMG_6.ppm");
			*img7 = readPPM("Images/ImageStacker_set1/IMG_7.ppm");
			*img8 = readPPM("Images/ImageStacker_set1/IMG_8.ppm");
			*img9 = readPPM("Images/ImageStacker_set1/IMG_9.ppm");
			*img10 = readPPM("Images/ImageStacker_set1/IMG_10.ppm");

			system("CLS");

			std::cout << "************************************" << std::endl;
			std::cout << "Image Stacker" << std::endl;
			std::cout << "************************************" << std::endl;

			std::cout << "1:Mean" << std::endl;
			std::cout << "2:Median" << std::endl;
			std::cout << "3:Sigma Clipped Mean" << std::endl;
			std::getline(std::cin, selection);
			//mean
			if (selection.compare("1") == 0 || selection.compare("mean") == 0 || selection.compare("Mean") == 0)
			{
				std::string name = "Mean";	std::string zoomT = "None";
				Image *output = new Image(w, h, name, 255, 1, 0, zoomT, 0);

				*output = mean10(*output, *img1, *img2, *img3, *img4, *img5, *img6, *img7, *img8, *img9, *img10);
				//write image
				outputPPM(*output, "MeanPPM.ppm");
			}
			//median
			else if (selection.compare("2") == 0 || selection.compare("median") == 0 || selection.compare("Median") == 0)
			{
				std::string name = "Median";	std::string zoomT = "None";
				Image *output = new Image(w, h, name, 255, 1, 0, zoomT, 0);

				*output = median10(*output, *img1, *img2, *img3, *img4, *img5, *img6, *img7, *img8, *img9, *img10);
				//write image
				outputPPM(*output, "MedianPPM.ppm");
			}
			//Sigma clipped mean
			else if (selection.compare("3") == 0 || selection.compare("Sigma Clipped Mean") == 0 || selection.compare("sigma clipped mean") == 0)
			{
				std::string name = "Sigma_Clipped_Mean";	std::string zoomT = "None";
				Image *output = new Image(w, h, name, 255, 1, 0, zoomT, 0);

				//find mean
				Image *mea = new Image(w, h, 0);

				*mea = mean10(*output, *img1, *img2, *img3, *img4, *img5, *img6, *img7, *img8, *img9, *img10);

				//find median
				Image *med = new Image(w, h, 0);

				*med = median10(*output, *img1, *img2, *img3, *img4, *img5, *img6, *img7, *img8, *img9, *img10);

				//Sigma clipped mean
				std::cout << (float)output->h << std::endl;

				*output = sClippedMean10(*output, *mea, *med, *img1, *img2, *img3, *img4, *img5, *img6, *img7, *img8, *img9, *img10);

				//write image
				outputPPM(*output, "Sigma_clipped_meanPPM.ppm");
			}
			else
			{
				std::cout << selection << ": not vaild input. try 1,2, etc." << std::endl;
			}
		}
		//13 images
		else if (selection.compare("1") == 0 || selection.compare("13") == 0)
		{
			int w = readWidth("Images/ImageStacker_set1/IMG_1.ppm");
			int h = readHeight("Images/ImageStacker_set1/IMG_1.ppm");

			Image *img1 = new Image(w, h);
			Image *img2 = new Image(w, h);
			Image *img3 = new Image(w, h);
			Image *img4 = new Image(w, h);
			Image *img5 = new Image(w, h);
			Image *img6 = new Image(w, h);
			Image *img7 = new Image(w, h);
			Image *img8 = new Image(w, h);
			Image *img9 = new Image(w, h);
			Image *img10 = new Image(w, h);
			Image *img11 = new Image(w, h);
			Image *img12 = new Image(w, h);
			Image *img13 = new Image(w, h);

			*img1 = readPPM("Images/ImageStacker_set1/IMG_1.ppm");
			*img2 = readPPM("Images/ImageStacker_set1/IMG_2.ppm");
			*img3 = readPPM("Images/ImageStacker_set1/IMG_3.ppm");
			*img4 = readPPM("Images/ImageStacker_set1/IMG_4.ppm");
			*img5 = readPPM("Images/ImageStacker_set1/IMG_5.ppm");
			*img6 = readPPM("Images/ImageStacker_set1/IMG_6.ppm");
			*img7 = readPPM("Images/ImageStacker_set1/IMG_7.ppm");
			*img8 = readPPM("Images/ImageStacker_set1/IMG_8.ppm");
			*img9 = readPPM("Images/ImageStacker_set1/IMG_9.ppm");
			*img10 = readPPM("Images/ImageStacker_set1/IMG_10.ppm");
			*img11 = readPPM("Images/ImageStacker_set1/IMG_11.ppm");
			*img12 = readPPM("Images/ImageStacker_set1/IMG_12.ppm");
			*img13 = readPPM("Images/ImageStacker_set1/IMG_13.ppm");

			system("CLS");

			std::cout << "************************************" << std::endl;
			std::cout << "Image Stacker" << std::endl;
			std::cout << "************************************" << std::endl;

			std::cout << "1:Mean" << std::endl;
			std::cout << "2:Median" << std::endl;
			std::cout << "3:Sigma Clipped Mean" << std::endl;
			std::getline(std::cin, selection);
			//mean
			if (selection.compare("1") == 0 || selection.compare("mean") == 0 || selection.compare("Mean") == 0)
			{
				std::string name = "Mean";	std::string zoomT = "None";
				Image *output = new Image(w, h, name, 255, 1, 0, zoomT, 0);

				*output = mean13(*output, *img1, *img2, *img3, *img4, *img5, *img6, *img7, *img8, *img9, *img10, *img11, *img12, *img13);
				//write image
				outputPPM(*output, "MeanPPM.ppm");
			}
			//median
			else if (selection.compare("2") == 0 || selection.compare("median") == 0 || selection.compare("Median") == 0)
			{
				std::string name = "Median";	std::string zoomT = "None";
				Image *output = new Image(w, h, name, 255, 1, 0, zoomT, 0);

				*output = median13(*output, *img1, *img2, *img3, *img4, *img5, *img6, *img7, *img8, *img9, *img10, *img11, *img12, *img13);
				//write image
				outputPPM(*output, "MedianPPM.ppm");
			}
			//Sigma clipped mean
			else if (selection.compare("3") == 0 || selection.compare("Sigma Clipped Mean") == 0 || selection.compare("sigma clipped mean") == 0)
			{
				std::string name = "Sigma_Clipped_Mean";	std::string zoomT = "None";
				Image *output = new Image(w, h, name, 255, 1, 0, zoomT, 0);

				//find mean
				Image *mea = new Image(w, h, 0);

				*mea = mean13(*output, *img1, *img2, *img3, *img4, *img5, *img6, *img7, *img8, *img9, *img10, *img11, *img12, *img13);

				//find median
				Image *med = new Image(w, h, 0);

				*med = median13(*output, *img1, *img2, *img3, *img4, *img5, *img6, *img7, *img8, *img9, *img10, *img11, *img12, *img13);

				//Sigma clipped mean
				std::cout << (float)output->h << std::endl;

				*output = sClippedMean13(*output, *mea, *med, *img1, *img2, *img3, *img4, *img5, *img6, *img7, *img8, *img9, *img10, *img11, *img12, *img13);

				//write image
				outputPPM(*output, "Sigma_clipped_meanPPM.ppm");
			}
			else
			{
				std::cout << selection << ": not vaild input. try 1,2, etc." << std::endl;
			}
		}
		else
		{
			std::cout << selection << ": not vaild input. try 1,2, etc." << std::endl;
		}
	}
	else if (selection.compare("2") == 0 || selection.compare("Image Scaler") == 0 || selection.compare("Scaler") == 0 || selection.compare("image scaler") == 0 || selection.compare("scaler") == 0)
	{
		
		system("CLS");

		std::cout << "************************************" << std::endl;
		std::cout << "Image Scaler" << std::endl;
		std::cout << "************************************" << std::endl;
		std::cout << "Image must be loacted in the image folder 'Images / Zoom / zIMG_1.ppm'." << std::endl;
		std::cout << "1:Nearist Neighbour x2" << std::endl;
		std::cout << "2:Nearist Neighbour x4" << std::endl;
		std::cout << "3:linear x2" << std::endl;
		std::cout << "4:linear x4" << std::endl;
		std::getline(std::cin, selection);

		//nearist neighbour x2
		if (selection.compare("1") == 0 )
		{
			int w = readWidth("Images/Zoom/zIMG_1.ppm");
			int h = readHeight("Images/Zoom/zIMG_1.ppm");

			//base image
			std::string name = "Nearist_Neighbour_x2";	std::string zoomT = "Nearist_Neighbour";
			Image *temp = new Image(w, h, 255, 1, 2, name, zoomT);
			*temp = readPPM("Images/Zoom/zIMG_1.ppm");

			//output image
			Image *output = new Image((w * 2), (h * 2), name, 255, 1, 2, zoomT, 0);

			//zoom by nearist neighbour
			neighbour neig;
			*output = neig.zoom(*temp);

			outputPPM(*output, "Nearist_Neighbour_x2.ppm");
			//write image
		}
		//nearist neighbour x4
		else if (selection.compare("2") == 0 )
		{
			int w = readWidth("Images/Zoom/zIMG_1.ppm");
			int h = readHeight("Images/Zoom/zIMG_1.ppm");

			//base image
			std::string name = "Nearist_Neighbour_x4";	std::string zoomT = "Nearist_Neighbour";
			Image *temp = new Image(w, h, 255, 1, 4, name, zoomT);
			*temp = readPPM("Images/Zoom/zIMG_1.ppm");

			//output image
			Image *output1 = new Image((w * 2), (h * 2), name, 255, 1, 4, zoomT, 0);
			Image *output2 = new Image((w * 4), (h * 4), name, 255, 1, 4, zoomT, 0);

			//zoom by nearist neighbour
			neighbour neig;
			*output1 = neig.zoom(*temp);
			*output2 = neig.zoom(*output1);

			//write image
			outputPPM(*output2, "Nearist_Neighbour_x4.ppm");
		}
		//bilinear x2
		else if (selection.compare("3") == 0 )
		{
			int w = readWidth("Images/Zoom/zIMG_1.ppm");
			int h = readHeight("Images/Zoom/zIMG_1.ppm");

			//base image
			std::string name = "Bilinear_x2";	std::string zoomT = "Bilinear";
			Image *temp = new Image(w, h, 255, 1, 2, name, zoomT);
			*temp = readPPM("Images/Zoom/zIMG_1.ppm");

			//output image
			Image *output = new Image((w * 2), (h * 2), name, 255, 1, 2, zoomT, 0);

			//zoom by nearist neighbour
			bilinear bili;
			*output = bili.zoom(*temp);

			//write image
			outputPPM(*output, "Bilinear_x2.ppm");
		}
		//bilinear x4
		else if (selection.compare("4") == 0 )
		{
			int w = readWidth("Images/Zoom/zIMG_1.ppm");
			int h = readHeight("Images/Zoom/zIMG_1.ppm");

			//base image
			std::string name = "Bilinear_x4";	std::string zoomT = "Bilinear";
			Image *temp = new Image(w, h, 255, 1, 4, name, zoomT);
			*temp = readPPM("Images/Zoom/zIMG_1.ppm");

			//output image
			Image *output1 = new Image((w * 2), (h * 2), name, 255, 1, 4, zoomT, 0);
			Image *output2 = new Image((w * 4), (h * 4), name, 255, 1, 4, zoomT, 0);

			//zoom by nearist neighbour
			bilinear bili;
			*output1 = bili.zoom(*temp);
			*output2 = bili.zoom(*output1);

			//write image
			outputPPM(*output2, "Bilinear_x4.ppm");
		}
		else
		{
			std::cout << selection << ": not vaild input. try 1,2, etc." << std::endl;
		}
	}
	else
	{
		std::cout << selection << ": not vaild input. try 1,2, etc." << std::endl;
	}
	return 0;
}

//Read ppm files into the code
Image readPPM(const char *filename)
{
	std::cout << "Loading:" << filename << std::endl;
	std::ifstream ifs;
	ifs.open(filename, std::ios::binary);
	Image src;
	try {
		if (ifs.fail()) {
			throw("Can't open the input file - is it named correctly/is it in the right directory?");
		}
		std::string header;
		int w, h, b;
		ifs >> header;
		if (strcmp(header.c_str(), "P6") != 0) throw("Can't read the input file - is it in binary format (Has P6 in the header)?");
		ifs >> w >> h >> b;
		src.w = w;
		src.h = h;
		src.colour = b;
		src.pixels = new Image::Rgb[w * h]; // this is throw an exception if bad_alloc 
		ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data 
		unsigned char pix[3]; // read each pixel one by one and convert bytes to floats 
		for (int i = 0; i < w * h; ++i) {
			ifs.read(reinterpret_cast<char *>(pix), 3);
			src.pixels[i].r = pix[0];
			src.pixels[i].g = pix[1];
			src.pixels[i].b = pix[2];
		}
		ifs.close();
	}
	catch (const char *err) {
		fprintf(stderr, "%s\n", err);
		ifs.close();
	}
	return src;
}

//get width of image
int readWidth(const char *filename)
{
	std::ifstream ifs;
	ifs.open(filename, std::ios::binary);
	int w, h, b;
	try {
		if (ifs.fail())
		{
			throw("Can't open the input file - is it named correctly/is it in the right directory?");
		}
		std::string header;
		ifs >> header;
		if (strcmp(header.c_str(), "P6") != 0) throw("Can't read the input file - is it in binary format (Has P6 in the header)?");
		ifs >> w >> h >> b;
		}
	catch (const char *err) {
		fprintf(stderr, "%s\n", err);
		ifs.close();
	}
	return w;
}

//get height of image
int readHeight(const char *filename)
{
	std::ifstream ifs;
	ifs.open(filename, std::ios::binary);
	int w, h, b;
	try {
		if (ifs.fail())
		{
			throw("Can't open the input file - is it named correctly/is it in the right directory?");
		}
		std::string header;
		ifs >> header;
		if (strcmp(header.c_str(), "P6") != 0) throw("Can't read the input file - is it in binary format (Has P6 in the header)?");
		ifs >> w >> h >> b;
	}
	catch (const char *err) {
		fprintf(stderr, "%s\n", err);
		ifs.close();
	}
	return h;
}

//Mean, Median and Sigma for 13 images
//Find Mean
Image mean13(const Image output, const Image img1 , const Image img2 , const Image img3 , const Image img4 , const Image img5, const Image img6, const Image img7, const Image img8, const Image img9, const Image img10, const Image img11, const Image img12, const Image img13)
{
	std::cout << "Starting Mean" << std::endl;
	//get pixel amount
	int pi = img1.w * img1.h;
	//find mean for RGB and set values
	for (int i = 0; i < pi; ++i)
	{
		output.pixels[i].r = (img1.pixels[i].r + img2.pixels[i].r + img3.pixels[i].r + img4.pixels[i].r + img5.pixels[i].r + img6.pixels[i].r + img7.pixels[i].r + img8.pixels[i].r + img9.pixels[i].r + img10.pixels[i].r + img11.pixels[i].r + img12.pixels[i].r + img13.pixels[i].r) / 13;
		output.pixels[i].g = (img1.pixels[i].g + img2.pixels[i].g + img3.pixels[i].g + img4.pixels[i].g + img5.pixels[i].g + img6.pixels[i].g + img7.pixels[i].g + img8.pixels[i].g + img9.pixels[i].g + img10.pixels[i].g + img11.pixels[i].g + img12.pixels[i].g + img13.pixels[i].g) / 13;
		output.pixels[i].b = (img1.pixels[i].b + img2.pixels[i].b + img3.pixels[i].b + img4.pixels[i].b + img5.pixels[i].b + img6.pixels[i].b + img7.pixels[i].b + img8.pixels[i].b + img9.pixels[i].b + img10.pixels[i].b + img11.pixels[i].b + img12.pixels[i].b + img13.pixels[i].b) / 13;
	}
	std::cout << "Finished Mean" << std::endl;
	return output;
}

//Find Median
Image median13(const Image output, const Image img1, const Image img2, const Image img3, const Image img4, const Image img5, const Image img6, const Image img7, const Image img8, const Image img9, const Image img10, const Image img11, const Image img12, const Image img13)
{
	std::cout << "Starting Median" << std::endl;
	//get pixel amount
	int pi = img1.w * img1.h;
	//find mean for RGB and set values
	for (int i = 0; i < (pi); ++i)
	{
		//char array of pixels
		unsigned char r[] = { img1.pixels[i].r, img2.pixels[i].r, img3.pixels[i].r, img4.pixels[i].r, img5.pixels[i].r, img6.pixels[i].r, img7.pixels[i].r, img8.pixels[i].r, img9.pixels[i].r, img10.pixels[i].r, img11.pixels[i].r, img12.pixels[i].r, img13.pixels[i].r };
		unsigned char g[] = { img1.pixels[i].g, img2.pixels[i].g, img3.pixels[i].g, img4.pixels[i].g, img5.pixels[i].g, img6.pixels[i].g, img7.pixels[i].g, img8.pixels[i].g, img9.pixels[i].g, img10.pixels[i].g, img11.pixels[i].g, img12.pixels[i].g, img13.pixels[i].g };
		unsigned char b[] = { img1.pixels[i].b, img2.pixels[i].b, img3.pixels[i].b, img4.pixels[i].b, img5.pixels[i].b, img6.pixels[i].b, img7.pixels[i].b, img8.pixels[i].b, img9.pixels[i].b, img10.pixels[i].b, img11.pixels[i].b, img12.pixels[i].b, img13.pixels[i].b };
		//set as a vectoer
		std::vector<unsigned char> redVector(r, r + 13);
		std::vector<unsigned char> greenVector(g, g + 13);
		std::vector<unsigned char> blueVector(b, b + 13);
		//sort vector
		std::sort(redVector.begin(), redVector.end());
		std::sort(greenVector.begin(), greenVector.end());
		std::sort(blueVector.begin(), blueVector.end());
		//set values
		output.pixels[i].r = redVector[7];
		output.pixels[i].g = greenVector[7];
		output.pixels[i].b = blueVector[7];
	}

	std::cout << "Finished Median" << std::endl;
	return output;
}

//Find Sigma Clipped Mean
Image sClippedMean13(const Image output, const Image mea, const Image med, const Image img1, const Image img2, const Image img3, const Image img4, const Image img5, const Image img6, const Image img7, const Image img8, const Image img9, const Image img10, const Image img11, const Image img12, const Image img13)
{
	std::cout << "Starting Sigma Clipped Mean" << std::endl;
	//get pixel amount
	int pi = img1.w * img1.h;
	int varible = 0;
	unsigned char pix = 0;
	float temp = 0;
	//find mean for RGB and set values
	for (int z = 0; z < 10; ++z)
	{
		
		
		for (int i = 0; i < pi; ++i)
		{
			//old standard deviation
			float redOld = 256;
			float greenOld = 256;
			float blueOld = 256;

			float red = (
				  (pow((img1.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img2.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img3.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img4.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img5.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img6.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img7.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img8.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img9.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img10.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img11.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img12.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img13.pixels[i].r - mea.pixels[i].r), 2)) / 13);
			float green = (
				  (pow((img1.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img2.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img3.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img4.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img5.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img6.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img7.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img8.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img9.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img10.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img11.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img12.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img13.pixels[i].g - mea.pixels[i].g), 2)) / 13);
			float blue = (
				  (pow((img1.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img2.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img3.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img4.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img5.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img6.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img7.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img8.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img9.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img10.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img11.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img12.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img13.pixels[i].b - mea.pixels[i].b), 2)) / 13);
			//Square Root
			red = pow(red, 0.5);
			green = pow(green, 0.5);
			blue = pow(blue, 0.5);

			//red values
			if (redOld >= red)
			{
				int pixAmount = 0;

				float minus = med.pixels[i].r - red;
				float add = med.pixels[i].r + red;
				temp = 0;

				if (add >= img1.pixels[i].r && minus <= img1.pixels[i].r)
				{
					temp = temp + img1.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				if (add >= img2.pixels[i].r && minus <= img2.pixels[i].r)
				{
					temp = temp + img2.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				if (add >= img3.pixels[i].r && minus <= img3.pixels[i].r)
				{
					temp = temp + img3.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				if (add >= img4.pixels[i].r && minus <= img4.pixels[i].r)
				{
					temp = temp + img4.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				if (add >= img5.pixels[i].r && minus <= img5.pixels[i].r)
				{
					temp = temp + img5.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				if (add >= img6.pixels[i].r && minus <= img6.pixels[i].r)
				{
					temp = temp + img6.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				if (add >= img7.pixels[i].r && minus <= img7.pixels[i].r)
				{
					temp = temp + img7.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				if (add >= img8.pixels[i].r && minus <= img8.pixels[i].r)
				{
					temp = temp + img8.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				if (add >= img9.pixels[i].r && minus <= img9.pixels[i].r)
				{
					temp = temp + img9.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				if (add >= img10.pixels[i].r && minus <= img10.pixels[i].r)
				{
					temp = temp + img10.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				if (add >= img11.pixels[i].r && minus <= img11.pixels[i].r)
				{
					temp = temp + img11.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				if (add >= img12.pixels[i].r && minus <= img12.pixels[i].r)
				{
					temp = temp + img12.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				if (add >= img13.pixels[i].r && minus <= img13.pixels[i].r)
				{
					temp = temp + img13.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				//red devide
				output.pixels[i].r = temp / pixAmount;
			}
			//green values
			if (blueOld >= blue)
			{
				int pixAmount = 0;

				float minus = med.pixels[i].g - green;
				float add = med.pixels[i].g + green;
				temp = 0;

				if (add >= img1.pixels[i].g && minus <= img1.pixels[i].g)
				{
					temp = temp + img1.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				if (add >= img2.pixels[i].g && minus <= img2.pixels[i].g)
				{
					temp = temp + img2.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				if (add >= img3.pixels[i].g && minus <= img3.pixels[i].g)
				{
					temp = temp + img3.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				if (add >= img4.pixels[i].g && minus <= img4.pixels[i].g)
				{
					temp = temp + img4.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				if (add >= img5.pixels[i].g && minus <= img5.pixels[i].g)
				{
					temp = temp + img5.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				if (add >= img6.pixels[i].g && minus <= img6.pixels[i].g)
				{
					temp = temp + img6.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				if (add >= img7.pixels[i].g && minus <= img7.pixels[i].g)
				{
					temp = temp + img7.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				if (add >= img8.pixels[i].g && minus <= img8.pixels[i].g)
				{
					temp = temp + img8.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				if (add >= img9.pixels[i].g && minus <= img9.pixels[i].g)
				{
					temp = temp + img9.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				if (add >= img10.pixels[i].g && minus <= img10.pixels[i].g)
				{
					temp = temp + img10.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				if (add >= img11.pixels[i].g && minus <= img11.pixels[i].g)
				{
					temp = temp + img11.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				if (add >= img12.pixels[i].g && minus <= img12.pixels[i].g)
				{
					temp = temp + img12.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				if (add >= img13.pixels[i].g && minus <= img13.pixels[i].g)
				{
					temp = temp + img13.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				//green devide
				output.pixels[i].g = temp / pixAmount;
			}
			//blue values
			if (blueOld >= blue)
			{
				int pixAmount = 0;

				float minus = med.pixels[i].b - blue;
				float add = med.pixels[i].b + blue;
				temp = 0;

				if (add >= img1.pixels[i].b && minus <= img1.pixels[i].b)
				{
					temp = temp + img1.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				if (add >= img2.pixels[i].b && minus <= img2.pixels[i].b)
				{
					temp = temp + img2.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				if (add >= img3.pixels[i].b && minus <= img3.pixels[i].b)
				{
					temp = temp + img3.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				if (add >= img4.pixels[i].b && minus <= img4.pixels[i].b)
				{
					temp = temp + img4.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				if (add >= img5.pixels[i].b && minus <= img5.pixels[i].b)
				{
					temp = temp + img5.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				if (add >= img6.pixels[i].b && minus <= img6.pixels[i].b)
				{
					temp = temp + img6.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				if (add >= img7.pixels[i].b && minus <= img7.pixels[i].b)
				{
					temp = temp + img7.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				if (add >= img8.pixels[i].b && minus <= img8.pixels[i].b)
				{
					temp = temp + img8.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				if (add >= img9.pixels[i].b && minus <= img9.pixels[i].b)
				{
					temp = temp + img9.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				if (add >= img10.pixels[i].b && minus <= img10.pixels[i].b)
				{
					temp = temp + img10.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				if (add >= img11.pixels[i].b && minus <= img11.pixels[i].b)
				{
					temp = temp + img11.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				if (add >= img12.pixels[i].b && minus <= img12.pixels[i].b)
				{
					temp = temp + img12.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				if (add >= img13.pixels[i].b && minus <= img13.pixels[i].b)
				{
					temp = temp + img13.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				output.pixels[i].b = temp / pixAmount;
			}

			redOld = red;
			greenOld = green;
			blueOld = blue;

			if (redOld >= red && greenOld >= green && blueOld >= blue)
			{
				varible = varible + 1;
			}
		}
		if (varible == pi)
		{
			z = 10;
		}
	}

	std::cout << "Finished Sigma Clipped Mean" << std::endl;
	return output;
}

//Mean, Median and Sigma for 10 images
//Find Mean
Image mean10(const Image output, const Image img1, const Image img2, const Image img3, const Image img4, const Image img5, const Image img6, const Image img7, const Image img8, const Image img9, const Image img10)
{
	std::cout << "Starting Mean" << std::endl;
	//get pixel amount
	int pi = img1.w * img1.h;
	//find mean for RGB and set values
	for (int i = 0; i < pi; ++i)
	{
		output.pixels[i].r = (img1.pixels[i].r + img2.pixels[i].r + img3.pixels[i].r + img4.pixels[i].r + img5.pixels[i].r + img6.pixels[i].r + img7.pixels[i].r + img8.pixels[i].r + img9.pixels[i].r + img10.pixels[i].r) / 10;
		output.pixels[i].g = (img1.pixels[i].g + img2.pixels[i].g + img3.pixels[i].g + img4.pixels[i].g + img5.pixels[i].g + img6.pixels[i].g + img7.pixels[i].g + img8.pixels[i].g + img9.pixels[i].g + img10.pixels[i].g) / 10;
		output.pixels[i].b = (img1.pixels[i].b + img2.pixels[i].b + img3.pixels[i].b + img4.pixels[i].b + img5.pixels[i].b + img6.pixels[i].b + img7.pixels[i].b + img8.pixels[i].b + img9.pixels[i].b + img10.pixels[i].b) / 10;
	}
	std::cout << "Finished Mean" << std::endl;
	return output;
}

//Find Median
Image median10(const Image output, const Image img1, const Image img2, const Image img3, const Image img4, const Image img5, const Image img6, const Image img7, const Image img8, const Image img9, const Image img10)
{
	std::cout << "Starting Median" << std::endl;
	//get pixel amount
	int pi = img1.w * img1.h;
	//find mean for RGB and set values
	for (int i = 0; i < (pi); ++i)
	{
		//char array of pixels
		unsigned char r[] = { img1.pixels[i].r, img2.pixels[i].r, img3.pixels[i].r, img4.pixels[i].r, img5.pixels[i].r, img6.pixels[i].r, img7.pixels[i].r, img8.pixels[i].r, img9.pixels[i].r, img10.pixels[i].r};
		unsigned char g[] = { img1.pixels[i].g, img2.pixels[i].g, img3.pixels[i].g, img4.pixels[i].g, img5.pixels[i].g, img6.pixels[i].g, img7.pixels[i].g, img8.pixels[i].g, img9.pixels[i].g, img10.pixels[i].g};
		unsigned char b[] = { img1.pixels[i].b, img2.pixels[i].b, img3.pixels[i].b, img4.pixels[i].b, img5.pixels[i].b, img6.pixels[i].b, img7.pixels[i].b, img8.pixels[i].b, img9.pixels[i].b, img10.pixels[i].b};
		//set as a vectoer
		std::vector<unsigned char> redVector(r, r + 10);
		std::vector<unsigned char> greenVector(g, g + 10);
		std::vector<unsigned char> blueVector(b, b + 10);
		//sort vector
		std::sort(redVector.begin(), redVector.end());
		std::sort(greenVector.begin(), greenVector.end());
		std::sort(blueVector.begin(), blueVector.end());
		//set values
		output.pixels[i].r = (redVector[5] + redVector[6]) / 2;
		output.pixels[i].g = (greenVector[5] + redVector[6]) / 2;
		output.pixels[i].b = (blueVector[5] + redVector[6]) / 2;
	}

	std::cout << "Finished Median" << std::endl;
	return output;
}

//Find Sigma Clipped Mean
Image sClippedMean10(const Image output, const Image mea, const Image med, const Image img1, const Image img2, const Image img3, const Image img4, const Image img5, const Image img6, const Image img7, const Image img8, const Image img9, const Image img10)
{
	std::cout << "Starting Sigma Clipped Mean" << std::endl;
	//get pixel amount
	int pi = img1.w * img1.h;
	int varible = 0;
	unsigned char pix = 0;
	float temp = 0;
	//find mean for RGB and set values
	for (int z = 0; z < 10; ++z)
	{


		for (int i = 0; i < pi; ++i)
		{
			//old standard deviation
			float redOld = 256;
			float greenOld = 256;
			float blueOld = 256;

			float red = (
				(pow((img1.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img2.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img3.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img4.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img5.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img6.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img7.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img8.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img9.pixels[i].r - mea.pixels[i].r), 2))
				+ (pow((img10.pixels[i].r - mea.pixels[i].r), 2)) / 10);
			float green = (
				(pow((img1.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img2.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img3.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img4.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img5.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img6.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img7.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img8.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img9.pixels[i].g - mea.pixels[i].g), 2))
				+ (pow((img10.pixels[i].g - mea.pixels[i].g), 2)) / 10);
			float blue = (
				(pow((img1.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img2.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img3.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img4.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img5.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img6.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img7.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img8.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img9.pixels[i].b - mea.pixels[i].b), 2))
				+ (pow((img10.pixels[i].b - mea.pixels[i].b), 2)) / 10);
			//Square Root
			red = pow(red, 0.5);
			green = pow(green, 0.5);
			blue = pow(blue, 0.5);

			//red values
			if (redOld >= red)
			{
				int pixAmount = 0;

				float minus = med.pixels[i].r - red;
				float add = med.pixels[i].r + red;
				temp = 0;

				if (add >= img1.pixels[i].r && minus <= img1.pixels[i].r)
				{
					temp = temp + img1.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img2.pixels[i].r && minus <= img2.pixels[i].r)
				{
					temp = temp + img2.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img3.pixels[i].r && minus <= img3.pixels[i].r)
				{
					temp = temp + img3.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img4.pixels[i].r && minus <= img4.pixels[i].r)
				{
					temp = temp + img4.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img5.pixels[i].r && minus <= img5.pixels[i].r)
				{
					temp = temp + img5.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img6.pixels[i].r && minus <= img6.pixels[i].r)
				{
					temp = temp + img6.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img7.pixels[i].r && minus <= img7.pixels[i].r)
				{
					temp = temp + img7.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img8.pixels[i].r && minus <= img8.pixels[i].r)
				{
					temp = temp + img8.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img9.pixels[i].r && minus <= img9.pixels[i].r)
				{
					temp = temp + img9.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img10.pixels[i].r && minus <= img10.pixels[i].r)
				{
					temp = temp + img10.pixels[i].r;
					pixAmount = pixAmount + 1;
				}
				//red devide
				output.pixels[i].r = temp / pixAmount;
			}
			//green values
			if (blueOld >= blue)
			{
				int pixAmount = 0;

				float minus = med.pixels[i].g - green;
				float add = med.pixels[i].g + green;
				temp = 0;

				if (add >= img1.pixels[i].g && minus <= img1.pixels[i].g)
				{
					temp = temp + img1.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img2.pixels[i].g && minus <= img2.pixels[i].g)
				{
					temp = temp + img2.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img3.pixels[i].g && minus <= img3.pixels[i].g)
				{
					temp = temp + img3.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img4.pixels[i].g && minus <= img4.pixels[i].g)
				{
					temp = temp + img4.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img5.pixels[i].g && minus <= img5.pixels[i].g)
				{
					temp = temp + img5.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img6.pixels[i].g && minus <= img6.pixels[i].g)
				{
					temp = temp + img6.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img7.pixels[i].g && minus <= img7.pixels[i].g)
				{
					temp = temp + img7.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img8.pixels[i].g && minus <= img8.pixels[i].g)
				{
					temp = temp + img8.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img9.pixels[i].g && minus <= img9.pixels[i].g)
				{
					temp = temp + img9.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img10.pixels[i].g && minus <= img10.pixels[i].g)
				{
					temp = temp + img10.pixels[i].g;
					pixAmount = pixAmount + 1;
				}
				//green devide
				output.pixels[i].g = temp / pixAmount;
			}
			//blue values
			if (blueOld >= blue)
			{
				int pixAmount = 0;

				float minus = med.pixels[i].b - blue;
				float add = med.pixels[i].b + blue;
				temp = 0;

				if (add >= img1.pixels[i].b && minus <= img1.pixels[i].b)
				{
					temp = temp + img1.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img2.pixels[i].b && minus <= img2.pixels[i].b)
				{
					temp = temp + img2.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img3.pixels[i].b && minus <= img3.pixels[i].b)
				{
					temp = temp + img3.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img4.pixels[i].b && minus <= img4.pixels[i].b)
				{
					temp = temp + img4.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img5.pixels[i].b && minus <= img5.pixels[i].b)
				{
					temp = temp + img5.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img6.pixels[i].b && minus <= img6.pixels[i].b)
				{
					temp = temp + img6.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img7.pixels[i].b && minus <= img7.pixels[i].b)
				{
					temp = temp + img7.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img8.pixels[i].b && minus <= img8.pixels[i].b)
				{
					temp = temp + img8.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img9.pixels[i].b && minus <= img9.pixels[i].b)
				{
					temp = temp + img9.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				else if (add >= img10.pixels[i].b && minus <= img10.pixels[i].b)
				{
					temp = temp + img10.pixels[i].b;
					pixAmount = pixAmount + 1;
				}
				output.pixels[i].b = temp / pixAmount;
			}

			redOld = red;
			greenOld = green;
			blueOld = blue;

			if (redOld >= red && greenOld >= green && blueOld >= blue)
			{
				varible = varible + 1;
			}
		}
		if (varible == pi)
		{
			z = 10;
		}
	}

	std::cout << "Finished Sigma Clipped Mean" << std::endl;
	return output;
}

//Write data out to a ppm file
void outputPPM(const Image &img, const char *filename)
{
	system("CLS");

	std::string selection;
	std::cout << "************************************" << std::endl;
	std::cout << "Image Output" << std::endl;
	std::cout << "************************************" << std::endl;
	std::cout << "1:Write Image" << std::endl;
	std::cout << "2:Show Image Info" << std::endl;
	std::cout << "3:Both" << std::endl;
	std::getline(std::cin, selection);

	if (selection.compare("1") == 0)
	{
		std::cout << filename << std::endl;
		std::cout << "Writing image ..." << std::endl;
		if (img.w == 0 || img.h == 0) { fprintf(stderr, "Can't save an empty image\n"); return; }
		std::ofstream ofs;
		try {
			ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users 
			if (ofs.fail()) throw("Can't open output file");
			ofs << "P6\n" << img.w << " " << img.h << "\n255\n";
			std::cout << "P6\n" << img.w << " " << img.h << "\n255\n";
			unsigned char r, g, b;
			// loop over each pixel in the image, clamp and convert to byte format
			for (int i = 0; i < img.w * img.h; ++i) {
				r = static_cast<unsigned char>(1.f, img.pixels[i].r);
				g = static_cast<unsigned char>(1.f, img.pixels[i].g);
				b = static_cast<unsigned char>(1.f, img.pixels[i].b);
				ofs << r << g << b;
			}
			ofs.close();
			//Confirm image write
			std::cout << "Image written" << std::endl;
		}
		catch (const char *err) {
			fprintf(stderr, "%s\n", err);
			ofs.close();
		}
	}
	else if (selection.compare("2") == 0)
	{
		Image i;
		i.info(img);
	}
	else if (selection.compare("3") == 0)
	{
		std::cout << filename << std::endl;
		std::cout << "Writing image ..." << std::endl;
		if (img.w == 0 || img.h == 0) { fprintf(stderr, "Can't save an empty image\n"); return; }
		std::ofstream ofs;
		try {
			ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users 
			if (ofs.fail()) throw("Can't open output file");
			ofs << "P6\n" << img.w << " " << img.h << "\n255\n";
			std::cout << "P6\n" << img.w << " " << img.h << "\n255\n";
			unsigned char r, g, b;
			// loop over each pixel in the image, clamp and convert to byte format
			for (int i = 0; i < img.w * img.h; ++i) {
				r = static_cast<unsigned char>(1.f, img.pixels[i].r);
				g = static_cast<unsigned char>(1.f, img.pixels[i].g);
				b = static_cast<unsigned char>(1.f, img.pixels[i].b);
				ofs << r << g << b;
			}
			ofs.close();
			//Confirm image write
			std::cout << "Image written" << std::endl;
		}
		catch (const char *err) {
			fprintf(stderr, "%s\n", err);
			ofs.close();
		}

		Image i;
		i.info(img);

	}
	else
	{
		std::cout << selection << ": not vaild input. try 1,2, etc." << std::endl;
	}
}