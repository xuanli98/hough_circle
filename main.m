clc
clear all
close all
I = imread('3.PNG');

I=im2bw(I); 
BW = I;
%BW = edge(I,'sobel');
Step_r = 0.5;  
%角度步长0.1，单位为弧度  
Step_angle = 0.1;  
%最小圆半径2  
minr =20;  
%最大圆半径30  
maxr = 30;  
%以thresh*hough_space的最大值为阈值，thresh取0-1之间的数  
thresh = 1;  
circleParaXYR=[];  
%---------------------------------------------------------------------------------  
%开始检测  
[Hough_space,Hough_circle_result,Para] = Hough_circle(BW,Step_r,Step_angle,minr,maxr,thresh);  
circleParaXYR=Para;  
axis equal  
figure(2);  
imshow(BW,[]),title('边缘');  
axis equal  
figure(3);  
imshow(Hough_circle_result,[]),title('检测结果');  
axis equal  
figure(4),imshow(I,[]),title('检测出图中的圆')  
hold on;  
%---------------------------------------------------------------------------------  
%以红色线标记出的检测圆心与圆  
plot(circleParaXYR(:,2), circleParaXYR(:,1), 'r+');  
for k = 1 : size(circleParaXYR, 1)
    t=0:0.01*pi:2*pi;  
    x=cos(t).*circleParaXYR(k,3)+circleParaXYR(k,2);  
    y=sin(t).*circleParaXYR(k,3)+circleParaXYR(k,1);  
    plot(x,y,'r-');  
end  
