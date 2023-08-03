import cv2
import numpy as np
import filt
  
def contours(cont):
    if len(cont)!=0:
        #contours_ball = cv2.drawContours(image, cont, -1,(0,0,0),3)
        M=cv2.moments(cont[0])
        area=M["m00"]
        largestcontours=cont[0]
        for i in cont:
            M2=cv2.moments(i)
            area2=M2["m00"]
            #print(area2)
            if area2>area:
                largestcontours=i
                area=area2
                
        M6=cv2.moments(largestcontours)
        if area>15000:
            return True,255,0
        if area<50:
            return False,0,0
            
        if M6["m00"]!=0:
            cX = int(M6["m10"] / M6["m00"])
            cY = int(M6["m01"] / M6["m00"])
            #print(area)
            if cX>=255:
                cX=254
            return True,cX,cY
    else:
        circletest=False
        return False,0,0
