#include <iostream>
using namespace std;

int carryOut(int A, int B, int Cin)
{
    int sum = A * B + A * Cin + B * Cin;
    if (sum == 0)
    {
        return 0;
    }
    else if (sum >= 0)
    {
        return 1;
    }
}
int complement(int A)
{
    if (A == 0)
    {
        return 1;
    }
    else if (A > 0)
    {
        return 0;
    }
}

int sumOut(int A, int B, int Cin)
{
    int Exor = (complement(B) * Cin) + (B * complement(Cin));
    int sum = (complement(A) * Exor) + (complement(Exor) * A);
    if (sum == 0)
    {
        return sum;
    }
    else if (sum > 0)
    {
        return 1;
    }
}

int main()
{
    int A, B, Cin;
    int choice;
    do
    {
        cout << "\nEnter 1 to run or any other number to exit: " << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the value of A,B,Cin: " << endl;
            cin >> A >> B >> Cin;
            cout << "sum: " << sumOut(A, B, Cin);
            cout << "\ncarry: " << carryOut(A, B, Cin);
            break;
        default:
            cout << "Exiting program" << endl;
            break;
        }
    } while (choice == 1);

    return 0;
}

// 000
// 001
// 010
// 011
// 100
// 101
// 110
// 111