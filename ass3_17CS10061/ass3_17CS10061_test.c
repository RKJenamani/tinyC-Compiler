/* Test File */
#include <stdio.h>

int bubble_sort(int a[],int n)
{
	int i,j,flag,temp;
	for(i=0;i<n-1;i++)
	{
		flag=0;
		for(j=0;j<n-i-1;j++)
			if(a[j]>a[j+1])
			{
				flag=1;
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		if(flag==0)
			break;
	}
}

typedef struct node
{
	int value;
	struct node* next;
};

int main () { // ass3_12CS10008_test.c

	//Testing identifiers and constants
	float abc_a12=11.124;
	int a , i=1;
	char abs_02_1 = 'd';
	char str[] = "This is a test file";
	int val = 10;
	int array[4] = {4,1,3,2};
	struct node* tree = NULL;

	for (i=0; i<21;i++) 
	{
		if(abc_a12<321.34-13 && abc_a12 >= i) 
		{
			printf("%s",str);
		}
		else if(str[i]=='i')
		{
			val++;
			val--;
			val=val*10;
			val=val+10;
			val=val-10;
			val=val/10;
			val=val%10;

		}
		else if(str[i]==f)
		{
			break;
			bubble_sort(array,4);
			#define kk 12
			_Bool najs;
			_Complex as12;
			_Imaginary aw1;
		}
		else
		{
			val/=1;
			val%=2;
	 		val+=3;
	 		val-=4;
	 		val<<=5;
	 		val>>=6;
	 		val&=7;
	 		val^=8;
	 		val|=9;
		}
	}
	return 0;
}