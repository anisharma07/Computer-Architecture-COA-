// Parallel bit full adder.

// full adder
// sum = A XOR B XOR C;
// carry = A*B + B*Cin + Cin * A;

// Full Substracter
// sum = A XOR B XOR C;
// Borrow = A'B + (A' + B)*Bin;

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
// int substracterBorrow(int A, int B, int Cin)
// {
//     int l = OR(complement(A), B);
//     int m = AND(l, Cin);
//     int n = AND(complement(A), B);
//     int borrow = OR(n, m);
//     return borrow;
// }

//-------------------------- Parallel Adder ----------------------------
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

int twoComplement(int Num)
{
    int NumComp = 0;
    int x = 0;
    int i = 0;
    int flag = 0;
    int multiplier = 1;
    while (Num > 0)
    {
        x = Num % 10;
        if (flag == 0)
        {
            NumComp = NumComp + (multiplier * x);
            if (x >= 1)
            {
                flag = 1;
            }
        }
        else
        {
            NumComp = NumComp + (multiplier * complement(x));
        }

        Num = Num / 10;
        multiplier *= 10;
        i++;
    }
    return NumComp;
}

int subBits(int Num1, int Num2)
{
    int Num2comp = twoComplement(Num2);
    return addBits(Num1, Num2comp);
}
//-------------------------- Parallel Substracter ----------------------------

// int subBits(int Num1, int Num2)
// {
//     int borrow = 0;
//     int sum = 0;
//     int x = 0;
//     int y = 0;
//     int i = 0;
//     int multiplier = 1;
//     while (Num1 > 0 || Num2 > 0)
//     {

//         x = Num1 % 10;
//         y = Num2 % 10;

//         sum = sum + (multiplier * sumOut(x, y, borrow));
//         borrow = substracterBorrow(x, y, borrow);
//         Num1 = Num1 / 10;
//         Num2 = Num2 / 10;
//         multiplier *= 10;
//         i++;
//     }
//     return sum;
// }

//-------------------------- main function----------------------------

int main()
{
    int A, B;
    int choice1;
    int choice2;
    do
    {
        cout << "\n1. Enter Numbers";
        cout << "\n2. Exit Program";
        cout << "\nEnter your Choice: ";
        cin >> choice1;
        switch (choice1)
        {
        case 1:
            cout << "\nEnter two n-bit numbers: " << endl;
            cin >> A >> B;

            do
            {
                cout << "0 for ADD, 1 for SUB: ";
                cin >> choice2;
                switch (choice2)
                {
                case 0:
                    cout << A << " + " << B << " = " << addBits(A, B) << endl;
                    break;
                case 1:
                    cout << A << " - " << B << " = " << subBits(A, B) << endl;
                    break;
                default:
                    cout << "Invalid Input, Enter again";
                    break;
                }
            } while (choice2 != 0 && choice2 != 1);

            break;
        case 2:
            cout << "Exiting Program......" << endl;
            break;
        default:
            cout << "\nInvalid Input!" << endl;
            break;
        }
    } while (choice1 != 2);

    return 0;
}