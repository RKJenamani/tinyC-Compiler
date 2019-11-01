// Greatest Common Divisor Calculation 
int euclidGCD(int a, int b) 
{ 
    if (a == 0)
    { 
        return b;
    }
    else
    { 
        return euclidGCD(b % a, a); 
    }
} 

int main()
{
    int a,b,gcd;
    printStr("_______ Greatest Common Divisor Calculation _________\n");
    printStr("Input Integer a\n"); 
    int err=1;
    a=readInt(&err);
    printStr("Input Integer b\n"); 
    b=readInt(&err);
    gcd = euclidGCD(a, b);   // recursive function call
    printStr("Greatest Common Divisor: ");
    printInt(gcd);
    printStr("\n_____________\n");
    return 0;
}
