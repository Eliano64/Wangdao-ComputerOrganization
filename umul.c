#include <stdio.h>

unsigned long long int umul(unsigned int a, unsigned int b)
{
    unsigned CF = 0; //CF存进位
    unsigned long long int al = (unsigned long long int)a;
    int cnt = 32;
    while(1){
        if(al&1){
            unsigned long long int ah = (al>>32) + b;
            CF = (ah>>32)&1; //进位
            al = (ah<<32)|(unsigned int)al; //高32位与低32位拼接
        }
        al >>= 1; //右移
        al |= (unsigned long long)CF<<63; //进位右移至乘积寄存器里
        CF = 0; //进位清零
        cnt--;
        if(cnt<=0){
            break;
        }
    }
    return al;
}

int main()
{
    unsigned int a,b;
    scanf("%u %u",&a,&b);
    unsigned long long int res = umul(a, b);
    printf("%llu\n", res);
    return 0;
}