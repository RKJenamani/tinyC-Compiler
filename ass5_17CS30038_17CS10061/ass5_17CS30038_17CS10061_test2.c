// function calling and conditional statements (ternery and if-else)
int max(int x, int y) 
{
   int ans;
   if(x>y)  // if-else
   	ans=x;
   else
   	ans=y;
   return ans;
}

int min(int x, int y) 
{
   int ans;
   ans = x>y ? y:x; // ternery
   return ans;
}

int difference(int x, int y)
{
	int i,j,diff;
	i = max(x,y);	// nested function calls
	j = min(x,y);
	diff=i-j;
	return diff;
}

int main() 
{
	int a,b,diff;
	a=10;
	b=5;
	diff=difference(a,b);
	return 0;
}