#pragma once
#include <cstdlib> 
#include <cstdio>

class Image
{
public:
	// Rgb structure, i.e. a pixel 
	struct Rgb
	{
		Rgb() : r(0), g(0), b(0) {}
		Rgb(unsigned char c) : r(c), g(c), b(c) {}
		Rgb(unsigned char _r, unsigned char _g, unsigned char _b) : r(_r), g(_g), b(_b) {}
		bool operator != (const Rgb &c) const
		{
			return c.r != r || c.g != g || c.b != b;
		}
		Rgb& operator *= (const Rgb &rgb)
		{
			r *= rgb.r, g *= rgb.g, b *= rgb.b; return *this;
		}
		Rgb& operator += (const Rgb &rgb)
		{
			r += rgb.r, g += rgb.g, b += rgb.b; return *this;
		}
		unsigned char r, g, b;
	};
	Image() : w(0), h(0), pixels(nullptr) { /* empty image */ }
	Image(const unsigned int &_w, const unsigned int &_h, const Rgb &c = kBlack) : w(_w), h(_h), pixels(NULL)
	{
		pixels = new Rgb[w * h];
		for (int i = 0; i < w * h; ++i)
			pixels[i] = c;
	}
	//output Image With additional values
	Image(const unsigned int &_w, const unsigned int &_h, const std::string fileN, const int col, const int man, const int ZoomL, const std::string zoomT, const Rgb &c = kBlack) : w(_w), h(_h), pixels(NULL)
	{
		filename = fileN;
		colour = col;
		manuiplated = man;
		zoomType = zoomT;
		zoomLevel = ZoomL;
		
		pixels = new Rgb[w * h];
		for (int i = 0; i < w * h; ++i)
			pixels[i] = c;
	}
	Image(const unsigned int &_w, const unsigned int &_h, const int col, const int man, const int ZoomL, const std::string fileN,  const std::string zoomT) : w(_w), h(_h)
	{
		filename = fileN;
		colour = col;
		manuiplated = man;
		zoomType = zoomT;
		zoomLevel = ZoomL;
	}
	//copy constructor
	Image(const Image &im)
	{
		w = im.w;
		h = im.h;
		filename = im.filename;
		colour = im.colour;
		manuiplated = im.manuiplated;
		zoomType = im.zoomType;
		zoomLevel = im.zoomLevel;
		colour = im.colour;
		manuiplated = im.manuiplated;
		pixels = new Rgb[im.w * im.h];
		for (int i = 0; i < im.w * im.h; ++i)
			pixels[i] = im.pixels[i];
	}
	//copy assignment operator
	Image& operator=(const Image& other)
	{
		w = other.w;
		h = other.h;
		filename = other.filename;
		colour = other.colour;
		manuiplated = other.manuiplated;
		zoomType = other.zoomType;
		zoomLevel = other.zoomLevel;
		pixels = new Rgb[other.w * other.h];
		for (int i = 0; i < other.w * other.h; ++i)
			pixels[i] = other.pixels[i];

		return *this;

	}
	const Rgb& operator [] (const unsigned int &i) const
	{
		return pixels[i];
	}
	Rgb& operator [] (const unsigned int &i)
	{
		return pixels[i];
	}
	//Info of image
	void info(const Image main)
	{
		system("CLS");
		std::cout << "************************************" << std::endl;
		std::cout << "Image Info" << std::endl;
		std::cout << "************************************" << std::endl;

		std::cout << "File Name   :" << main.filename << std::endl;
		std::cout << "Width       :" << main.w << std::endl;
		std::cout << "Height      :" << main.h << std::endl;
		std::cout << "Colour depth:" << main.colour << std::endl;
		std::cout << "Manuiplated :" << main.manuiplated << std::endl;
		std::cout << "Zoom Type   :" << main.zoomType << std::endl;
		std::cout << "Zoom Level  :" << main.zoomLevel << std::endl;

		std::cout << "Do you whish to output image info as log?" << std::endl;
		std::string selection;
		std::getline(std::cin, selection);

		if (selection.compare("yes") == 0 || selection.compare("Yes") == 0 || selection.compare("YES") == 0 || selection.compare("1") == 0)
		{
			std::string name = (main.filename + "_Info.txt");
			std::ofstream ofs(name);
			try {
				ofs << "File Name   :" << main.filename << std::endl;
				ofs << "Width       :" << main.w << std::endl;
				ofs << "Height      :" << main.h << std::endl;
				ofs << "Colour depth:" << main.colour << std::endl;
				ofs << "Manuiplated :" << main.manuiplated << std::endl;
				ofs << "Zoom Type   :" << main.zoomType << std::endl;
				ofs << "Zoom Level  :" << main.zoomLevel << std::endl;

				ofs.close();
				//Confirm image write
				std::cout << "Image info written" << std::endl;
			}
			catch (const char *err) {
				fprintf(stderr, "%s\n", err);
				ofs.close();
			}
		}

		return;
	}
	~Image()
	{
		if (pixels != NULL) delete[] pixels;
		//delete[] pixels;
	}


