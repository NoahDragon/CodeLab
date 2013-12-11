#
# GCE Histogram Modification Algorithm for Image Contrast Enhancement
#
# Ref(s):
#	T. Arici, S. Dikbas, and Y. Altunbasak, "A Histogram Modfication Framework
#	and Its Application for Image Contrast Enhancement". IEEE Trans. on IMAGE 
#	PROCESSING, VOL. 18, NO. 9, pp. 1921-1935(2009).
#
# Input: 8-bit gray image (array); enhancement level; threshold for two lagged difference;
#        b&w stretch parameters black, white, a.
# Output: modified image (array)
#
# 2013 Feb

import sys
import math
import numpy
import scipy
from PIL import Image 

def gcehistmod(img, enhancement, threshold, black, white, a, nbr_bins=256):
	# prameter K for recording the two lagged difference	
	k = 0
	
	# init temp histogram
	h_i = []
	for i in range(nbr_bins):
		h_i.append(0)	
	
	count = 0
	#pixel = f.load()
	for m in range(0, img.shape[0]):
		for n in range(2,img.shape[1]):
			abs_t = abs(img[m][n]-img[m][n-2])
			k = k + abs_t
			if abs_t > threshold:
				h_i[img[m][n]] += 1
				count += 1
	
	# normalize gk to k_star
	k_star = float(enhancement*k)
	while k_star > 1.0:
		k_star = k_star/10.0

	# original histogram
	hist, bins = numpy.histogram(img.flatten(), nbr_bins , (0,255) , density=False)

	# find the u_min
	u_min = float(count/float(nbr_bins))
	for i in range(nbr_bins):
		if u_min >hist[i]:
			u_min = hist[i]
	
	# B&W stretch
	h = list(hist) #copy orginal histogram
	for n in range(nbr_bins):
		if n>black and n<white:
			h[n] = (1.0-k_star)*u_min + k_star*float(h_i[n])
		else:
			h[n] = float(1.0/(1.0+a))*((1.0-k_star)*u_min+k_star*float(h_i[n]))


    	# Applying Histogram Equalization on Modified Histogram
    	histpdf = h / numpy.float32(img.size)
    	cdf = histpdf.cumsum()
    	fL = 255 * cdf
    	fL = fL.astype('uint8')

	# New Picture    
	nimg = numpy.zeros(img.shape,dtype=numpy.int16)
    	for i in range(0,img.shape[0]):
        	for j in range(0,img.shape[1]):
 	           	nimg[i][j] = fL[img[i][j]]

	return nimg, h # return new image array and modified histogram
