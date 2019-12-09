#include <stdio.h>

typedef long long FIBNACCI_TYPE;


/*!
    @brief 求解斐波拉契
*/
FIBNACCI_TYPE Fibonacci(FIBNACCI_TYPE n)
{
    const FIBNACCI_TYPE result[2] = {0, 1};

    if (n < 2)
    {
        return result[n];
    }

    FIBNACCI_TYPE fibN = 0;
    FIBNACCI_TYPE fibNum1 = 1;
    FIBNACCI_TYPE fibNum2 = 0;
    FIBNACCI_TYPE i = 0;

    for (i = 2; i <= n; i++)
    {
        fibN = fibNum1 + fibNum2;
        fibNum2 = fibNum1;
        fibNum1 = fibN;
    }

    return fibN;
}

FIBNACCI_TYPE RecursionFib(FIBNACCI_TYPE n)
{
    if (n <= 0)
    {
        return 0;
    }

    if (n == 1)
    {
        return 1;
    }

    return RecursionFib(n-1) + RecursionFib(n-2);
}

int main()
{
    int i = 0;

    for (i = 3; i < 10; i++)
    {
        printf("The Quick Algor %lld\n", Fibonacci(i));
        printf("The Recursion Algor %lld\n", RecursionFib(i));
    }

    return 0;
}
