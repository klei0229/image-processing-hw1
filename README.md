# image-processing-hw1

## 1. Quantize
HW_quantize reads the input image from I1 and uniformly quantizes it into levels quantization levels.  The output is stored in I2. Quantization should be done by subdividing the range of 256 intensities into levels uniform intervals.  Assign the midpoints of the uniform intervals as the output intensities. For instance, if levels=4, then gray values 32, 96, 160, and224 are used.  In general, the intermediate gray values are increments of 256 / levels with a bias of 128 / levels.

## 2. Clip
HW_clip clips the input image in I1 to the range [t1,t2]. The output is savedinI2. 

## 3. Gamma
HW_gamma performs gamma correction on the input image in I1 using the specified gamma.

## 4. Contrast
HW_contrast applies  contrast  enhancement  to  I1. This  function  stretches  the  intensity  difference  from  reference value  (128)  by  multiplying  the  difference  of  each  pixel  from  128  by contrast and  adding  it  back  to  128. Shift result by adding brightness value. The output is saved in I2.

## 5. histoStretch
HW_histoStretch stretches  the  dynamic  range  of  the  input  image  in  image  I1  to  fill  the  entire  [0,255]  range. The range that is stretched spans from t1 to t2.  All intensity values below t1 or above t2 are pulled to 0 or 255, respectively. The output is stored in image I2.  Note: you may want to look at the image histogram before selecting an appropriate t1 and t2.

## 6. histoMatch
HW_histoMatch performs  a  histogram  matching  operation  to  input  image  I1,  saving  the  result  in  image  I2. The histogram used is given in image Ihisto.  That image has 256 numbers that denote the shape of the histogram curve.  When all the numbers are the same, a flat histogram is specified and histogram equalization will be performed. You will have to make sure that the histogram entries are scaled properly so that their sum is equal to the total number of pixels in the input image. Modify the code supplied in the notes so that the histogram is matched exactly, with the possible exception of the very last histogram  entry. If the boolean flag approxAlg is set to 1, then implement the simpler (non-exact) version of histogrammatching, as shown in the textbook.  If that flag is set to 0, then implement the exact version included in the notes, where by the histogram of the output image will closely match the histogram specified in Ihisto.