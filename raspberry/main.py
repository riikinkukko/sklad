import requests
import serial
import time
import cv2
from pyzbar.pyzbar import decode

arduino = serial.Serial("/dev/ttyUSB0", 115200)
time.sleep(2)
arduino.reset_input_buffer()

def get_data_list():
    url = 'https://riikinkukko.pythonanywhere.com/api/data/'
    response = requests.get(url)
    if response.status_code == 200:
        data_list = response.json()
        return data_list
    else:
        print(f"Error: Unable to fetch data. Status code: {response.status_code}")
    return None

def QR(image):
    try:
       obj = decode(image)
    except:
       return 0
    try:
        data = obj[0].data
    except IndexError:
       return 0
    print(data)
    new_data = list(map(str, data.decode().split(",")))
    return new_data

while True:
    data_list = get_data_list()
    time.sleep(0.01)
    a = 0
    if data_list is not None and data_list != []:
        arduino.write("START".encode())
        c = 0
        while arduino.readline().decode() != 'END':
            if arduino.in_waiting > 0:
                a = arduino.readline().decode()
                print(a)
            if a == 'QR':
                cap = cv2.VideoCapture(0)
                _, img = cap.read()
                data = QR(img) # Выход будет: ["А1"]
                c += 1

                while data == 0:
                    _, img = cap.read()
                    data = QR(img)
                for elem in data:
                    if elem in data_list:
                        arduino.write("TAKE".encode())
                        data_list.remove(elem)
                while arduino.readline().decode() != "QR" and c < 4:
                    cap = cv2.VideoCapture(0)
                    _, img = cap.read()
                    data = QR(img)  # Выход будет: ["А1"]
                    c += 1

                    while data == 0:
                        _, img = cap.read()
                        data = QR(img)
                    for elem in data:
                        if elem in data_list:
                            arduino.write("TAKE".encode())
                            data_list.remove(elem)
            else:
                break
