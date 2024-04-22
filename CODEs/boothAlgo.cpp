// Write a program to simulate the behaviour of booth's multiplier.

#include <iostream>
using namespace std;

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

void parallelAdder(int mul[], int ACC[], int a_size)
{

    int carry = 0;
    for (int i = a_size - 1; i >= 0; i--)
    {
        int temp = ACC[i];
        ACC[i] = sumOut(ACC[i], mul[i], carry);
        carry = carryOut(temp, mul[i], carry);
    }
}

void twosComplement(int arr[], int n)
{
    int flag = 0;
    for (int i = n - 1; i >= 0; i--)
    {

        if (flag == 0)
        {
            if (arr[i] == 0)
            {
                arr[i] = 0;
            }
            else if (arr[i] == 1)
            {
                flag = 1;
            }
        }
        else
        {

            if (arr[i] == 0)
            {
                arr[i] = 1;
            }
            else
            {
                arr[i] = 0;
            }
        }
    }
}
void A_right_shift(int Q[], int Acc[], int a_size, int mul_size, int *Qx)
{
    *Qx = Q[mul_size - 1];
    int temp = Acc[a_size - 1];
    for (int i = a_size - 1; i > 0; i--)
    {
        Acc[i] = Acc[i - 1];
    }
    for (int i = mul_size - 1; i > 0; i--)
    {
        Q[i] = Q[i - 1];
    }
    Q[0] = temp;
}

void displayStep(int accumulator[], int multiplier[], int a_size, int multiplier_size, int Qx)
{
    for (int i = 0; i < a_size; i++)
    {
        cout << accumulator[i] << " ";
    }
    cout << "\t";
    for (int i = 0; i < multiplier_size; i++)
    {
        cout << multiplier[i] << " ";
    }
    cout << "\t" << Qx << endl;
}

void boothAlgo(int multiplicand[], int mul_inverse[], int multiplier[], int accumulator[], int multiplier_size, int a_size)
{
    int Qx = 0;
    cout << "\nACC\t\tQ\t\tQx" << endl;
    cout << "-----------------------------------" << endl;
    displayStep(accumulator, multiplier, a_size, multiplier_size, Qx);
    for (int i = 0; i < multiplier_size; i++)
    {
        cout << "\nStep: " << i + 1 << endl;
        if (multiplier[multiplier_size - 1] == Qx)
        {
            A_right_shift(multiplier, accumulator, multiplier_size, a_size, &Qx);
            cout << "Right Shift" << endl;
            displayStep(accumulator, multiplier, a_size, multiplier_size, Qx);
        }
        else if (multiplier[multiplier_size - 1] == 1 && Qx == 0)
        {
            parallelAdder(mul_inverse, accumulator, a_size);
            cout << "Subtraction" << endl;
            displayStep(accumulator, multiplier, a_size, multiplier_size, Qx);

            A_right_shift(multiplier, accumulator, multiplier_size, a_size, &Qx);
            cout << "Right Shift" << endl;
            displayStep(accumulator, multiplier, a_size, multiplier_size, Qx);
        }
        else
        {

            parallelAdder(multiplicand, accumulator, a_size);
            cout << "Addition" << endl;
            displayStep(accumulator, multiplier, a_size, multiplier_size, Qx);

            A_right_shift(multiplier, accumulator, multiplier_size, a_size, &Qx);
            cout << "Right Shift" << endl;
            displayStep(accumulator, multiplier, a_size, multiplier_size, Qx);
        }
    }
}

int main()
{
    int n;
    cout << "Enter the size of multiplicand: ";
    cin >> n;
    int M[n];
    cout << "Enter the multiplicand: ";
    for (int i = 0; i < n; i++)
    {
        cin >> M[i];
    }
    int m;
    cout << "Enter the size of multiplier: ";
    cin >> m;
    int Q[m];
    cout << "Enter the multiplier: ";
    for (int i = 0; i < m; i++)
    {
        cin >> Q[i];
    }

    cout << "Multiplicand = ";
    for (int i = 0; i < n; i++)
    {
        cout << M[i] << " ";
    }
    cout << "\nmultiplier: ";
    for (int i = 0; i < m; i++)
    {
        cout << Q[i] << " ";
    }

    int M_dash[n] = {0};
    for (int i = 0; i < n; i++)
    {
        M_dash[i] = M[i];
    }
    twosComplement(M_dash, n);
    cout << "\nM_dash:";
    for (int i = 0; i < n; i++)
    {
        cout << M_dash[i] << " ";
    }

    int acc_size = n;
    int ACC[acc_size] = {0};

    boothAlgo(M, M_dash, Q, ACC, n, acc_size);

    cout << "\nResult: ";
    for (int i = 0; i < acc_size; i++)
    {
        cout << ACC[i] << " ";
    }
    for (int i = 0; i < m; i++)
    {
        cout << Q[i] << " ";
    }
    return 0;
}