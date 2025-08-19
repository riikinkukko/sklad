import time

import cv2
import serial

#ser = serial.Serial('COM11', 115200)
time.sleep(3)
#ser.reset_input_buffer()
#ser.reset_output_buffer()
#ser.write("QR1".encode())
print('QR1')
#print(ser.readline().decode())
def QR():
    cap = cv2.VideoCapture(1)

    # инициализируем детектор QRCode cv2
    detector = cv2.QRCodeDetector()
    while True:
        _, img = cap.read()
        # обнаружить и декодировать

        ret_qr, decoded_info, points, _ = detector.detectAndDecodeMulti(img)

        if ret_qr:
            for s, p in zip(decoded_info, points):
                if s:
                    print(s)
                    return 0
        # отобразить результат
        cv2.imshow("img", img)
        if cv2.waitKey(1) == ord("q"):
            break
    cap.release()
    cv2.destroyAllWindows()

qr_state = QR()

while qr_state:
    qr_state = QR()
ser.write("QR2".encode())