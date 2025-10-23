/*
Lab#: Lab1
Name: Jin Gi Min
Find if all of the array's elements are prime number or not with usuing iteration and recursion and print
the all elements in the array is all prime nubmer or not
*/

#include <iostream>
#include <cmath>

using namespace std;

bool IsArrayPrimeIter(int arrIter[], int size);
bool IsArrayPrimeRecur(int arrRecur[], int size);
bool isPrimeRecur(int dividend, int divisor);

const int SORT_MAX_SIZE = 8;

int main()
{
    int arrSize = 0;
    int userArr[SORT_MAX_SIZE];

    cout << "Please enter your input data on one line only." << endl;
    // get a array size
    cin >> arrSize; 

    for (int i = 0; i < arrSize; i++)
    {
        // get array elements
        cin >> userArr[i]; 
    }

    if (IsArrayPrimeIter(userArr, arrSize))
    {
        cout << "Array was found to be prime using iteration" << endl;
    }

    else
    {
        cout << "Not a Prime Array using iteration" << endl;
    }

    if (IsArrayPrimeRecur(userArr, arrSize))
    {
        cout << "Array was found to be prime using recursion" << endl;
    }

    else
    {
        cout << "Not a Prime Array using recursion" << endl;
    }

    return 0;
}

/*
Algorithm IsArrayPrimeIter (arrIter, size)

    With using iteration, find the elements in array is all prime number or not
    Pre: arrIter - a integer array contains number of elements at the first element and positive numbers after that
         size - size of arrIter array
    Post:
    Return: true when all elements are prime, false when there's non-prime number

    print "Entering IsArrayPrimeIter"
    isArrayPrime = true
    loop for i = 0 to size - 1
        if (arrIter[i] is 1)
            it's not prime number
        
        else if (arrIter[i] not equal to 2 AND even number)
            it's not prime number

        else if (arrIter[i] not equal to 3 AND can be completely divided by 3 )
            it's not prime number

        else
            loop for j = 0  to square root of arrIter[i] + 1
                if (arrIter[i] is divided by j without ramainder)
                    it's not prime number
                end if
            endl loop
        end if


    end loop

    Print "Leaving IsArrayPrimeIter"

    return isArrayPrime

end algorithm
*/
bool IsArrayPrimeIter(int arrIter[], int size)
{
    cout << "Entering IsArrayPrimeIter" << endl;

    // when found prime number change to false
    bool isArrayPrime = true;

    for (int i = 0; i < size; i++)
    {
        if (arrIter[i] == 1) 
        {
            isArrayPrime = false;
        }

        else if ((arrIter[i] != 2) && (arrIter[i] % 2 == 0))
        {
            isArrayPrime = false;
        }

        // many numbers can be divided by 3
        else if ((arrIter[i] != 3) && (arrIter[i] % 3 == 0))
        {
            isArrayPrime = false;
        }

        else
        {
            // don't need to check even number because it's same as diveded by 2
            for (int j = 5; j <= sqrt(arrIter[i]) + 1; j = j + 2)
            {
                if (arrIter[i] % j == 0)
                {
                    isArrayPrime = false;
                    break;
                }
            }
        }

        if(!isArrayPrime) {
            break;
        }
    }

    cout << "Leaving IsArrayPrimeIter" << endl;

    return isArrayPrime;
}

/*
Algorithm IsArrayPrimeRecur(arrRecur, size)

    This algorithm checks the elements in array is all prime number or not with recursion
    Pre: arrRecur - a array which first element is number of elements and have positive integers from second elements
         size - size of arrRecur
    Post:
    Return: true when the array is prime number array, otherwise, false

    print "Entering IsArrayRecur"
    set isPrime true
    check the index 1 smaller than size

    if (arrRecur[index] is one)
        it's not a prime number

    else if (arrRecur[index] is not equal to 2 AND even number)
        it's not a prime number

    else if (arrRecur[index] is not equal to 3 AND completely divided by 3)
        it's not a prime number
    else
        when arrRecur[index] not divided by 5 ~ square root of arrRecur[index]
        it's prime number. Otherwise, it's not a prime number
    end if

    if (arrRecur[index] is prime number AND index > 0)
        Call the IsArrayPrimeRecur function again with size - 1 parameter
    end if

    print "Leaving IsArrayPrimeRecur" << endl

    return isPrime
end algorithm
*/

bool IsArrayPrimeRecur(int arrRecur[], int size)
{
    cout << "Entering IsArrayPrimeRecur" << endl;
    bool isArrayPrime = true;
    int index = size - 1;
    
    if (arrRecur[index] == 1) 
    {
        isArrayPrime = false;
    }

    else if ((arrRecur[index] != 2) && (arrRecur[index] % 2 == 0) )
    {
        isArrayPrime = false;
    }

    else if ((arrRecur[index] != 3) && (arrRecur[index] % 3 == 0))
    {
        isArrayPrime = false;
    }

    else
    {
        isArrayPrime = isPrimeRecur(arrRecur[index], 5);
    }

    if (isArrayPrime && index > 0)
    {
        isArrayPrime = IsArrayPrimeRecur(arrRecur, index);
    }

    cout << "Leaving IsArrayPrimeRecur" << endl;
    return isArrayPrime;
}

/*
Algorithm isPrimeRecur(dividend, divisor)

    This algorithm check if the all elements in the array is prime number or not with recursion
    Pre: dividend - a number that will be checked it's prime number or not
         divisor - a number that will divide the dividend
    Post: 
    Return: true if dividend is prime number. Otherwise, false

    set isPrime true

    print "Entering isPrimeRecur"

    if (square root of dividend + 1 is greater or equal than divisor)
        if (dividend is completely divided by divisor)
           it's not a prime number
        else
            isPrime = isPrimeRecur(dividend, divisor + 2)
        end if
    end if

    print "Leaving isPrimeRecur"
    return isPrime
end algoritm

*/

bool isPrimeRecur(int dividend, int divisor)
{
    bool isElementPrime = true;

    cout << "Entering isPrimeRecur" << endl;
    if (sqrt(dividend) + 1 >= divisor)
    {

        if (dividend % divisor == 0)
        {
            isElementPrime = false;
        }

        else
        {
            isElementPrime = isPrimeRecur(dividend, divisor + 2);
        }
    }

    cout << "Leaving isPrimeRecur" << endl;
    return isElementPrime;
}
