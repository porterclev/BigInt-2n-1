// Porter Clevidence
// Class (CECS 325-01)
// Project Name (Prog 7 - 3N + 1(BigInt))
// Due Date (4/25/2023)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <string>
#include <vector>
#include <iostream>
#include <limits.h>
#include <cstring>
#include <fstream>
using namespace std;

class BigInt
{
private:
    vector<char> v;

public:
    /// @brief Creates a bigint with a 0 value
    BigInt() // default constructor – set value to 0
    {
        v.push_back((int)'0');
    }

    /// @brief Converts an int to a vector of chars inorder to store infinitely large numbers
    /// @param n The int to be converted
    BigInt(int n)
    {
        char digit;
        while (n > 9) // builds left to right
        {
            digit = n % 10;
            n /= 10;
            v.push_back(digit);
        }
        digit = n;
        v.push_back(digit);
    }

    /// @brief Converts a string of numbers into a vector of chars inorder to store infinitely large numbers
    /// @param s string of numbers
    BigInt(string s)
    {
        for (int i = s.length() - 1; i >= 0; i--)
        {
            v.push_back((int)s[i] - 48);
        }
    }

    /// @brief Compiles vector
    /// @return in the form of a string
    string get()
    {
        string s = "";
        for (int i = 0; i < v.size(); i++)
        {
            s += to_string(v[i]);
        }
        return s;
    }

    /// @brief Add two BigInts
    /// @param imp implicit BigInt variable
    /// @return BigInt sum of the two BigInts
    BigInt operator+(BigInt imp)
    {
        string sum = "";
        bool carry = false;
        int temp = 0, i = 0, j = 0;
        while (i < v.size() || j < imp.v.size())
        {
            if (i < v.size() && j < imp.v.size())
            {
                temp = v[i++] + imp.v[j++];
            }
            else if (i < v.size())
            {
                temp = v[i++];
            }
            else if (j < imp.v.size())
            {
                temp = imp.v[j++];
            }

            if (carry)
            {
                carry = false;
                temp++;
            }

            if (temp == 10 && v.size() == 1)
            {
                carry = true;
                sum += to_string(0);
                temp = 1;
            }
            else if (temp > 9)
            {
                carry = true;
                temp -= 10;
            }
            sum += to_string(temp);
        }

        string temp2 = "";
        for (int z = sum.length() - 1; z >= 0; z--)
        {
            temp2 += sum[z];
        }

        return BigInt(temp2);
    }

    /// @brief this.operator++() prefix increment
    /// @param x implicit Variable
    /// @return new BigInt Value to explicit BigInt
    BigInt operator++()
    {
        int i = 0;
        bool nextPlace = false;
        for (int k = v.size() - 1; k >= 0; k--)
        {
            if (v[k] == 9)
                nextPlace = true;
            else
                nextPlace = false;
        }

        while (i < v.size())
        {
            v[i]++;
            if (nextPlace)
            {
                v[i++] = 0;
                v.push_back(0);
                nextPlace = false;
            }
            else if (v[i] > 9)
            {
                v[i++] -= 10;
            }
            else
            {
                break;
            }
        }

        return *this;
    }

    /// @brief this.operator++(x) postfix increment
    /// @param x implicit Variable
    /// @return new BigInt Value to explicit BigInt
    BigInt operator++(int x)
    {
        BigInt temp = BigInt(this->get());
        int i = 0;
        bool nextPlace = true;
        for (int k = v.size() - 1; k >= 0; k--)
        {
            if (v[k] != 9)
                nextPlace = false;
        }

        while (i < v.size())
        {
            v[i]++;
            if (nextPlace)
            {
                v[i++] = 0;
                v.push_back(0);
                nextPlace = false;
            }
            else if (v[i] > 9)
            {
                v[i++] -= 10;
            }
            else
            {
                break;
            }
        }

        return BigInt(temp);
    }

    /// @brief Multiplies BigInt by BigInt(3)
    /// @param x has to be BigInt(3) or it will fail
    /// @return product
    BigInt operator*(BigInt x)
    {
        // to-do fix this
        string product = "";
        int carry = 0, temp = 0;
        for (int i = 0; i < v.size(); i++)
        {
            temp = v[i] * 3;
            if (carry > 0)
            {
                temp += carry;
                carry = 0;
            }
            while (temp > 9)
            {
                temp -= 10;
                carry++;
            }

            product += to_string(temp);
        }
        if (carry > 0)
        {
            product += to_string(carry);
        }

        string temp2 = "";
        for (int z = product.length() - 1; z >= 0; z--)
        {
            temp2 += product[z];
        }

        return BigInt(temp2);
    }

    /// @brief Compares the right BigInt to the left BigInt
    /// @param x right BigInt
    /// @return true if the left BigInt is less than the right BigInt
    bool operator<(BigInt &x)
    {
        if (v.size() < x.v.size())
        {
            return true;
        }
        else if (v.size() > x.v.size())
        {
            return false;
        }
        else
        {
            for (int i = v.size() - 1; i >= 0; i--)
            {
                if (v[i] < x.v[i])
                {
                    return true;
                }
                else if (v[i] > x.v[i])
                {
                    return false;
                }
            }
        }
        return false;
    }

