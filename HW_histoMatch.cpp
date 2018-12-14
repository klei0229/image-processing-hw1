
void histoMatchApprox(ImagePtr, ImagePtr, ImagePtr);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_histoMatch:
//
// Apply histogram matching to I1. Output is in I2.
//
void
HW_histoMatch(ImagePtr I1, ImagePtr targetHisto, bool approxAlg, ImagePtr I2)
{
	if (approxAlg) {
		histoMatchApprox(I1, targetHisto, I2);
		return;
	}
}

void
histoMatchApprox(ImagePtr I1, ImagePtr targetHisto, ImagePtr I2)
{
	// copy image header (width, height) of input image I1 to output image I2
	IP_copyImageHeader(I1, I2);

	int i, p, R;
	int left[MXGRAY], right[MXGRAY];
	int total, Hsum, Havg, h1[MXGRAY];

	ChannelPtr<uchar> in, out;
	ChannelPtr<int> h2;

	double scale;

	int w = I1->width();
	int h = I1->height();

	total = w * h;
	// declarations for image channel pointers and datatype


	int type;

	// Note: IP_getChannel(I, ch, p1, type) gets pointer p1 of channel ch in image I.
	// The pixel datatype (e.g., uchar, short, ...) of that channel is returned in type.
	// It is ignored here since we assume that our input images consist exclusively of uchars.
	// IP_getChannel() returns 1 when channel ch exists, 0 otherwise.


	for (int ch = 0; IP_getChannel(I1, ch, in, type); ch++) {	// get input  pointer for channel ch and store pointer to in
		IP_getChannel(I2, ch, out, type);						// get output pointer for channel ch and store point to out


	//clears histogram 1 by zeroing all gray scale values
		for (int i = 0; i < MXGRAY; i++) {
			h1[i] = 0;
		}

	//evaulates histogram for input image (I1)
		for (int i = 0; i < total; i++) {
			h1[in[i]]++;
		}

		//get input pointer for channel ch for targetHisto Image
		IP_getChannel(targetHisto, ch, h2, type);

		//normalize histogram for h2 to scale with h1
		for (int i = Havg = 0; i < MXGRAY; i++) Havg += h2[i];

		scale = (double)total / (Havg);

		if (scale != 1)
		{
			for (int i = 0; i < MXGRAY; i++)
			{
				h2[i] *= scale;
			}
		}

		//computes left and right interval bounds 
		R = 0;
		Hsum = 0;
		for (int i = 0; i < MXGRAY; i++) {
			left[i] = R;
			Hsum += h1[i];
			while (Hsum > h2[R] && R < MXGRAY - 1) {
				Hsum -= h2[R];
				R++;
			}
			right[i] = R;
		}

		//clears h1 and reuse
		for (int i = 0; i < MXGRAY; i++) {
			h1[i] = 0;
		}

		//used left and right arrays to compute and display new image onto I2
		for (int i = 0; i < total; i++) {
			p = left[in[i]];
			if (h1[p] < h2[p]) {
				out[i] = p;
			}
			else {
				out[i] = p = left[in[i]] = MIN(p + 1, right[in[i]]);
			}
			h1[p]++;
		}
	}
}
