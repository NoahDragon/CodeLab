# Color Image Histogram Equalization by Absolute Discounting Back-off
#
# Ref(s):
#	N. Bassiou, C. Kotropoulos, "Color Image Histogram Equalization by 
#	Absolute Discounting Back-off". Computer Vision and Image Understanding,
#	VOL. 107, pp. 108-122(2007).
#
# 2013 Mar
#

from math import *
import sys
import math
import numpy
import scipy
from PIL import Image 

#
# RGB color space to HSI
# @param RGB color list or tuple
# @return HSI tuple
# Ref: http://fourier.eng.hmc.edu/e161/lectures/color_processing/node3.html
#

def rgb2hsi(rgb):
	R = float(rgb[0])
	G = float(rgb[1])
	B = float(rgb[2])
	
	# add a really small number to avoid divid zero
	smallnumber = 1.e-10
	i = R+G+B
	
	I = i/3.0

	r = R/(i+smallnumber)
	g = G/(i+smallnumber)
	b = B/(i+smallnumber)
	
	if R==G and G==B:
		S=0.0
		H=0.0
	else:
		w=0.5*(R-G+R-B)/sqrt((R-G)*(R-G)+(R-B)*(G-B))
		if w>1.0:
			w=1.0
		if w<-1.0:
			w=-1.0

		H = acos(w)

		if B>G:
			H = 2.0*pi - H
		if r<=g and r<=b:
			S = 1.0-3.0*r
		elif g<=r and g<=b:
			S = 1.0-3.0*g
		elif b<=r and b<=g:
			S = 1.0-3.0*b

	return (H, S, I)

#
# HSI color space to RGB
# @param HSI color list or tuple
# @return RGB tuple
# tested if the Max R,G,B is 255
# Ref: http://fourier.eng.hmc.edu/e161/lectures/color_processing/node4.html
#

def hsi2rgb(hsi):
	H = hsi[0]	
	S = hsi[1]
	I = hsi[2]

	r = 0.0
	g = 0.0
	b = 0.0

	if S>1.0: 
		S=1.0
	#if I>1.0: 
	#	I=1.0
	if S==0.0:
		R = I
		G = I
		B = I
	else:
		if H >= 0.0 and H<2.0*pi/3.0 :
			b = (1.0-S)/3.0
			r = (1.0+S*cos(H)/cos(pi/3.0-H))/3.0
			g = 1.0-r-b
		elif H>=2.0*pi/3.0 and H<4.0*pi/3.0:
			H = H-2.0*pi/3.0
			r = (1.0-S)/3.0
			g = (1.0+S*cos(H)/cos(pi/3.0-H))/3.0
			b = 1.0-r-g
		elif H>=4.0*pi/3.0 and H<2.0*pi:
			H = H-4.0*pi/3.0
			g = (1.0-S)/3.0
			b = (1.0+S*cos(H)/cos(pi/3.0-H))/3.0
			r = 1.0-b-g
		else:
			print "H out of range"
			sys.exit(1)
		
		if r<0.0:
			r = 0.0
		if g<0.0:
			g = 0.0
		if b<0.0:
			b = 0.0

		R = 3.0*I*r
		G = 3.0*I*g
		B = 3.0*I*b

		#if R > 1.0:
		#	R = 1.0
		#if G > 1.0:
		#	G = 1.0
		#if B > 1.0:
		#	B = 1.0
	return (R,G,B)

#
# Equalization of the intensity component in the HSI space
# @param image array
# @param ibins intensity levels
# @param sbins saturation levels
# @return modified image array
#
# Ref(s):
#	N. Bassiou, C. Kotropoulos, "Color Image Histogram Equalization by 
#	Absolute Discounting Back-off". Computer Vision and Image Understanding,
#	VOL. 107, pp. 108-122(2007).
#

def hsihe_i(img, ibins=256, sbins=256):
	#trasform the RGB to HSI
	hs = []
	hi = []
	imghsi = numpy.zeros(img.shape,dtype=numpy.float32)
	for i in range(img.shape[0]):
		for j in range(img.shape[1]):
			imghsi[i][j] = rgb2hsi(img[i][j])
			hs.append(imghsi[i][j][1])
			hi.append(imghsi[i][j][2])

	#histogram for saturation and intensity (S&I)
	hist_s, bins_s = numpy.histogram(hs, sbins , (0.0,1.0), density=False)
	hist_i, bins_i = numpy.histogram(hi, ibins , (0.0,255.0), density=False)

	# pdf and cdf for S and I respectively
	pdf_s = hist_s / numpy.float32(img.size/3.0)
	pdf_i = hist_i / numpy.float32(img.size/3.0)

	cdf_s = pdf_s.cumsum()
	cdf_i = pdf_i.cumsum()
	
	newi = 255.0 * cdf_i
	im = numpy.zeros(img.shape,dtype=numpy.float32)
	for i in range(img.shape[0]):
		for j in range(img.shape[1]):
			im[i][j] = hsi2rgb(( imghsi[i][j][0], imghsi[i][j][1], newi[int(imghsi[i][j][2])] ))
	
	return im

