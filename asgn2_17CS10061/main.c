#include "myl.h"
int main()
{
	printStr("Input an Integer:");
	int k;
	int check = readInt(&k);
	if(check==0)
		printStr("Error!\n");
	else
	{
		printStr("Integer Input:");
		printInt(k);
	}
	printStr("Input a Floating Point Number:");
	float m;
	check = readFlt(&m);
	if(check==0)
		printStr("Error!\n");
	else
	{
		printStr("Floating Point Number Input:");
		printFlt(m);
	}
}