# cross-correlation.py
# 
# a simple test of the cross-correlation (template matching) that OpenCV offers.
# (c) Ryan Jensen, 2019

# import libraries
import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt

# load your images
img_A = cv.imread('./A.png', cv.IMREAD_COLOR)
img_B = cv.imread('./B.png', cv.IMREAD_COLOR)
#cv.namedWindow('image', cv.WINDOW_NORMAL)
cv.imshow('A', img_A)
cv.imshow('B', img_B)

cv.imwrite('./output/absdiff,A,B.png',cv.absdiff(img_A, img_B))
cv.imwrite('./output/absdiff==0',img_out == )

#cv.matchTemplate(, method= )



#cv.waitKey(0)
#cv.destroyAllWindows()


