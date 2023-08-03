import cv2
import numpy as np
import filt
import center
import com
import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
GPIO.setup(37, GPIO.IN)

 
# path
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_BUFFERSIZE, 1);
LastX=128
while(True):
    
    catchMessage = GPIO.input(37)
    #capture camera
    ret, image = cap.read()
    image = cv2.resize(image,(255,143))
    
    if catchMessage == 0:
        #filter
        image,mask=filt.customfilter(image,"red","ball")
    else:
        #filter
        image,mask=filt.customfilter(image,"yellow","wall")
        
    #contours search
    
    contours,_ =cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    
    circletest,cX,cY=center.contours(contours)
    cv2.putText(image, ".", (cX, cY),cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 5)
    cv2.imshow("asdfasdf", image)
    if circletest==False:
        if LastX<128:
            cX=0
        else:
            cX=254
    #print(cX)
    com.send(cX)
    LastX=cX
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
  
#waits for user to press any key  
#(this is necessary to avoid Python kernel form crashing) 
  
#closing all open windows  
cap.release() 
cv2.destroyAllWindows()