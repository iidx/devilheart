#include <iostream>
#include"time.h"
using namespace std;

bool check(int m[],int n);

void main()
{
    srand((unsigned)time(NULL));//以当前时间作为随机种子，否则每次结果一样
    int temp;
	int r;
	int a[8]={1,2,3,4,6,7,8,9};
	int b[8];
	int c[9];//存储最终结果的数组

	bool it=false;
	
	while(!it){
	
    for(int i=8;i>=2;i--)
	{
	   r = rand()%i;//随机出一个下标，并将数组上此位置的数和数组最后一个数交换，交换后将最后一个数去掉形成一个新的数组,依次类推
       temp=a[i-1];
	   a[i-1]=a[r];
	   a[r]=temp;
    }
	
    
    for(int j=0;j<8;j++)
	{
       b[j]=a[7-j]; //将数组a倒过来变成数组b
     }    
   
	
	c[0]=b[0];
	c[1]=b[1];
	c[2]=b[2];
	c[3]=b[3];
	c[4]=5;//九宫图中间一定是5
	c[5]=b[4];
	c[6]=b[5];
	c[7]=b[6];
	c[8]=b[7];

    it=check(c,9);

	}

	cout<<c[0]<<" "<<c[1]<<" "<<c[2]<<endl;
	cout<<c[3]<<" "<<c[4]<<" "<<c[5]<<endl;
	cout<<c[6]<<" "<<c[7]<<" "<<c[8]<<endl;



}

bool check(int m[],int n)//检查是否满足题目要求

{
    if( m[0]+m[1]+m[2]==15&&m[3]+m[4]+m[5]==15&&m[6]+m[7]+m[8]==15&&m[0]+m[3]+m[6]==15
		&&m[1]+m[4]+m[7]==15&&m[2]+m[5]+m[8]==15&&m[0]+m[4]+m[8]==15&&m[2]+m[4]+m[6]==15)
		return true;
	else
		return false;
  

}