    /// @brief Cuts the BigInt in half (must be even)
    /// @return returns quotient
    BigInt half() // return half the value
    {
        string quotient = "";
        /* int carry = 0, temp = 0;
        for (int i = v.size(); i > 0; i--)
        {
            temp = v[i] / 2;
            if (carry > 0)
            {
                temp += carry;
                carry = 0;
            }
            if (v[i] % 2 == 1)
                carry = 5;

            quotient += to_string(temp);
        }
        if (carry > 0)
            quotient += to_string(carry);

        for (int i = 0; i < quotient.length(); i++)
        {
            if (quotient[i] == '0')
                quotient.erase(i--, 1);
            else
                break;
        }

        string temp2 = "";
        for (int z = quotient.length() - 1; z >= 0; z--)
        {
            temp2 += quotient[z];
        } */
        int carry = 0, temp = 0;
        for (int i = v.size() - 1; i >= 0; i--)
        {
            if (carry > 0)
            {
                temp = v[i] + (10 * carry);
                carry = 0;
            }
            else
            {
                temp = v[i];
            }
            carry = temp - ((temp / 2) * 2);
            quotient += to_string(temp / 2);
        }
        for (int i = 0; i < quotient.length(); i++)
        {
            if (quotient[i] == '0')
                quotient.erase(i--, 1);
            else
                break;
        }

        return BigInt(quotient);
    }

    bool isOdd() // true if the number is odd
    {
        if (v[0] % 2 == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool isEven() // true if the number is even
    {
        if (v[0] % 2 == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool operator==(BigInt n) // true if 2 BigInts are equal
    {
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i] != n[i])
            {
                return false;
            }
        }
        return true;
    }

    /// @brief Vector size accessor
    /// @return size of the vector
    int size() const { return v.size(); }

    /// @brief Overloads the [ ] operator to return the integer at the index of the char vector
    /// @param n index of the char vector
    /// @return integer at the index of the char vector
    int operator[](int n) const
    {
        return v[n];
    }

    /// @brief (friend) prints the bigint to the console
    /// @param out console out
    /// @param n the integer
    /// @return output stream
    friend ostream &operator<<(ostream &out, const BigInt n)
    {
        int count = -1;
        for (int i = n.v.size() - 1; i >= 0; i--) // prints out in reverse order
        {
            if (n.v.size() > 9)
            {
                if (i == n.v.size() - 2)
                {
                    out << ".";
                }

                if (i > n.v.size() - 9)
                {
                    out << (int)n.v[i];
                    count++;
                }
                else
                {
                    count++;
                }
            }
            else
            {
                out << (int)n.v[i];
            }
        }
        if (n.v.size() > 9)
            out << "e" << count;
        /* out << (int)n.v[i];
    } */
        return out;
    }
};

// create struct to store all details of 3n+1 sequences
struct ThreeNp1
{
    BigInt start;
    BigInt steps;
    BigInt max;
    BigInt odd;
    BigInt even;
};
// utility function to see details of 3n+1 sequence
// notice that all values are BigInt… cout << BigInt
void print(ThreeNp1 temp)
{
    cout << "start:" << temp.start << endl;
    cout << "steps:" << temp.steps << endl;
    cout << "max:" << temp.max << endl;
    cout << "odds:" << temp.odd << endl;
    cout << "evens:" << temp.even << endl;
}
// recursive function to find all details about 3n+1 sequence
// Function has a default parameter as the 3rd parameter
void findThreeNp1(BigInt n, ThreeNp1 &Np1, bool printSteps)
{
    if (printSteps)
    {
        cout << "->" << '(' << n << ')';
    }
    if (Np1.max < n) // BigInt::operator<( )
        Np1.max = n; // No need to overload - C++ provides operator=( )

    if (n == BigInt(1)) // BigInt::operator==( )
    {
        return; // we are done
    }
    else if (n.isEven()) // BigInt::isEven()
    {
        Np1.even++; // BigInt::operator++( )
        Np1.steps++;
        // findThreeNp1(n/2,N, printSteps); // BigInt::operator/( ) - Hard…
        findThreeNp1(n.half(), Np1, printSteps); // BigInt::half( ) - Easy
    }
    else if (n.isOdd()) // BigInt::isOdd( )
    {
        Np1.odd++;
        Np1.steps++;
        BigInt tempN(n);                                                // BigInt constructor
        findThreeNp1((tempN * BigInt(3)) + BigInt(1), Np1, printSteps); // BigInt::operator*( )
        // BigInt::operator+( )
    }
    else
    {
        cout << "How the hell did I get here?\n";
        return;
    }
}
// https://en.wikipedia.org/wiki/Collatz_conjecture
int main(int argc, char const *argv[])
{
    BigInt MAX(INT_MAX);
    cout << "The largest integer is " << MAX << endl;
    cout << "Twice the largest integer is " << MAX + MAX << endl;
    bool printSteps = true;

    BigInt start = BigInt(INT_MAX);
    int input = 0;
    int args[argc - 1];
    /*
        Arg Handling
        up to 5 args (not including name)
    */
    if (argc < 2)
    {
        cout << "Enter a 3n+1 candidate number: ";
        cin >> input;
        start = BigInt(input);
    }
    else
    {
        for (int i = 0; i < argc - 1; i++)
        {
            args[i] = atoi(argv[i + 1]);
        }
    }
    ThreeNp1 N = {start, 0, 0, 0, 0}; // initialize N
    /*
        Algorithm
    */
    if (input != 0)
    {
        findThreeNp1(start, N, printSteps); // print out the steps
        cout << endl;
        print(N);
    }
    else
    {
        for (int i = 0; i < argc - 1; i++)
        {
            cout << "\nSolving 3n+1 - starting value: " << args[i] << endl;

            findThreeNp1(start, N, printSteps); // print out the steps
            cout << endl;
            print(N);
        }
    }

    // BigInt start(100); // BigInt constructor – use for testing

    return 0;
}
