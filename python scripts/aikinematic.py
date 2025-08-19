import math

def calculate_angles(x, y, l1, l2):
    """
    Вычисляет углы двухзвенного манипулятора.

    Args:
        x: Координата x целевой точки.
        y: Координата y целевой точки.
        l1: Длина первого звена.
        l2: Длина второго звена.

    Returns:
        Кортеж (theta1, theta2), содержащий углы в радианах.
        Возвращает None, если решение не существует.
    """

    # Проверка на допустимые значения длин звеньев
    if l1 <= 0 or l2 <= 0:
        raise ValueError("Длины звеньев должны быть положительными числами.")

    # Расстояние до целевой точки
    d = math.sqrt(x*2 + y*2)

    # Проверка на достижимость точки
    if d > l1 + l2 or d < abs(l1 - l2):
        return None # Точка недостижима

    # Вычисление угла theta2
    theta2 = math.acos((x*2 + y*2 - l1*2 - l2*2) / (2 * l1 * l2))

    # Вычисление угла theta1
    alpha = math.atan2(y, x)
    beta = math.atan2(l2 * math.sin(theta2), l1 + l2 * math.cos(theta2))
    theta1 = alpha - beta


    return theta1, theta2


# Пример использования:
l1 = 280 # Длина первого звена
l2 = 400 # Длина второго звена
x = 340 # Координата x целевой точки
y = 410 # Координата y целевой точки

angles = calculate_angles(x, y, l1, l2)

if angles:
    theta1, theta2 = angles
    print(f"Угол theta1: {math.degrees(theta1):.2f} градусов")
    print(f"Угол theta2: {math.degrees(theta2):.2f} градусов")
else:
    print("Точка недостижима.")

