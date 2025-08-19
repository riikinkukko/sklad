from __future__ import print_function
import requests
import time
import math
import cv2
import sys
import numpy as np
import serial


ser = serial.Serial('COM12', 9600)
desired_aruco_dictionary = "DICT_4X4_100"
ser.reset_input_buffer()
ser.reset_output_buffer()
ARUCO_DICT = {
    "DICT_4X4_50": cv2.aruco.DICT_4X4_50,
    "DICT_4X4_100": cv2.aruco.DICT_4X4_100,
    "DICT_4X4_250": cv2.aruco.DICT_4X4_250,
    "DICT_4X4_1000": cv2.aruco.DICT_4X4_1000,
    "DICT_5X5_50": cv2.aruco.DICT_5X5_50,
    "DICT_5X5_100": cv2.aruco.DICT_5X5_100,
    "DICT_5X5_250": cv2.aruco.DICT_5X5_250,
    "DICT_5X5_1000": cv2.aruco.DICT_5X5_1000,
    "DICT_6X6_50": cv2.aruco.DICT_6X6_50,
    "DICT_6X6_100": cv2.aruco.DICT_6X6_100,
    "DICT_6X6_250": cv2.aruco.DICT_6X6_250,
    "DICT_6X6_1000": cv2.aruco.DICT_6X6_1000,
    "DICT_7X7_50": cv2.aruco.DICT_7X7_50,
    "DICT_7X7_100": cv2.aruco.DICT_7X7_100,
    "DICT_7X7_250": cv2.aruco.DICT_7X7_250,
    "DICT_7X7_1000": cv2.aruco.DICT_7X7_1000,
    "DICT_ARUCO_ORIGINAL": cv2.aruco.DICT_ARUCO_ORIGINAL
}

dict_dist = {
    "0": 100,
    "1": 60,
    "2": 50,
    "3": 60,
    "4": 70
}
obj_size = 100
focal_length = 3.7

def get_data_list():
    url = 'https://riikinkukko.pythonanywhere.com/api/data/'
    response = requests.get(url)
    if response.status_code == 200:
        data_list = response.json()
        return data_list
    else:
        print(f"Error: Unable to fetch data. Status code: {response.status_code}")
    return None
data_list = get_data_list()
while data_list == []:
    data_list = get_data_list()
def forward(frame, now_id, this_aruco_dictionary, this_aruco_parameters):
    """ДВИГАЕТСЯ ПРЯМО!!!"""
    flag = 1
    while flag:
        (corners, ids, rejected) = cv2.aruco.detectMarkers(frame, this_aruco_dictionary,
                                                           parameters=this_aruco_parameters)
        print(len(corners))
        if len(corners) > 0:
            ids = ids.flatten()
            for (marker_corner, marker_id) in zip(corners, ids):
                if flag == 0:
                    break

                corners = marker_corner.reshape((4, 2))
                (top_left, top_right, bottom_right, bottom_left) = corners
                # Convert the (x,y) coordinate pairs to integers
                top_right = (int(top_right[0]), int(top_right[1]))
                bottom_right = (int(bottom_right[0]), int(bottom_right[1]))
                bottom_left = (int(bottom_left[0]), int(bottom_left[1]))
                top_left = (int(top_left[0]), int(top_left[1]))
                # прорисовка
                """cv2.line(frame, top_left, top_right, (0, 255, 0), 2)
                cv2.line(frame, top_right, bottom_right, (0, 255, 0), 2)
                cv2.line(frame, bottom_right, bottom_left, (0, 255, 0), 2)
                cv2.line(frame, bottom_left, top_left, (0, 255, 0), 2)

                center_x = int((top_left[0] + bottom_right[0]) / 2.0)
                center_y = int((top_left[1] + bottom_right[1]) / 2.0)
                cv2.circle(frame, (center_x, center_y), 4, (0, 0, 255), -1)"""
                x1_l, y1_l = top_left
                x2_l, y2_l = bottom_left
                x1_r, y1_r = top_right
                x2_r, y2_r = bottom_right
                x1 = (abs(x1_l) + abs(x1_r)) // 2
                x2 = (abs(x2_l) + abs(x2_r)) // 2
                y1 = (abs(y1_l) + abs(y1_r)) // 2
                y2 = (abs(y2_r) + abs(y2_l)) // 2
                image_size = ((x1 - x2) ** 2 + (y1 - y2) ** 2) ** 0.5
                distance = (focal_length * obj_size / image_size) * 16.89
                # print(distance, f, abs(((x1_l-x2_l)**2+(y1_l-y2_l)**2)**0.5-((x1_r-x2_r)**2+(y1_r-y2_r)**2)**0.5)*0.5437, marker_id)
                # print(abs(((x1_l-x2_l)**2+(y1_l-y2_l)**2)**0.5-((x1_r-x2_r)**2+(y1_r-y2_r)**2)**0.5)*0.5437, ids, distance)
                if marker_id == now_id:
                    if int(distance) >= (dict_dist[str(marker_id)]) and flag == 1:
                        ser.write("FORWARD".encode())
                        print(distance)# ser.readline().decode())
                        print("forward")
                        return 1

                    else:
                        ser.write("STOP".encode())
                        #print(distance, "stop 1", ser.readline().decode())
                        time.sleep(5)
                        flag = 0
                        return 0
