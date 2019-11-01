// Dynamic Programming solution for n-th fibonacci number
int fib(int n) 
{ 
  int f[100];   
  int i; 
  
  f[0] = 0; 
  f[1] = 1; 
  
  for (i = 2; i <= n; i++) 
  { 
      f[i] = f[i-1] + f[i-2]; 
  } 
  return f[n]; 
} 
  
int main () 
{ 
  int n,fib_num; 
  int err=1;
  printStr("_____________ nth Fibonacci Number _____________\n");
  printStr("Input number n:\n");
  n=readInt(&err);
  fib_num = fib(n);
  printStr("nth Fibonacci number is: ");
  printInt(fib_num);
  printStr("\n_________________________\n");
  return 0; 
} 

