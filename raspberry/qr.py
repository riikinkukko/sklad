import cv2
from pyzbar.pyzbar import decode


def QR(image):
    try:
       obj = decode(image)
    except:
       return 0
    try:
       data = obj[0].data
    except IndexError:
       return 0
    new_data = list(map(str, data.decode().split(",")))
    return new_data
    
cap = cv2.VideoCapture(0)
data = 0
while data == 0:
	_, img = cap.read()
			
	data = QR(img)
	
	print(data)
