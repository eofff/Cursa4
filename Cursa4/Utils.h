#pragma once

#include <fstream>
#include <string.h>

#include <omp.h>
#include <CL/cl.h>

using namespace System::Drawing;

class Utils
{
public:
	static Bitmap^ SequentialChangeContrast(Bitmap^ img, double coeff);
	static Bitmap^ OmpChangeContrast(Bitmap^ img, double coeff);
	static Bitmap^ CLChangeContrast(cl_device_id* devices, Bitmap^ img, float coeff);
	static int convertToString(const char* fileName, std::string& s);
};