	//Image values
	std::string filename = "------------------------------------------"; // Image file name
	std::string zoomType = "------------------------------------------"; // Image zoom type
	int w, h;				   // Image resolution
	int colour;				   // Image colour
	int manuiplated;		   // Image if manuiplated
	int zoomLevel = 1;		   // Image zoom level
	Rgb *pixels;		       // 1D array of pixels 
	static const Rgb kBlack, kWhite, kRed, kGreen, kBlue; // Preset colors 

};

class neighbour : public Image
{
public:
	neighbour() {}
	Image& zoom(const Image& main)
	{
		//set new image
		w = main.w * 2;
		h = main.h * 2;

		pixels = new Image::Rgb[w * h];
		//set values and loop old image
		int z = 0;
		int x = 0;
		int pi = 2;
		int base = main.w * main.h;
		for (int i = 1; i < base; ++i)
		{
			z = z + 1;
			//skip every other pixel line
			if (z == main.w)
			{
				x = x + 1;
				pi = (i * 2);
				pi = pi + (w * x);
				z = 0;
			}
			else
				pi = (i * 2) + (w * x);


			//write pixels
			pixels[pi - 1] = main.pixels[i];
			pixels[pi - 2] = main.pixels[i];
			pixels[pi - 1 + w] = main.pixels[i];
			pixels[pi - 2 + w] = main.pixels[i];
		}

		manuiplated = 1;
		zoomType = "Nearist_Neighbour";
		zoomLevel = main.zoomLevel * 2;
		colour = 255;
		filename = ("Nearist_Neighbour" + std::to_string(main.zoomLevel * 2));

		return *this;
	}
};

class bilinear : public Image
{
public:
	bilinear() {}
	Image& zoom(const Image& main)
	{
		//set new image
		w = main.w * 2;
		h = main.h * 2;

		pixels = new Image::Rgb[w * h];
		//set values and loop old image
		int base = main.w * main.h;

		int z = 0;
		int x = 0;
		int pi = 2;

		for (int i = 1; i < base; ++i)
		{
			z = z + 1;
			//skip every other pixel line
			if (z == main.w)
			{
				x = x + 1;
				pi = (i * 2);
				pi = pi + (w * x);
				z = 0;
			}
			else
				pi = (i * 2) + (w * x);


			//write pixels
			pixels[pi - 1] = main.pixels[i];
		}
		z = 0;
		x = 0;
		pi = 2;

		for (int i = 1; i < base; ++i)
		{
			z = z + 1;
			//skip every other pixel line
			if (z == main.w)
			{
				x = x + 1;
				pi = (i * 2);
				pi = pi + (w * x);
				z = 0;
			}
			else
				pi = (i * 2) + (w * x);

			//write pixels
			pixels[pi - 2].r = (main.pixels[i].r + main.pixels[i + 1].r) / 2;
			pixels[pi - 2].g = (main.pixels[i].g + main.pixels[i + 1].g) / 2;
			pixels[pi - 2].b = (main.pixels[i].b + main.pixels[i + 1].b) / 2;
		}

		z = 0;
		x = 0;
		pi = 2;

		for (int i = 1; i < (base - main.w); ++i)
		{
			z = z + 1;
			//skip every other pixel line
			if (z == main.w)
			{
				x = x + 1;
				pi = (i * 2);
				pi = pi + (w * x);
				z = 0;
			}
			else
				pi = (i * 2) + (w * x);

			//write pixels
			pixels[pi - 1 + w].r = (pixels[pi - 1].r + pixels[pi - 1 + (2 * w)].r) / 2;
			pixels[pi - 1 + w].g = (pixels[pi - 1].g + pixels[pi - 1 + (2 * w)].g) / 2;
			pixels[pi - 1 + w].b = (pixels[pi - 1].b + pixels[pi - 1 + (2 * w)].b) / 2;

			pixels[pi - 2 + w].r = (pixels[pi - 2].r + pixels[pi - 2 + (2 * w)].r) / 2;
			pixels[pi - 2 + w].g = (pixels[pi - 2].g + pixels[pi - 2 + (2 * w)].g) / 2;
			pixels[pi - 2 + w].b = (pixels[pi - 2].b + pixels[pi - 2 + (2 * w)].b) / 2;
		}
		manuiplated = 1;
		zoomType = "Bilinear";
		zoomLevel = main.zoomLevel * 2;
		colour = 255;
		filename = ("Bilinear" + std::to_string(main.zoomLevel * 2));

		return *this;
	}
};
	
const Image::Rgb Image::kBlack = Image::Rgb(0);
const Image::Rgb Image::kWhite = Image::Rgb(255);
const Image::Rgb Image::kRed = Image::Rgb(255, 0, 0);
const Image::Rgb Image::kGreen = Image::Rgb(0, 255, 0);
const Image::Rgb Image::kBlue = Image::Rgb(0, 0, 255);
