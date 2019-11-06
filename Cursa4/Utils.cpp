#include "Utils.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

Bitmap^ Utils::SequentialChangeContrast(Bitmap^ img, double coeff)
{
	Bitmap^ returned = gcnew Bitmap(img->Width, img->Height);

	unsigned char pallete[256];
	int avg = 0;
	int j = 0;
	int height = img->Height;
	int width = img->Width;

	unsigned char* inputImagePixels = new unsigned char[height * width * 4];
	unsigned char* ch = &inputImagePixels[0];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			*ch++ = img->GetPixel(j, i).A;
			*ch++ = img->GetPixel(j, i).R;
			*ch++ = img->GetPixel(j, i).G;
			*ch++ = img->GetPixel(j, i).B;
		}
	}

	ch = &inputImagePixels[0];
	for (int i = 0; i < height; i++)
	{
		int buff_avg = 0;
		for (int j = 0; j < width; j++)
		{
			*ch++;
			unsigned char r = *ch++;
			unsigned char g = *ch++;
			unsigned char b = *ch++;
			avg += r * 0.299 + g * 0.587 + b * 0.114;
		}
	}
	avg /= (width * height);

	for (int i = 0; i <= 255; i++)
	{
		int temp = avg + coeff * (i - avg);
		if (temp < 0)
		{
			temp = 0;
		}
		else if (temp > 255)
		{
			temp = 255;
		}
		pallete[i] = temp;
	}

	ch = &inputImagePixels[0];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			*ch++;
			*ch = pallete[*ch];
			*ch++;
			*ch = pallete[*ch];
			*ch++;
			*ch = pallete[*ch];
			*ch++;
		}
	}

	ch = &inputImagePixels[0];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			unsigned int temp = *ch++ << 24;
			temp |= (*ch++ << 16);
			temp |= (*ch++ << 8);
			temp |= *ch++;
			returned->SetPixel(j, i, Color::FromArgb(temp));
		}
	}

	return returned;
}

Bitmap^ Utils::OmpChangeContrast(Bitmap^ img, double coeff)
{
	Bitmap^ returned = gcnew Bitmap(img->Width, img->Height);

	unsigned char pallete[256];
	int avg = 0;
	int j = 0;
	int height = img->Height;
	int width = img->Width;

	unsigned char* inputImagePixels = new unsigned char[height * width * 4];
	unsigned char* ch = &inputImagePixels[0];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			*ch++ = img->GetPixel(j, i).A;
			*ch++ = img->GetPixel(j, i).R;
			*ch++ = img->GetPixel(j, i).G;
			*ch++ = img->GetPixel(j, i).B;
		}
	}

	int buff_avg = 0;
#pragma omp parallel for schedule(dynamic, 200) firstprivate(buff_avg, inputImagePixels)
	for (int i = 0; i < height; i++)
	{
#pragma omp critical
		buff_avg = 0;
		for (int j = 0; j < width; j++)
		{
			unsigned char r = inputImagePixels[(i * width + j) * 4 + 1];
			unsigned char g = inputImagePixels[(i * width + j) * 4 + 2];
			unsigned char b = inputImagePixels[(i * width + j) * 4 + 3];
			buff_avg += r * 0.299 + g * 0.587 + b * 0.114;
		}
#pragma omp critical
		{
			avg += buff_avg;
		}
	}
	avg /= (width * height);

	for (int i = 0; i <= 255; i++)
	{
		int temp = avg + coeff * (i - avg);
		if (temp < 0)
		{
			temp = 0;
		}
		else if (temp > 255)
		{
			temp = 255;
		}
		pallete[i] = temp;
	}

#pragma omp parallel for schedule(dynamic, 200) shared(inputImagePixels) 
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			inputImagePixels[(i * width + j) * 4 + 1] = pallete[inputImagePixels[(i * width + j) * 4 + 1]];
			inputImagePixels[(i * width + j) * 4 + 2] = pallete[inputImagePixels[(i * width + j) * 4 + 2]];
			inputImagePixels[(i * width + j) * 4 + 3] = pallete[inputImagePixels[(i * width + j) * 4 + 3]];
		}
	}

	ch = &inputImagePixels[0];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			unsigned int temp = *ch++ << 24;
			temp |= (*ch++ << 16);
			temp |= (*ch++ << 8);
			temp |= *ch++;
			returned->SetPixel(j, i, Color::FromArgb(temp));
		}
	}

	return returned;
}

