from math import *
import cv2
l1, l2 = 280, 400

a_x = 290
b_y = 440
angle1_start, angle2_start, angle3_start = 0, 0, 0
now_x, now_y = 150+a_x, -30+b_y
this_angle = 90

def kinematik_egor(x,y):
    b = sqrt((a_x+x-100)**2+(b_y+y-20)**2)
    q1 = round(acos((a_x+x-100)/b) / (pi/180))
    q2 = round(acos((((b**2)/(2*b*l1)))) / (pi/180))
    angle1 = q1+q2
    angle2 = round(acos((l1**2+l2**2-b**2)/(2*l1*l2)))
    angle3 = angle2-angle1
    return (angle1, angle2, angle3)

print(kinematik_egor(now_x,now_y))

















"""
def kinematic_max(x,y) -> list:
    b = pow(x, 2) + pow(y, 2)
    q1 = acos(x / b) / (pi / 180)
    q2 = acos((l1**2 - l2**2 + b) / (2 * b**0.5 * l1)) / (pi / 180)
    angle1 = round(q1 + q2)
    angle2 = round(180 - (acos((pow(l1, 2) + pow(l2, 2) - b) / (2 * l1 * l2)) / (pi / 180)))
    #angle3 = round(this_angle + 180 - (180 - angle2) - q2 - q1)
    angle3 = 360-angle2-angle1
    return [angle1, angle2, angle3]
print(*kinematic_max(now_x,now_y))
"""