# example code for HazeRemoval.py

from HazeRemoval import *
from numpy import *
import scipy

img = Image.open("beijing.jpg")
#img = Image.open("forest.jpg")
imga = numpy.asarray(img)

# get dark channel prior
#J = makeDarkChannel(imga, patch_size=15)
#print J
#scipy.misc.imsave("test.jpg", J)

# get global atmospheric light
#A = estimateA(imga, J,240 )
#print A
#scipy.misc.imsave("test.jpg", A)

#get dehazed image
Dehazed = removeHaze(imga,15)
scipy.misc.imsave("beijingtest.jpg", Dehazed)
