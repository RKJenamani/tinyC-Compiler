// Calculate Force 
int main()

{
    int force, mass, accelaration;
    printStr("_____________ Calculating Force _____________\n");
    printStr("Input the value of mass:");
    int err = 1;
    mass = readInt(&err);
    printStr("Input the value of accelaration:");
    accelaration = readInt(&err);

    force = mass * accelaration;

    printStr("The value of force is ");
    printInt(force);
    printStr("\n");
    printStr("\n__________________________\n");
    return 0;

}