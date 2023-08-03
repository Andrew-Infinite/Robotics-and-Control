import cv2
import numpy as np
  
# path

def customfilter(image,color,target):
    image_hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    
    if color=="green":
        lo = np.array([40, 30, 50])
        hi = np.array([90, 255, 255])
        mask2=cv2.inRange(image_hsv,lo,hi)
    elif color=="red":
        if target=="wall":
            lo = np.array([160, 50, 50])
            hi = np.array([200, 255, 255])
            lo2 = np.array([0, 50, 50])
            hi2 = np.array([10, 255, 255])
        elif target=="ball":
            lo = np.array([160, 100, 50])
            hi = np.array([255, 255, 255])
            lo2 = np.array([0, 100, 50])
            hi2 = np.array([10, 255, 255])
        
        mask2=cv2.inRange(image_hsv,lo,hi)
        mask3=cv2.inRange(image_hsv,lo2,hi2)
        mask2=cv2.bitwise_or(mask2,mask3)
    elif color=="blue":
        lo = np.array([100, 100, 50])
        hi = np.array([125, 255, 255])
        mask2=cv2.inRange(image_hsv,lo,hi)
    elif color=="yellow":
        lo = np.array([20,50, 50])
        hi = np.array([40, 255, 255])
        mask2=cv2.inRange(image_hsv,lo,hi)
    elif color=="purple":
        lo = np.array([125, 50, 50])
        hi = np.array([155, 255, 255])
        mask2=cv2.inRange(image_hsv,lo,hi)
        
    cv2.imshow("hi",mask2)
    if target=="ball":
        kernel = np.ones((15,15),np.uint8)
        filimg = cv2.erode(mask2,kernel,iterations = 1)
        #filimg = cv2.erode(mask2,kernel,iterations = 1)
        #filimg = cv2.dilate(filimg,kernel,iterations = 1)
        filimg = cv2.dilate(filimg,np.ones((25,25),np.uint8),iterations = 1)
        #filimg = cv2.dilate(filimg,kernel,iterations = 1)
        #filimg = cv2.dilate(filimg,kernel,iterations = 1)
    elif target=="wall":
        kernel = np.ones((3,3),np.uint8)
        filimg = cv2.erode(mask2,kernel,iterations = 1)
        #filimg = cv2.erode(mask2,kernel,iterations = 1)
        #filimg = cv2.dilate(filimg,kernel,iterations = 1)
        filimg = cv2.dilate(filimg,np.ones((5,5),np.uint8),iterations = 1)
        #filimg = cv2.dilate(filimg,kernel,iterations = 1)
        #filimg = cv2.dilate(filimg,kernel,iterations = 1)

    image=cv2.bitwise_and(image,image,mask=filimg)
    
    return image,filimg

