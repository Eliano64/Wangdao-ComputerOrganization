#include <stdio.h>

unsigned add(unsigned a, unsigned b, unsigned is_sub) {
  if (is_sub) {
    b = ~b + 1;
  }
  return a + b;
}

float fadd(float a, float b) {
  unsigned a1 = *((unsigned *)&a);
  unsigned b1 = *((unsigned *)&b);
  // 取符号
  unsigned af = (a1 >> 31);
  unsigned bf = (b1 >> 31);
  // 阶
  unsigned ak = (a1 >> 23) & 0xff;
  unsigned bk = (b1 >> 23) & 0xff;
  // 1.尾数*2^23
  unsigned at = (1 << 23) | (a1 & 0x7fffff);
  unsigned bt = (1 << 23) | (b1 & 0x7fffff);
  // 对阶 向大的对齐 阶数增加尾数右移
  int k;
  if (ak > bk) {
    if (ak - bk > 23) { //大数吃小数
      return a;
    }
    k = ak;
    bt >>= (ak - bk);
  } else {
    if(bk - ak > 23){
        return b;
    }
    k = bk;
    at >>= (bk - ak);
  }
  // 尾数计算
  unsigned f;
  unsigned t1; // t1为1t，尾数前加上1
  if (af == bf) {
    t1 = add(at, bt, 0);
    f = af;
  } else {
    if (at > bt) {
      t1 = add(at, bt, 1);
      f = af;
    } else {
      t1 = add(bt, at, 1);
      f = bf;
    }
  }
  // 现在，f k 1t皆得到
  //  规格化 主要是1t
  // 1t必须在2^23~2^24-1
  // 判0
  if (t1 == 0) {
    unsigned res = 0;
    return *(float *)&res;
  }
  while ((t1 >> 24) & 1) { // 即使t1较大时可能bit23也为0
    t1 >>= 1;              // 直接截断
    ++k;
    if (k > 0xfe) { // 上溢
      unsigned res = (f << 31) | 0x7f800000;
      return *(float *)&res; // inf
    }
  }
  while (!((t1 >> 23) & 1)) {
    t1 <<= 1;
    --k;
    if (k < 1) { // 下溢
      break;
    }
  }
  unsigned res = (f << 31) | (k << 23) | (t1 & 0x7fffff);
  float fres = *(float *)&res;
  return fres;
}

float fsub(float a, float b) {
  unsigned b1 = *((unsigned *)&b);
  b1 ^= 0x80000000; // 符号取反
  b = *((float *)&b1);
  float res = fadd(a, b);
  return res;
}

// 限制：输入为规格化数
int main() {
  float a, b;
  scanf("%f %f", &a, &b);
  float res = fadd(a, b);
  printf("%.9e\n", res);
  float res2 = fsub(a, b);
  printf("%.9e\n", res2);
  return 0;
}