#
# Single Image Haze Removal Using Dark Channel Prior
#
# Ref(s):
#	K. He, J. Sun, and X. Tang. "Single Image Haze Removal Using Dark Channel 
#	Prior". In CVPR, IEEE, pp. 1956-1963(2009).
#
# Notice:
#       Please make sure the input image has RGB channels, not gray or any other
#       format of picture. Otherwise, the program will crash.
#
# 2013 Mar
#

import sys
import math
import numpy
import numpy.lib
import scipy
import pylab
from PIL import Image 

'''
Function: get dark channel prior
Pramater: img array, patch size (default 15)
'''

def makeDarkChannel(img, patch_size=15):
    # Assuming image is RGB format
    [image_x, image_y, channels] = numpy.shape(img)
    darkC = numpy.zeros((image_x, image_y)) # Dark Channel
    tmpPatch = numpy.double(numpy.zeros(2 * numpy.floor(patch_size / 2), 2 * numpy.floor(patch_size / 2), channels))

    I = numpy.lib.pad(img, (numpy.floor(patch_size/2), numpy.floor(patch_size/2)), 'symmetric')

    # Use original image_x, image_y and add 2*floor(patch_size/2)
    for i in range(image_x):
        minX = i
        maxX = (i + 2 * numpy.floor(patch_size / 2))
        for j in range(image_y):
            minY = j
            maxY = (j + 2 * numpy.floor(patch_size / 2))

            # copy all color channels over
            tmpPatch = I[minX:maxX, minY:maxY,:]
            darkC[i][j] = tmpPatch.min()       # find min in all channels
    
    return darkC

'''
Function: use dark channel prior to get the atmospheric light
Pramater: image array, dark channel, number of pixels represent the brightest region(usually 0.1% of total)
'''

def estimateA(img, darkC, numPixels):

    # Make a list of the brightest pixels
    brightestL = numpy.zeros((numPixels, 3))
    [x_dim, y_dim] = numpy.shape(darkC)
    for i in range(x_dim):
        for j in range(y_dim):
            minElement = brightestL[:, 2].min()
	    index = numpy.argmax(brightestL[:,2])
            if darkC[i, j] > minElement:
                brightestL[index] = [i, j, darkC[i, j]]

    # Find the brightest intensity pixel from the original Image using the list above
    brightestIntensity = numpy.zeros(3)
    for i in range(numPixels):
        x = brightestL[i, 0]
        y = brightestL[i, 1]
        intensity = numpy.sum(img[x, y, :])
        if intensity > numpy.sum(brightestIntensity):
            brightestIntensity = img[x, y, :]

    # the Atmosphere lighting
    dimI = numpy.shape(img)
    air = numpy.zeros((x_dim, y_dim, 3))
    for i in range(dimI[2]):
	for j in range(x_dim):
    	    for k in range(y_dim):
       		air[j, k, i] = air[j, k, i] + brightestIntensity[i]
    
    return air

'''
Function: Remove Haze
Parameter: image array, patch size
'''

def removeHaze(img, patch_size):
    #img = Image.open(imgfile)
    aerialPerspective = 0.95 # a constant parameter introduced in paper

    I = numpy.double(img) / 255

    J = makeDarkChannel(I, patch_size)

    # Estimate Atmosphere
    dimJ = numpy.shape(J)
    numBrightestPixels = numpy.ceil(0.001 * dimJ[0] * dimJ[1])

    A = estimateA(I, J, numpy.int(numBrightestPixels))

    # Estimate the Transmission
    T_est = 1 - aerialPerspective * makeDarkChannel(I/A, patch_size)

    dehazed = numpy.zeros(numpy.shape(I))

    for c in range(3):
        dehazed[:, :, c] = (I[:, :, c] - A[:, :, c])/ (numpy.max(T_est, .1)) + A[:, :, c]


    return dehazed

