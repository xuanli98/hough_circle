#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define pi 3.1415926


struct circle{
    int cx;
    int cy;
    float cr;
};
const int m = 70;
const int n = 50;
//这里阈值就取1因为就一个圆，不存在概率问题
struct circle  HoughCircle(int edge[m][n],float step_r,float step_angle,int r_min,int r_max)
{
    struct circle result;
    printf("%d\n",edge[0][0]);
    long int i=0,j=0,k=0,r=0,num_x = 0,num_y = 0;
    int a=0,b=0;
    int max_para=0;
    int size_r = round((r_max - r_min) / step_r) + 1;
    int size_angle = round(2 * pi / step_angle);
    int hough_space[m][n][size_r];  //m,n为二值图像的大小
    int no_zero_x[800000];
    int no_zero_y[800000];
    long int index[1000];
    long int count = 0;
    long int length = 0;
    int par1=0,par2=0,par3=0;
    int circleParaXYR[1000][3];
    long int num = 1;

    memset(hough_space,0,sizeof(hough_space));
    memset(no_zero_x,0,sizeof(no_zero_x));
    memset(no_zero_y,0,sizeof(no_zero_y));
    memset(index,0,sizeof(index));
    memset(circleParaXYR,0,sizeof(circleParaXYR));
    printf("hello\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            if(edge[i][j])
            {
                no_zero_x[num_x] = i;
                no_zero_y[num_y] = j;
                num_x ++;
                num_y ++;
            }
        }
    }
    printf("hello1\n");
    for(i=0;i<num_x;i++)
    {
        for(r=0;r<size_r;r++)
        {
            for(k=0;k<size_angle;k++)
            {
                a = round(no_zero_x[i] - (r_min + (r - 1) * step_r) * cos(k * step_angle));
                b = round(no_zero_y[i] - (r_min + (r - 1) * step_r) * sin(k * step_angle));
                if(a > 0 && a < m && b > 0 && b < n)
                {
                    hough_space[a][b][r] += 1;
                }
            }
        }
    }
    printf("hello2\n");
    max_para  = hough_space[0][0][0];

    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            for(k=0;k<size_r;k++)
            {
                if(max_para < hough_space[i][j][k])
                {
                    max_para = hough_space[i][j][k];
                }
            }
        }
    }

    printf("hello5\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            for(k=0;k<size_r;k++)
            {
                count ++;
                if(max_para == hough_space[i][j][k])
                {
                    index[length] = count;
                    length ++;
                }
            }
        }
    }
    printf("test\n");
    j=0;    
    for(k=0;k<length;k++)
    {
        printf("what\n");
        par3 = floor(index[k]/(m*n))+1;
        par2 = floor((index[k]-(par3-1)*(m*n))/m)+1;
        par1 = index[k] - (par3-1)*(m*n)-(par2-1)*m;
        circleParaXYR[j][0] = par1;
        circleParaXYR[j][1] = par2;
        circleParaXYR[j][2] = par3;
     }
    printf("hello213\n");
    if(length>=1)
    {
        int temp1 = circleParaXYR[0][0];
        int temp2 = circleParaXYR[0][1];
        float temp3 = circleParaXYR[0][2];
        int c1 = temp1;
        int c2 = temp2;
        float c3 = temp3;
        temp3 = r_min + (temp3-1)*step_r;
        if(length>1)
        {
            for(k=1;k<length;k++)
            {
                c1 += circleParaXYR[k][0];
                c2 += circleParaXYR[k][1];
                c3 += circleParaXYR[k][2];
                num ++;
            }
        }
        c1 = round(c1/num);
        c2 = round(c2/num);
        c3 = round(c3/num);
        c3 = r_min + (c3-1)*step_r;
        result.cx = c1;
        result.cy = c2;
        result.cr = c3;
        printf("圆心x坐标：%d，圆心y坐标：%d，圆半径：%f\n",c1,c2,c3);
        
    }
    return result;
}

int main()
{ 
    int i,j;
    int test[m][n];
    memset(test,0,sizeof(test));
    long long int count=0;
    float step_r = 0.5;
    float step_angle = 0.1;
    int r_min = 20;
    int r_max = 30;
 /*   for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            test[j][i] = c[count];
            count++;
        }
    }*/
    struct circle t = HoughCircle(test,step_r,step_angle,r_min,r_max);

    return 0;
}
