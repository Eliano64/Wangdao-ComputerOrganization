#include <assert.h>
#include <stdio.h>

// 无符号数相减，a - b = (a - b)%M = (a + (M - b))%M 上溢a>=b
unsigned int usub(unsigned int a, unsigned int b, unsigned int *CF) {
  b = (b ^ 0xffffffff) + 1;
  unsigned long long int c = (unsigned long long int)a + b;
  *CF = (c >> 32) & 1;
  return (unsigned int)c;
}

// uint恢复余数法
unsigned int division(unsigned int a, unsigned int b) {
  assert(b != 0);
  unsigned int *CF;
  unsigned int t;
  CF = &t;
  usub(a, b, CF);
  if(!(*CF)){
    return 0; //a<b
  }
  unsigned long long int al = a;
  // 商最高位一定为0
  for (int i = 0; i < 32; ++i) {
      al <<= 1;
    // 最高32位与b相减
    unsigned int at = (al >> 32);
    unsigned int alow = (unsigned int)al; //存低32位
    at = usub(at,b,CF); //减去除数
    if(*CF){  // a>=b,商1不恢复
        al = ((unsigned long long int)at << 32) | alow;
        al += 1;
    }//a<b时商0恢复（即at不写入al高32位）
  }
  return (unsigned int)al;
}

int main() {
  unsigned int a, b;
  scanf("%u %u", &a, &b);
  unsigned int res = division(a, b);
  printf("%u\n", res);
  return 0;
}