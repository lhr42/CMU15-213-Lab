/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(((~(x & (~y)))) & (~((~x) & y)));//异或: 与或式 二次取反 转化为 与非式 (逻辑函数表达式的转换)
  //结果也可以使用“非”和“与”计算不是同时为0情况和不是同时为1的情况进行位与，即~(~x&~y)&~(x&y)
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  //将 x 加1的值再和 x 相加，得到了全1，然后取反得到全0，因为补码-1也有这个特点，所以要排除
  int a = x + 1;
  int b = a + x;
  b += !a;//排除x = -1(x + 1 为 全0)的情况,
  return !~b;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int mask = 0xAA + (0xAA << 8);
  mask = mask + (mask << 16);
  //掩码中的1保留x的特征, 0掩盖x的特征. x & 掩码 之后必须与mask相同
  return !(mask ^ (mask & x));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  //-x的补码实际上就是带符号位取反 + 1
  //因为 x + -x == 0，所以 -x 可以通过对 x 取反加1得到。
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  //定义两个数.
  //b = high + 大于0x39的数后 符号由0变1 b符号位要为0
  //a = low + 0x30 符号恰好由负变正 a要为正
  // int Tmin = 1 << 31;
  // int high = Tmin + (~0x3A + 1);//1000···0000 - k 可以不用‘-’实现
  // printf("high:%x\n", (unsigned int)high);
  // int low = 0 + (~0x30 + 1);
  // int flag1 = (high + x) & Tmin >> 31;
  // int flag2 = (low + x) & Tmin >> 31; 
  // return (!flag1) & flag2;

  //用加[-x]的补码实现减法操作
  int a = x + (~0x30 + 1);
  int b = x + (~0x3A + 1);
  a >>= 31;
  b >>= 31;
  return (!a) & b;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int flag = !!x;
  //0000···0001变为全1, 0为全0
  int mask = ~flag + 1;//[0 - x]补
  return (y & mask) | (z & ~mask);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int flag1 = x >> 31;
  int flag2 = y >> 31;
  int s = (y + (~x + 1)) >> 31;
  //符号相同时且s为0 或 flag1为0且flag2为1 时返回1
  return (!(flag1 ^ flag2) & !s) | (flag1 & !flag2);
  //有人说这样当y、x符号不同时直接做差可能会爆int, 应该先判断符号
  // return !((y + (~x + 1)) >> 31);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  //只有0 和 Tmin 的补码和自身相同, 其他互为相反数(所以符号位一个是1一个是0)
  //Tmin 和Tmin补码的符号位都为1, 0都为0
  //(x | (~x + 1)) >> 31 结果为全0(if x == 0), 为全1(if x != 0)
  return ((x | (~x + 1)) >> 31) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  // -5 = 1, 00000101
  // 1, 11111011 4'
  // -1 = 1, 00000001
  // 1, 11111111 1' = 0 + 1
  // 0x80000000: 1, 00000000 32' = 31 + 1
  //若x为正数, 找到1的最高位置, 答案所有位数 + 1位符号位; 若为负数, 找到0的最高位置, 所以取反之后和正数处理方法一样
  int sign = x >> 31;
  int b16, b8, b4, b2, b1, b0;
  x = (sign & ~x) | (~sign & x);
  //二分的思想
  b16 = !!(x >> 16) << 4;//若x的高16位中有一位为1, !!(x >> 16)等于1, 否则等于0
  x >>= b16;//若x的高16位中有一位为1, 再在这高16位中继续看高8位;否则, 在低16位中看
  b8 = !!(x >> 8) << 3;
  x >>= b8;
  b4 = !!(x >> 4) << 2;
  x >>= b4;
  b2 = !!(x >> 2) << 1;
  x >>= b2;
  b1 = !!(x >> 1);
  x >>= b1;
  b0 = x;//如果最后2位中高位无1, 则低位必然是1
  return b16 + b8 + b4 + b2 + b1 + b0 + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  unsigned exp = (0x7F800000 & uf) >> 23;
  unsigned frac = 0x7FFFFF & uf;
  unsigned s = uf >> 31 & 1;
  if(exp == 0xFF) return uf;//特殊值: exp全1, 代表NaN、无穷
  if(!exp){
    //非规格化值,exp全0
    frac <<= 1;
    return (s << 31) | frac;
  }
  //规格化值
  exp++;
  return (s << 31) | (exp << 23) | frac;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  //对规格化值: E = exp - bias < 0, (int)取整后为0
  //  E >= 31, out of range
  unsigned s = uf >> 31 & 1;
  unsigned exp = (uf & 0x7F800000) >> 23;
  unsigned frac = uf & 0x7FFFFF;
  int E = exp - 127;
  if(E >= 31) return  0x80000000u;//特殊值exp全1也包括在这种情况内
  if(E < 0) return 0;//非规格化值exp全0也包括在这种情况内
  frac = frac | (1 << 23);//添上隐含1
  //模拟小数点移动
  if(E >= 23) frac <<= E - 23;
  else  frac >>= 23 -E;//舍弃移动后的小数点后面的精度
  return  s ? -frac : frac;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  //(exp - bias127) range : [-126, 127];
  if(x >= 128)  return 0xFF << 23;//+INF
  if(x < -149) return 0;//达到非规格化的最小值: -126 + -23(frac最低位) = -149
  if(x < -126)  return 1 << (23 - (-126 - x));//非规格化中接近于0的数
  return x + 127 << 23;
}