// Egg Dropping Puzzle

/*
The following is a description of the instance of this famous puzzle involving N=2 eggs and a building with H=36 floors:
  
  Suppose that we wish to know which stories in a 36-story building are safe to drop eggs from, and which will cause the eggs to break on landing. We make a few assumptions:
  
    -An egg that survives a fall can be used again.
    -A broken egg must be discarded.
    -The effect of a fall is the same for all eggs.
    -If an egg breaks when dropped, then it would break if dropped from a higher window.
    -If an egg survives a fall, then it would survive a shorter fall.
    -It is not ruled out that the first-floor windows break eggs, nor is it ruled out that eggs can survive the 36th-floor windows.

*/

int max(int a, int b)
{
  if(a>b)
    return a;
  else
    return b;
}

int main()
{
  int DP[100][100];
  int n,f,i,j,min,k;
  printf("Input number of floors: ");
  scanf("%d",&n);
  printf("Input number of eggs: ");
  scanf("%d",&f);
  for(i=1;i<=f;i++)
  {
    DP[i][0]=0;
    DP[i][1]=1;
  }
  for(i=1;i<=n;i++)
    DP[1][i]=i;
  for(i=2;i<=f;i++)
  {
    for(j=2;j<=n;j++)
    {
      min=1000;
      for(k=1;k<=j;k++)
      {
        if(min>max(DP[i][j-k],DP[i-1][k-1]))
          min=max(DP[i][j-k],DP[i-1][k-1]);
      }
      DP[i][j]=min+1;
    }
  }
  printf("The minimum number of trials required is: %d",DP[f][n]);
}