def right(frame, now_id, this_aruco_dictionary, this_aruco_parameters):
    """ПОВОРОТ НАПРАВО"""
    flag = 1
    while flag:
        cameraMatrix = np.array([[1000, 0, 320], [0, 1000, 240], [0, 0, 1]])
        distCoeffs = np.zeros((5, 1))
        (corners, ids, rejected) = cv2.aruco.detectMarkers(frame, this_aruco_dictionary,
                                                           parameters=this_aruco_parameters)
        if len(corners) > 0:
            ids = ids.flatten()
            print("wtf")
            for (marker_corner, marker_id) in zip(corners, ids):
                if flag == 0:
                    break
                corners = marker_corner.reshape((4, 2))
                (top_left, top_right, bottom_right, bottom_left) = corners
                # Convert the (x,y) coordinate pairs to integers
                top_right = (int(top_right[0]), int(top_right[1]))
                bottom_right = (int(bottom_right[0]), int(bottom_right[1]))
                bottom_left = (int(bottom_left[0]), int(bottom_left[1]))
                top_left = (int(top_left[0]), int(top_left[1]))
                # прорисовка
                """cv2.line(frame, top_left, top_right, (0, 255, 0), 2)
                cv2.line(frame, top_right, bottom_right, (0, 255, 0), 2)
                cv2.line(frame, bottom_right, bottom_left, (0, 255, 0), 2)
                cv2.line(frame, bottom_left, top_left, (0, 255, 0), 2)

                center_x = int((top_left[0] + bottom_right[0]) / 2.0)
                center_y = int((top_left[1] + bottom_right[1]) / 2.0)
                cv2.circle(frame, (center_x, center_y), 4, (0, 0, 255), -1)"""
                x1_l, y1_l = top_left
                x2_l, y2_l = bottom_left
                x1_r, y1_r = top_right
                x2_r, y2_r = bottom_right
                x1 = (abs(x1_l) + abs(x1_r)) // 2
                x2 = (abs(x2_l) + abs(x2_r)) // 2
                y1 = (abs(y1_l) + abs(y1_r)) // 2
                y2 = (abs(y2_r) + abs(y2_l)) // 2
                image_size = ((x1 - x2) ** 2 + (y1 - y2) ** 2) ** 0.5
                distance = (focal_length * obj_size / image_size) * 16.89
                check_difference = abs(((x1_l - x2_l) ** 2 + (y1_l - y2_l) ** 2) ** 0.5 - (
                            (x1_r - x2_r) ** 2 + (y1_r - y2_r) ** 2) ** 0.5) * 0.5437 < 1
                for i in range(len(ids)):
                    if ids[i] == now_id:
                        rvec, tvec, _ = cv2.aruco.estimatePoseSingleMarkers(corners[i], 0.25, cameraMatrix, distCoeffs)
                        if rvec is not None and rvec.size > 0:
                            rvec = rvec.flatten()

                            R, _ = cv2.Rodrigues(rvec)

                            sy = math.sqrt(R[0, 0] * R[0, 0] + R[1, 0] * R[1, 0])
                            singular = sy < 1e-6
                            if not singular:
                                x = math.atan2(R[2, 1], R[2, 2])
                                y = math.atan2(-R[2, 0], sy)
                                z = math.atan2(R[1, 0], R[0, 0])
                            else:
                                x = math.atan2(-R[1, 2], R[1, 1])
                                y = math.atan2(-R[2, 0], sy)
                                z = 0

                            eulerAngles = np.array([x, y, z]) * 180 / np.pi

                            if abs(eulerAngles[1]) > 10 and marker_id == now_id and flag == 1:
                                # if check_difference and marker_id == now_id and flag == 1:
                                ser.write("STOP".encode())
                                time.sleep(5)
                                # print(distance, ser.readline().decode(), "s")
                                flag = 0
                                return 0
                    #if check_difference and marker_id == now_id and flag == 1:
                        # response = ser.readline()
                        # decoded_response = response.decode('utf-8')
                        # print(decoded_response)
                        elif marker_id == now_id and flag == 1:
                            ser.write("RIGHT".encode())
                        #print(check_difference, "r 1", ser.readline().decode())
                            return 1
        ser.write("RIGHT".encode())
        #print("r 2", ser.readline().decode())
        #time.sleep(0.5)
        return 1
