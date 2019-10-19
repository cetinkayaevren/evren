import cv2
import numpy as np

cap = cv2.VideoCapture(0)
if cap.isOpened():
    while(True):
        ret, frame = cap.read()
        # blurring the frame that's captured
        frame_gau_blur = cv2.GaussianBlur(frame, (5, 5), 0)
        #for hough circle
        gray=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
        abc = cv2.medianBlur(frame,5)
        # converting BGR to HSV
        hsv = cv2.cvtColor(frame_gau_blur, cv2.COLOR_BGR2HSV)
        # the range of blue color in HSV
        lower_blue = np.array([19, 28, 93])
        higher_blue = np.array([73, 123, 244])
        # getting the range of blue color in frame
        blue_range = cv2.inRange(hsv, lower_blue, higher_blue)
        res_blue = cv2.bitwise_and(frame_gau_blur,frame_gau_blur, mask=blue_range)
        blue_s_gray = cv2.cvtColor(res_blue, cv2.COLOR_BGR2GRAY)
        circles = cv2.HoughCircles(blue_s_gray, cv2.HOUGH_GRADIENT, dp=1, minDist=10, param1=100, param2=12,
                                   minRadius=0,
                                   maxRadius=0)
        canny_edge = cv2.Canny(blue_s_gray,60,80)
        # applying Histogram
        dst = cv2.equalizeHist(gray)

        #circles = np.uint16(np.around(circles))
        cnts = cv2.findContours(blue_s_gray.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
        center=None

        if circles is not None and canny_edge is not None:
                print("I  found circle!")
                if len(cnts) > 0:
                    c = max(cnts, key=cv2.contourArea)
                    (x, y), radius = cv2.minEnclosingCircle(c)
                    M = cv2.moments(c)
                    center = (int(M['m10'] / M['m00']), int(M['m01'] / M['m00']))
                    # Select contours with a size bigger than 0.1
                    if radius > 0.2:
                        # draw the circle and center
                        cv2.circle(frame, (int(x), int(y)), int(radius), (0, 255, 255), 2)
                        cv2.circle(frame, center, 5, (0, 0, 255), -1)

        else:
            print("circle yok")
        cv2.imshow('circles', frame)
        cv2.imshow('gray', blue_s_gray)
        cv2.imshow('canny', canny_edge)
        cv2.imshow('histogram', dst)
        if cv2.waitKey(25) & 0xFF == ord('q'):
            break

cv2.destroyAllWindows()

