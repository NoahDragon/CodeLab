#
# This is example code for how to using the functions in ColorImageHE.py
# and GCEHistMod.py
#

from ColorImageHE import *
from GCEHistMod import *
from numpy import *
import scipy

# Color space conversion, from RGB to HSI and from HSI to RGB
print "Color Space Conversion:"
h = rgb2hsi((15,100,255))
print "H:", h[0]
print "S:", h[1]
print "I:", h[2]
r = hsi2rgb(h)
print "R:", r[0]
print "G:", r[1]
print "B:", r[2]

# GCEHistMod
print "GCEHistMod example (please check the directory for output image):"
f = Image.open("Meije_Gray.jpg").convert('L')
o = numpy.asarray(f)
img, hist = gcehistmod(o, 10, 5, 230, 23, 2)
scipy.misc.imsave("ExampleofGCEHistMod.jpg", img)

# ColorImageHE
img = Image.open("1.jpg")
imga = numpy.asarray(img)

print "Equalization of Intensity example (please check the directory for output image):"
im = hsihe_i(imga) # Equalization of the intensity component in the HSI space
scipy.misc.imsave("ExampleofHSI01.jpg", im)

print "Equalization of Intensity and Saturation example (please check the directory for output image):"
im = hsihe_si(imga) # Equalization for intensity and saturation in the HSI space
scipy.misc.imsave("ExampleofHSI02.jpg", im)
