import math
# import numpy
thighLen, legLen = 64, 90
defaultZ = 80
toDegree = 57.2958



# calculating Z
def ik_z(newZ):
    theta3 = math.acos((pow(legLen,2)+pow(newZ,2)-pow(thighLen,2))/(2*legLen*newZ))
    thighJoint = math.acos((pow(thighLen,2)+pow(newZ,2)-pow(legLen,2))/(2*thighLen*newZ))
    legJoint = math.acos((pow(thighLen,2)+pow(legLen,2)-pow(newZ,2))/(2*thighLen*legLen))
    # zAngle
    # print("new Z value :" + str(zNew))

    return thighJoint *toDegree, legJoint *toDegree

# calculating X
def ik_x(newX):
    tempAngleX = math.atan(newX/defaultZ)
    zNew = (defaultZ/math.cos(tempAngleX))
    print("new Z value :" + str(zNew))
    return ik_z(zNew)

# calculating Y. Need to configure angle of hip Joint
def ik_y(newY):
    tempAngleY = math.atan(newY/defaultZ)
    zNew = (defaultZ/math.cos(tempAngleY))
    print("new Y value :" + str(zNew))
    return ik_z(zNew)


if __name__ == "__main__":
    angleThigh,angleLeg = ik_z(120)
    print("Thigh angle :"+str(angleThigh))
    print("Leg angle :"+str(angleLeg))