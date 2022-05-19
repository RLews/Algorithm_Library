/** 
 * @FilePath: \undefinedd:\git\Algorithm_Library\CatalanNum\catalan.c
 * @brief: 
 * @details: 
 * @author: Lews Hammond
 * @Date: 2022-05-19 20:53:35
 * @LastEditTime: 2022-05-19 21:01:28
 * @LastEditors: Lews Hammond
*/

#include <stdio.h>


unsigned long long catalan(unsigned int n)
{
    unsigned long long num = 0;
    unsigned int i = 0;

    if (n <= 1)
    {
        return 1;
    } 

    for (i = 0; i < n; i++)
    {
        num += catalan(i) * catalan(n - i - 1);
    }

    return num;
}

int main(void)
{
    int i = 0;

    for (i = 1; i < 10; i++)
    {
        printf("%lld\n", catalan(i));
    }

    return 0;
}
