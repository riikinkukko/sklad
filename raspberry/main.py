import requests
import serial
import time
import cv2
from pyzbar.pyzbar import decode
from ultralytics import YOLO
arduino = serial.Serial("/dev/ttyUSB0", 115200)
time.sleep(2)
arduino.reset_input_buffer()
model = YOLO('best_sklad_v8')

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

def calculate_angles(start, target, link1_length, link2_length):
    a = math.atan2(target["y"] - start["y"], target["x"] - start["x"]) + math.pi / 2

    delta = math.sqrt(
        (target["y"] - start["y"])**2 +
        (target["x"] - start["x"])**2 +
        (target["z"] - start["z"])**2
    )

    max_reach = link1_length + link2_length
    if delta > max_reach:
        delta = max_reach

    a2 = math.pi - 2 * math.asin((delta / 2) / link2_length)

    xy_proj = math.sqrt(
        (target["y"] - start["y"])**2 +
        (target["x"] - start["x"])**2
    )

    a3 = math.atan2(xy_proj, target["z"] - start["z"]) - math.acos((delta / 2) / link2_length) + math.pi / 2

    return {
        "base_angle": math.degrees(a),
        "segment1_angle": math.degrees(a3),
        "segment2_angle": math.degrees(a2)
    }
start = {"x": 0, "y": 260, "z": 0}
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
                    if arduino.readline().decode() != "QR":
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
                        print(arduino.readline().decode())
            if a == 'detect':
                results = model(img, save=True)
                boxes = results[0].boxes.xyxy
                boxes_new = boxes.numpy()
            else:
                break