def left(cap, now_id, this_aruco_dictionary, this_aruco_parameters):
    """ПОВОРОТ НАЛЕВО"""
    cameraMatrix = np.array([[1000, 0, 320], [0, 1000, 240], [0, 0, 1]])
    distCoeffs = np.zeros((5, 1))
    flag = 1
    while flag:
        ret, frame = cap.read()
        (corners, ids, rejected) = cv2.aruco.detectMarkers(frame, this_aruco_dictionary,
                                                           parameters=this_aruco_parameters)
        if len(corners) > 0:
            ids = ids.flatten()

            for (marker_corner, marker_id) in zip(corners, ids):
                if flag == 0:
                    break
                corners = marker_corner.reshape((4, 2))
                (top_left, top_right, bottom_right, bottom_left) = corners
                # Convert the (x,y) coordinate pairs to integers
                top_right = (int(top_right[0]), int(top_right[1]))
                bottom_right = (int(bottom_right[0]), int(bottom_right[1]))
                bottom_left = (int(bottom_left[0]), int(bottom_left[1]))
                top_left = (int(top_left[0]), int(top_left[1]))
                # прорисовка
                """cv2.line(frame, top_left, top_right, (0, 255, 0), 2)
                cv2.line(frame, top_right, bottom_right, (0, 255, 0), 2)
                cv2.line(frame, bottom_right, bottom_left, (0, 255, 0), 2)
                cv2.line(frame, bottom_left, top_left, (0, 255, 0), 2)

                center_x = int((top_left[0] + bottom_right[0]) / 2.0)
                center_y = int((top_left[1] + bottom_right[1]) / 2.0)
                cv2.circle(frame, (center_x, center_y), 4, (0, 0, 255), -1)"""
                x1_l, y1_l = top_left
                x2_l, y2_l = bottom_left
                x1_r, y1_r = top_right
                x2_r, y2_r = bottom_right
                x1 = (abs(x1_l) + abs(x1_r)) // 2
                x2 = (abs(x2_l) + abs(x2_r)) // 2
                y1 = (abs(y1_l) + abs(y1_r)) // 2
                y2 = (abs(y2_r) + abs(y2_l)) // 2
                image_size = ((x1 - x2) ** 2 + (y1 - y2) ** 2) ** 0.5
                distance = (focal_length * obj_size / image_size) * 16.89
                check_difference = abs(((x1_l - x2_l) ** 2 + (y1_l - y2_l) ** 2) ** 0.5 - (
                        (x1_r - x2_r) ** 2 + (y1_r - y2_r) ** 2) ** 0.5) * 0.5437 < 2
                for i in range(len(ids)):
                    if ids[i] == now_id:
                        rvec, tvec, _ = cv2.aruco.estimatePoseSingleMarkers(corners[i], 0.25, cameraMatrix, distCoeffs)
                        if rvec is not None and rvec.size > 0:
                            rvec = rvec.flatten()

                            R, _ = cv2.Rodrigues(rvec)

                            sy = math.sqrt(R[0, 0] * R[0, 0] + R[1, 0] * R[1, 0])
                            singular = sy < 1e-6
                            if not singular:
                                x = math.atan2(R[2, 1], R[2, 2])
                                y = math.atan2(-R[2, 0], sy)
                                z = math.atan2(R[1, 0], R[0, 0])
                            else:
                                x = math.atan2(-R[1, 2], R[1, 1])
                                y = math.atan2(-R[2, 0], sy)
                                z = 0

                            eulerAngles = np.array([x, y, z]) * 180 / np.pi

                            if abs(eulerAngles[1]) > 10 and marker_id == now_id and flag == 1:
                                # if check_difference and marker_id == now_id and flag == 1:
                                ser.write("STOP".encode())
                                time.sleep(5)
                                # print(distance, ser.readline().decode(), "s")
                                flag = 0
                                return 0
                        # if check_difference and marker_id == now_id and flag == 1:
                        # response = ser.readline()
                        # decoded_response = response.decode('utf-8')
                        # print(decoded_response)
                        elif marker_id == now_id and flag == 1:
                            ser.write("RIGHT".encode())
                            # print(check_difference, "r 1", ser.readline().decode())
                            return 1
        ser.write("LEFT".encode())
        #print("l 2", ser.readline().decode())
        return 1
        #cv2.imshow('frame', frame)



def main():
    # Check that we have a valid ArUco marker
    if ARUCO_DICT.get(desired_aruco_dictionary, None) is None:
        print("[INFO] ArUCo tag of '{}' is not supported".format(
            args["type"]))
        sys.exit(0)

    # Load the ArUco dictionary
    print("[INFO] detecting '{}' markers...".format(
        desired_aruco_dictionary))
    #this_aruco_dictionary = cv2.aruco.Dictionary_get(ARUCO_DICT[desired_aruco_dictionary])
    this_aruco_dictionary = cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_4X4_100) #!
    #this_aruco_parameters = cv2.aruco.DetectorParameters_create()
    this_aruco_parameters = cv2.aruco.DetectorParameters()
    # Start the video stream
    cap = cv2.VideoCapture(0)
    print('START')
    f = 1
    while f == 1:
        f = forward(cap, 0, this_aruco_dictionary, this_aruco_parameters)
    f = 1
    while f == 1:
        f = left(cap, 1, this_aruco_dictionary, this_aruco_parameters)
    f = 1
    while f == 1:
        f = forward(cap, 1, this_aruco_dictionary, this_aruco_parameters)
    while f == 1:
        f = right(cap, 2, this_aruco_dictionary, this_aruco_parameters)


if __name__ == '__main__':
    print(__doc__)
    main()
