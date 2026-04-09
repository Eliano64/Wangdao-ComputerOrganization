#include <stdio.h>

int isub(int a, int b)
{
    b =  (b^0xffffffff)+1;
    return a+b;
}

//booth算法 有符号相乘
//将有符号二进制数拆成若干二的整数次方相加减
// 例： b= 01001 = 01001'(0) = +10000 - 1000 + 10 - 1
// b = 1111 = -1
// 只关注“阶跃”,即"01""10"
int imul(int a, int b)
{
    int res = 0;
    int low = 0;
    for (int i = 0; i < 32; i++)
    {
       int last = (a&1);
       if(last == 1 && low == 0){
           res = isub(res,b);
       }
       else if(last == 0 && low == 1){
           res += b;
       }
       low = last;
       a >>= 1;
       b <<= 1;
    }
    return res;
}

int main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    int res = imul(a, b);
    printf("%d\n", res);
    return 0;
}