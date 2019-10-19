import cv2
import numpy as np
from collections import deque
import argparse
import imutils


camera = cv2.VideoCapture('4.mp4')

greenLower = (18, 0, 181)  # Less accurate -> (29,86,6) (17,30,35)
greenUpper = (80, 255, 255) #(76,241,255)

ap = argparse.ArgumentParser()
ap.add_argument("-v", "--video",
	help="path to the (optional) video file")
ap.add_argument("-b", "--buffer", type=int, default=32,
	help="max buffer size")
args = vars(ap.parse_args())

pts = deque(maxlen=args["buffer"])
counter = 0
(dX, dY) = (0, 0)
direction = ""


while camera.isOpened():
    ret, frame = camera.read()

    # blurring the frame that's captured
    frame_gau_blur = cv2.GaussianBlur(frame, (5, 5), 1)

    # converting BGR to HSV
    hsv = cv2.cvtColor(frame_gau_blur, cv2.COLOR_BGR2HSV)

    # the range of blue color in HSV
    # getting the range of blue color in frame
    green_range = cv2.inRange(hsv, greenLower, greenUpper)
    res_green = cv2.bitwise_and(frame_gau_blur,frame_gau_blur, mask=green_range)
    mask = cv2.erode(res_green, None, iterations=2)
    mask = cv2.dilate(mask, None, iterations=3)

    blue_s_gray = cv2.cvtColor(res_green, cv2.COLOR_BGR2GRAY)
    canny_edge = cv2.Canny(blue_s_gray, 200,210)  #100,110
    # applying HoughCircles
    rows=blue_s_gray.shape[0]
    circles = cv2.HoughCircles(canny_edge, cv2.HOUGH_GRADIENT, dp=2, minDist=9, param1=10, param2=10, minRadius=0, maxRadius=0)
    cnts = cv2.findContours(blue_s_gray.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]

    #cnts = imutils.grab_contours(cnts)

    center = None
    #print (circles)
    if len(cnts) > 0 and circles is not None:
        c = max(cnts, key=cv2.contourArea)
        (x, y), radius = cv2.minEnclosingCircle(c)
        M = cv2.moments(c)
        center = (int(M['m10'] / M['m00']), int(M['m01'] / M['m00']))
        # Select contours with a size bigger than 0.1
        if radius > 0.2:
             # draw the circle and center
            #print("Ball is Found !!")
            #print(x,y)
            #print(radius)
            cv2.circle(frame, (int(x), int(y)), int(radius), (0, 255, 255), 2)
            cv2.circle(frame, center, 5, (0, 0, 255), -1)
            pts.appendleft(center)
            print("x:",x,"y:",y)
    # loop over the set of tracked points
    for i in np.arange(1, len(pts)):
        # if either of the tracked points are None, ignore
        # them
        if pts[i - 1] is None or pts[i] is None:
            continue

        # check to see if enough points have been accumulated in
        # the buffer
        if counter >= 10 and i == 1 and pts[-10] is not None:
            # compute the difference between the x and y
            # coordinates and re-initialize the direction
            # text variables
            dX = pts[-10][0] - pts[i][0]
            dY = pts[-10][1] - pts[i][1]
            (dirX, dirY) = ("", "")

        # otherwise, compute the thickness of the line and
        # draw the connecting lines
        thickness = int(np.sqrt(args["buffer"] / float(i + 1)) * 3.5)
        #cv2.line(frame, pts[i - 1], pts[i], (170, 0, 0), thickness)

    cv2.imshow('circles', frame)
    #cv2.imshow('gray', blue_s_gray)
    #cv2.imshow('canny', canny_edge)
    if cv2.waitKey(25) & 0xFF == ord('q'):
        break
camera.release()
cv2.destroyAllWindows()



