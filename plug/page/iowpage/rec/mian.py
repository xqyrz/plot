import cv2

img = cv2.imread("slider.png")
cv2.imwrite("output.png", img, [int(cv2.IMWRITE_PNG_COMPRESSION), 95])
cv2.waitKey(0)
cv2.destroyAllWindows()