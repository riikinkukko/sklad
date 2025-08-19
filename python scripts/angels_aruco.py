import cv2
import numpy as np

# Aruco параметры
arucoDict = cv2.aruco.Dictionary_get(cv2.aruco.DICT_4X4_100)
arucoParams = cv2.aruco.DetectorParameters_create()

# Загрузка видеопотока (или изображения)
cap = cv2.VideoCapture(0) # 0 - номер вашей веб-камеры

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Преобразование изображения в оттенки серого
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Обнаружение маркеров Aruco
    corners, ids, rejected = cv2.aruco.detectMarkers(gray, arucoDict, parameters=arucoParams)

    # Отрисовка маркеров
    frame = cv2.aruco.drawDetectedMarkers(frame, corners, ids)

    if ids is not None:
        for i, corner in enumerate(corners):
            # Получение угла поворота
            rvec, tvec, _ = cv2.aruco.estimatePoseSingleMarkers(corner, 1, None, None) # 0.05 - предполагаемый размер маркера

            if rvec is not None:
                # Преобразование вектора вращения в угол Эйлера
                rvec = rvec[0, 0, :]
                rotM = np.zeros(shape=(3, 3))
                cv2.Rodrigues(rvec, rotM)
                eulerAngles = cv2.RQDecomp3x3(rotM)[0]
                angle = eulerAngles[1] * 180 / np.pi #Угол поворота в градусах

                #Отрисовка угла на изображении
                cv2.putText(frame, f"Angle: {angle:.2f}", (int(corner[0,0,0]), int(corner[0,0,1]) - 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0,255,0),2)

                # Проверка на выравнивание
                if abs(angle) < 5: # Порог выравнивания (в градусах)
                    print(f"Marker {ids[i][0]} is approximately aligned. Angles: {eulerAngles}")

    # Показ изображения
    cv2.imshow('Aruco Marker Detection', frame)

    # Выход из цикла
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Освобождение ресурсов
cap.release()
cv2.destroyAllWindows()