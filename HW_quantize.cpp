// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_quantize:
//
// Quantize I1 to specified number of levels. Apply dither if flag is set.
// Output is in I2.
//
void
HW_quantize(ImagePtr I1, int levels, bool dither, ImagePtr I2)
{
	// copy image header (width, height) of input image I1 to output image I2
	IP_copyImageHeader(I1, I2);

	// init vars for width, height, and total number of pixels
	int w = I1->width();
	int h = I1->height();
	int total = w * h;

	// init lookup table
	int i, lut[MXGRAY];
	double scale = MXGRAY / levels;
	double bias = scale / 2;
	for (i = 0; i < MXGRAY; ++i) lut[i] = scale * int(i / scale) + int(bias);

	// declarations for image channel pointers and datatype
	ChannelPtr<uchar> p1, p2;
	int type;

	// Note: IP_getChannel(I, ch, p1, type) gets pointer p1 of channel ch in image I.
	// The pixel datatype (e.g., uchar, short, ...) of that channel is returned in type.
	// It is ignored here since we assume that our input images consist exclusively of uchars.
	// IP_getChannel() returns 1 when channel ch exists, 0 otherwise.

	// Random
	srand(time(0));

	// visit all image channels and evaluate output image
	for (int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {	// get input  pointer for channel ch
		IP_getChannel(I2, ch, p2, type);		// get output pointer for channel ch
		for (i = 0; i < total; i++)
		{
			if (!dither)
			{
				*p2++ = lut[*p1++];	// use lut[] to eval output
			}
			else
			{
				//if(((i%w)+(i%h))%2) // odd : - rand
				if (i % 2)
					//if((((i/h)%w)+((i/w)%h))%2) // bad
					//if((((i/w)%w)+((i/h)%h))%2) //bad
				{
					*p2++ = lut[qMin(qMax(((*p1++) - (rand() % int(bias))), 0), 255)];	// use lut[] to eval output
				}
				else    // even : + rand
				{
					*p2++ = lut[qMin(qMax(((*p1++) + (rand() % int(bias))), 0), 255)];	// use lut[] to eval output
				}
			}
		}
	}
}
