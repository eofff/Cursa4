__kernel void pallete_kernel(__global unsigned char * output, __global unsigned char * avg, __global float * coeff)
{
	int id = get_global_id(0);

	int temp = avg[0] + coeff[0] * (id - avg[0]);
	if (temp < 0)
	{
		temp = 0;
	}
	else if (temp > 255)
	{
		temp = 255;
	}

	output[id] = temp;
}