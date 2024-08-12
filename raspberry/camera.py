import cv2

# Проверяем подключение к камере
cap = cv2.VideoCapture(0) # используйте '/dev/video1' или другой путь, если нужно

if not cap.isOpened():
    print("Не удалось открыть камеру")
    exit()

while True:
    ret, img = cap.read()

    if not ret:
        print("Не удалось получить кадр с камеры")
        break

    # Выводим изображение
    cv2.imshow('Video', img)

    # Выход из цикла, если нажата клавиша 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
