#include <iostream>
using namespace std;

//-------------------------- GATES ----------------------------
int complement(int A)
{
    if (A > 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int AND(int A, int B)
{
    int a_and_b = A * B;
    if (a_and_b > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int OR(int A, int B, int C = 0)
{
    int a_or_b = A + B + C;
    if (a_or_b > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int XOR(int A, int B)
{
    int n = AND(A, complement(B));
    int m = AND(B, complement(A));
    int a_exor_b = OR(n, m);
    return a_exor_b;
}

//-------------------------- Adder Functions----------------------------
int sumOut(int A, int B, int Cin)
{
    int Exor = XOR(B, Cin);
    int sum = XOR(Exor, A);
    return sum;
}
int carryOut(int A, int B, int Cin)
{
    int sum = OR(AND(A, B), AND(A, Cin), AND(B, Cin));
    return sum;
}
int addBits(int Num1, int Num2)
{
    int carry = 0;
    int sum = 0;
    int x = 0;
    int y = 0;
    int i = 0;
    int multiplier = 1;
    while (Num1 > 0 || Num2 > 0)
    {

        x = Num1 % 10;
        y = Num2 % 10;

        sum = sum + (multiplier * sumOut(x, y, carry));
        carry = carryOut(x, y, carry);

        Num1 = Num1 / 10;
        Num2 = Num2 / 10;
        multiplier *= 10;
        i++;
    }

    int additionalCarry = multiplier * carry;
    sum = sum + additionalCarry;
    return sum;
}
int multiply(int A, int B)
{
    int sum = 0;
    int i = 0;
    int multiplier = 1;
    while (B > 0)
    {
        int y = B % 10;
        int partialProduct = A * y * multiplier;
        sum = addBits(sum, partialProduct);
        B = B / 10;
        multiplier *= 10;
        i++;
    }
    return sum;
}

int main()
{
    int A, B;
    cout << "Enter two numbers: ";
    cin >> A >> B;
    cout << multiply(A, B);
    return 0;
}