Bitmap^ Utils::CLChangeContrast(cl_device_id *devices, Bitmap^ img, double coeff)
{
	// высчитаем новую палитру, этот шаг не поддаётся параллелизации с помощью OpenCL
	unsigned char pallete[256];
	int avg = 0;

	for (int i = 0; i < img->Height; i++)
		for (int j = 0; j < img->Width; j++)
		{
			Color newColor = img->GetPixel(j, i);
			unsigned char r = newColor.R;
			unsigned char g = newColor.G;
			unsigned char b = newColor.B;
			avg += r * 0.299 + g * 0.587 + b * 0.114;
		}
	avg /= (img->Width * img->Height);

	for (int i = 0; i <= 255; i++)
	{
		int temp = avg + coeff * (i - avg);
		if (temp < 0)
		{
			temp = 0;
		}
		else if (temp > 255)
		{
			temp = 255;
		}
		pallete[i] = temp;
	}

	// далее идёт участок кода с участием OpenCL
	cl_int status = 0;
	cl_context context = clCreateContext(NULL, 1, devices, NULL, NULL, NULL);
	cl_command_queue commandQueue = clCreateCommandQueue(context, devices[0], 0, NULL);
	const char* fileName = "main_kernel.cl";
	std::string sourceCode;
	status = convertToString(fileName, sourceCode);
	const char* source = sourceCode.c_str();
	size_t sizeOfSource[] = { strlen(source) };
	cl_program program = clCreateProgramWithSource(context, 1, &source,	sizeOfSource, &status);
	status = clBuildProgram(program, 1, devices, NULL, NULL, NULL);
	cl_image_format* imageFormat = new cl_image_format;
	imageFormat->image_channel_order = CL_ARGB;
	imageFormat->image_channel_data_type = CL_UNSIGNED_INT8;
	size_t imageWidth = img->Width;
	size_t imageHeight = img->Height;
	Bitmap^ bmpInputImage = gcnew Bitmap(img);
	unsigned char* inputImagePixels = new unsigned char[imageHeight * imageWidth * 4];
	unsigned char* ch = &inputImagePixels[0];
	for (int i = 0; i < imageHeight; i++)
	{
		for (int j = 0; j < imageWidth; j++)
		{
			*ch++ = bmpInputImage->GetPixel(j, i).A;
			*ch++ = bmpInputImage->GetPixel(j, i).R;
			*ch++ = bmpInputImage->GetPixel(j, i).G;
			*ch++ = bmpInputImage->GetPixel(j, i).B;
		}
	}
	cl_mem inputImage2DBuffer = clCreateImage2D(context, CL_MEM_COPY_HOST_PTR | CL_MEM_READ_ONLY, imageFormat, imageWidth, imageHeight, 0, (void*)inputImagePixels, &status);
	cl_mem outputImage2DBuffer = clCreateImage2D(context, CL_MEM_WRITE_ONLY, imageFormat, imageWidth, imageHeight, 0, NULL, &status);
	cl_mem palleteBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_uchar) * 256, pallete, &status);
	cl_kernel kernel = clCreateKernel(program, "main_kernel", &status);
	status = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&inputImage2DBuffer);
	status = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&outputImage2DBuffer);
	status = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&palleteBuffer);
	size_t global_work_size[] = { imageWidth, imageHeight };
	status = clEnqueueNDRangeKernel(commandQueue, kernel, 2, NULL, global_work_size, NULL, 0, NULL, NULL);
	size_t origin[3] = { 0, 0, 0 };
	size_t region[3] = { imageWidth, imageHeight, 1 };
	unsigned char* outputImagePixels = new unsigned char[imageWidth * imageHeight * 4];
	status = clEnqueueReadImage(commandQueue, outputImage2DBuffer, CL_TRUE, origin, region, 0, 0, outputImagePixels, 0, NULL, NULL);
	Bitmap^ bmpOutputImage = gcnew Bitmap(imageWidth, imageHeight);
	unsigned char* p = &outputImagePixels[0];
	for (int i = 0; i < imageHeight; i++)
	{
		for (int j = 0; j < imageWidth; j++)
		{
			unsigned int temp = *p++ << 24;
			temp |= (*p++ << 16);
			temp |= (*p++ << 8);
			temp |= *p++;
			bmpOutputImage->SetPixel(j, i, Color::FromArgb(temp));
		}
	}
	clReleaseMemObject(outputImage2DBuffer);
	clReleaseMemObject(inputImage2DBuffer);
	delete[]inputImagePixels;
	delete[]outputImagePixels;
	clReleaseKernel(kernel);
	clReleaseCommandQueue(commandQueue);
	clReleaseContext(context);
	clReleaseProgram(program);

	return bmpOutputImage;
}

int Utils::convertToString(const char* fileName, std::string& s)
{
	size_t size;
	char* str;
	std::fstream f(fileName, (std::fstream::in | std::fstream::binary));
	if (f.is_open())
	{
		size_t fileSize;
		f.seekg(0, std::fstream::end);
		size = fileSize = (size_t)f.tellg();
		f.seekg(0, std::fstream::beg);
		str = new char[size + 1];
		if (!str) {
			f.close();
			return 0;
		}
		f.read(str, fileSize);
		f.close();
		str[size] = '\0';
		s = str;
		delete[]str;
		return 0;
	}
	return -1;
}
