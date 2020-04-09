import cv2
import numpy as np

def nothing(x):
    # any operation
    pass

cap = cv2.VideoCapture(0)

cv2.namedWindow("Trackbars")
cv2.createTrackbar("Lower-Hue", "Trackbars", 0, 180, nothing)
cv2.createTrackbar("Lower-Saturation", "Trackbars", 66, 255, nothing)
cv2.createTrackbar("Lower-Value", "Trackbars", 134, 255, nothing)
cv2.createTrackbar("Upper-Hue-H", "Trackbars", 180, 180, nothing)
cv2.createTrackbar("Upper-Saturation-S", "Trackbars", 255, 255, nothing)
cv2.createTrackbar("Upper-Value-V", "Trackbars", 243, 255, nothing)

font = cv2.FONT_HERSHEY_COMPLEX

while True:
    _, frame = cap.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    u_h = cv2.getTrackbarPos("Upper-Hue", "Trackbars")
    u_s = cv2.getTrackbarPos("Upper-Saturation", "Trackbars")
    u_v = cv2.getTrackbarPos("Upper-Value", "Trackbars")
    l_h = cv2.getTrackbarPos("Lower-Hue", "Trackbars")
    l_s = cv2.getTrackbarPos("Lower-Saturation", "Trackbars")
    l_v = cv2.getTrackbarPos("Lower-Value", "Trackbars")


    lower_red = np.array([l_h, l_s, l_v])
    upper_red = np.array([u_h, u_s, u_v])

    mask = cv2.inRange(hsv, lower_red, upper_red)
    kernel = np.ones((5, 5), np.uint8)
    mask = cv2.erode(mask, kernel)

    # Contours detection
    _, contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    for cnt in contours:
        area = cv2.contourArea(cnt)
        approx = cv2.approxPolyDP(cnt, 0.02*cv2.arcLength(cnt, True), True)
        x = approx.ravel()[0]
        y = approx.ravel()[1]

        if area > 400:
            cv2.drawContours(frame, [approx], 0, (0, 0, 0), 5)
            if 10 < len(approx) < 20:
                cv2.putText(frame, "Circle", (x, y), font, 1, (0, 0, 0))


    cv2.imshow("Frame", frame)
    cv2.imshow("Mask", mask)

    key = cv2.waitKey(1)
    if key == 27:
        break

cap.release()
cv2.destroyAllWindows()