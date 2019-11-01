// Dynamic Programming solution for Rod cutting problem 

int max(int a, int b) 
{ 
	if(a > b)
		return a;
	else
		return b;
} 

int func(int price[], int n) 
{ 
	int val[100]; 
	val[0] = 0; 
	int i, j; 
	int max_val = 0;   
	for (i = 1; i<=n; i++) 
	{ 
		int max_val = 0;   
		for (j = 0; j < i; j++) 
			max_val = max(max_val, price[j] + val[i-j-1]); 
		val[i] = max_val; 
	} 
	return val[n]; 
} 

int main()
{
	int arr[100]; 
	int i,n,ans;
	printStr("_________ Rod Cutting Problem _________\n");
    printStr("Input the size of array(n):\n");
	int err=1;
    n = readInt(&err);
	printStr("Input the (n) elements of the array\n"); 
    for(i=0;i<n;i++)
    {
        arr[i]=readInt(&err);
    }
	ans = func(arr, n);
    printStr("The maximum value obtainable for rod cutting problem is:");
    printInt(ans);
    printStr("\n");
    printStr("\n_______________________________________________\n");
	return 0;
}