#
# 2-D Equalization for intensity and saturation in the HSI
# @param image array
# @param ibins intensity levels
# @param sbins saturation levels
# @return modified image array
#
# Ref(s):
#	N. Bassiou, C. Kotropoulos, "Color Image Histogram Equalization by 
#	Absolute Discounting Back-off". Computer Vision and Image Understanding,
#	VOL. 107, pp. 108-122(2007).
#

def hsihe_si(img, ibins=256, sbins=256):
	#trasform the RGB to HSI
	hs = []
	hi = []
	imghsi = numpy.zeros(img.shape,dtype=numpy.float32)
	for i in range(img.shape[0]):
		for j in range(img.shape[1]):
			imghsi[i][j] = rgb2hsi(img[i][j])
			hs.append(imghsi[i][j][1])
			hi.append(imghsi[i][j][2])

	#histogram for saturation and intensity (S&I)
	hist_s, bins_s = numpy.histogram(hs, sbins , (0.0,1.0), density=False)
	hist_i, bins_i = numpy.histogram(hi, ibins , (0.0,255.0), density=False)

	# pdf and cdf for S and I respectively
	n_i0 = 0 # the number of intensity values that are not seen in the image
	n_i1 = 0 # the number of intensity values that are seen exactly one time
	n_i2 = 0 # the number of intensity values that are seen exactly two times
	pdf_i = []
	pdf_si = numpy.zeros((ibins,sbins))
	pdf_s = hist_s / numpy.float32(img.size/3.0)
	sn = 1e-9 # small number to avoid divid by zero

	for i in range(ibins):
		if hist_i[i] == 0:
			n_i0 += 1		
		if hist_i[i] == 1:
			n_i1 += 1
		if hist_i[i] == 2:
			n_i2 += 1
	for i in range(ibins): # pdf for intensity
		if hist_i[i] > 0:
			p = (hist_i[i]-n_i1/(n_i1+2.0*n_i2+sn))/numpy.float32(img.size/3.0)
			pdf_i.append(p)
		elif hist_i[i] == 0:
			p = (n_i1/(n_i1+2.0*n_i2+sn)) * ((ibins-n_i0)/numpy.float32(img.size/3.0))*(1.0/(n_i0+sn))
			pdf_i.append(p)
		else:
			print 'error'
			sys.exit(1)

	table_si = numpy.zeros((ibins,sbins))
	for i in range(ibins):
		for j in range(sbins):
			t = (sbins*hs[i*ibins+j])%sbins
			table_si[hi[i*ibins+j]][t] += 1

	n_si1 = 0 # the number of intensity and saturation pairs that are seen exactly one time
	n_si2 = 0 # the number of intensity and saturation pairs that are seen exactly two times
	count_i = numpy.zeros((ibins)) # the number of pixels with the denoted values for intensity
	count_i0 = numpy.zeros((ibins)) # the number of the sturation values that are never seen given that the intensity
	sumpdf_s = numpy.zeros((ibins))	
	for i in range(ibins):
		for j in range(sbins):
			if table_si[i][j] == 1:	
				n_si1 += 1
			if table_si[i][j] == 2:
				n_si2 += 1
			if table_si[i][j] > 0 :
				count_i[i] += table_si[i][j]
			if table_si[i][j] == 0:
				count_i0[i] += 1
				sumpdf_s[i] += pdf_s[j]

	
	for i in range(ibins):
		for j in range(sbins):
			if table_si[i][j] > 0:
				pdf_si[i][j] = (table_si[i][j]-(n_si1/(n_si1+2.0*n_si2+sn)))/numpy.float32(count_i[i]+sn)
			elif table_si[i][j] == 0:
				pdf_si[i][j] = (n_si1/(n_si1+2.0*n_si2+sn))*((sbins-count_i0[i])/(count_i[i]+sn))*(pdf_s[j]/(sumpdf_s[i]+sn))
			else:
				print 'error'
				sys.exit(1)
				
	cdf_i = numpy.asarray(pdf_i).cumsum()
	cdf_si = numpy.zeros((ibins,sbins))
	for i in range(ibins):
		for j in range(sbins):
			for k in range(j):
				cdf_si[i][j] += float(pdf_si[i][k])/float(pdf_i[i])

	newi = 255.0 * cdf_i
	news = cdf_si
	im = numpy.zeros(img.shape,dtype=numpy.float32)
	for i in range(img.shape[0]):
		for j in range(img.shape[1]):
			t = (sbins*imghsi[i][j][1])%sbins
			im[i][j] = hsi2rgb(( imghsi[i][j][0], news[int(imghsi[i][j][2])][t], newi[int(imghsi[i][j][2])] ))
	
	return im	
		
