__constant sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP | CLK_FILTER_NEAREST;
__kernel void main_kernel(read_only image2d_t src_image, write_only image2d_t dst_image, __global unsigned char * pallete)
{
	uint y = get_global_id(1);	
	uint x = get_global_id(0);	
	uint width = get_global_size(0);
	uint height = get_global_size(1);
	int2 coor = (int2)(x, y);
	uint4 color = read_imageui(src_image, sampler, coor);
	uint4 newColor = (uint4)(pallete[color.x], pallete[color.y], pallete[color.z], color.w);
	write_imageui(dst_image, coor, newColor);
}