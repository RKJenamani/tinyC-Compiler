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
  int n = 9; 
  int fib_num;
  fib_num = fib(n);
  return 0; 
} 