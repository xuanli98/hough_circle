# -*- coding: utf-8 -*-
import  cv2
#载入并显示图片
img=cv2.imread('1.png')
#cv2.imshow('1',img)
#降噪（模糊处理用来减少瑕疵点）
result = cv2.blur(img, (5,5))
#cv2.imshow('2',result)
#灰度化,就是去色（类似老式照片）
gray=cv2.cvtColor(result,cv2.COLOR_BGR2GRAY)
#cv2.imshow('3',gray)
 
#param1的具体实现，用于边缘检测   
canny = cv2.Canny(img, 40, 80)  
#cv2.imshow('4', canny) 
 
 
#霍夫变换圆检测
circles=cv2.HoughCircles(gray,cv2.HOUGH_GRADIENT,1,50,param1=80,param2=30,minRadius=1,maxRadius=200)
#输出返回值，方便查看类型
print(circles)
 
#输出检测到圆的个数
print(len(circles[0]))
 
print('-------------我是条分割线-----------------')
#根据检测到圆的信息，画出每一个圆
for circle in circles[0]:
    #圆的基本信息
    print(circle[2])
    #坐标行列(就是圆心)
    x=int(circle[0])
    y=int(circle[1])
    #半径
    r=int(circle[2])
    if r > 60 :
        continue
    #在原图用指定颜色圈出圆，参数设定为int所以圈画存在误差
    img=cv2.circle(img,(x,y),r,(0,0,255),1,8,0)
#显示新图像
cv2.imshow('5',img)
 
#按任意键退出
cv2.waitKey(10000)
cv2.destroyAllWindows()
