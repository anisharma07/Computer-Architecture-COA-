// Half Adder

#include <iostream>
using namespace std;

int carryOut(int A, int B)
{
    int sum = A * B;
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

int sumOut(int A, int B)
{
    int sum = A * complement(B) + B * complement(A);
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
    int A, B;
    int choice;
    d
    {
        cout << "\nEnter 1 to run or any other number to exit: " << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the value of A,B: " << endl;
            cin >> A >> B;
            cout << "sum: " << sumOut(A, B);
            cout << "\ncarry: " << carryOut(A, B);
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