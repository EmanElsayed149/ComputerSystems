/* 
 * CS:APP Data Lab 
 * 
 * <Eman elsayed>
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
  /*
  x^y=y`x+x`y
  y`=~y+1
  a+b=(a`b`)`
  */
  int xorres=~((~(x&~y))&(~(~x&y)));
  return xorres;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /*
  0x80000000=1<<31
  */
  return (1<<31);
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 2
 */
int isTmax(int x) {
  /*
  max number is 0x7fffffff
  0x7fffffff=~(1<<31)
  use xor instead of using == for equality
  */
  int check= ~(1<<31);
  return !(x^check);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /*
  this return 1 if x & 0xAAAAAAAA = 0xAAAAAAAA
  */
  int bias=0xAA; 
  int check = (0xAA<<8)+bias;
  check= (check<<8)+bias;
  check= (check<<8)+bias; 
  return !((x & check) + ~check +1);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~x)+1;
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
  //x must equal (0x3m) and m must less than 9
  // to check about 0x3 !((x>>4)^0x03)
  // to check  first four bits !( (x>>3)&1  &   ((x>>2)&1 | (x>>1)&1) )
  // then i am sure that fourth bit and second bit all not equal 1 
  // and sure that fourth bit and third bit all not equal 1
  int res= (!((x>>4)^0x03)) & (!( ((x>>3)&1) & (((x>>2)&1)|((x>>1)&1)) ));
  return res;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  //x=((~x)+1)>>31;   // if x =0 then it remain 0 else 0xffffffff but it will wrong in case x is negative 
  // to be right in case of x negative use (x>>31) it will 0xffffffff
  // if x=0 then z else 0 (~x & z)
  // if x=0xffffffff then y else 0 (y&x)
  x=(x>>31) | (((~x)+1)>>31);
  int res=(y&x)+(~x &z);
  return res;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // to check equality use ^ 
  // to check less than (x-y) if it negative return true,if (x-y) negative or not (x-y)>>31 it will 1 else it will 0
  // there will be issue in case of x and y have different sign (overflow)(xpositive y negative)
  // When x, y have differnt sign, you can get the result trivally.
  // briefly this function return true in case of :
  // 1- equalcheck or (xnegative ypositive) or (x,y same sign x<y)
  int equalcheck= !(x^y);
  int xsign = (x>>31) &1;
  int ysign = (y>>31) &1;
  int XnegativeYpositive = xsign & (!ysign);
  int samesign = !(xsign ^ ysign);
  int diff = x + ~y +1;
  int diffsign = (diff>>31) & 1 ;
  int res= equalcheck | XnegativeYpositive | (samesign & diffsign);
  return res;
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
  //first x=0 if it=0 else 0xffffffff
  // then not x (~x) it will 0xffffffff if x=0 else 0
  // and result  with 1
  x=(x>>31) | (((~x)+1)>>31);
  x = ~x;
  int res=x&1;
  return res;
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
  /*
     * We first bit invert all negative numbers and
     * use binary search to find out the log2(n).
     * Then we add 1 to the final result since we need
     * the MSB to represent the sign.
     * Note: finding the following things are equal:
     * 1. find the most significant bit of 1 for positive numbers
     * 2. find the most significant bit of 0 for negative numbers
  */
  int sign,bit16,bit8,bit4,bit2,bit1,bit0,res=0;
  sign = x>>31;
  x= (sign & ~x) | (~sign & x); // inverting negative numbers 

  bit16= (!!(x>>16)) <<4;       // if most signefit bit contain any ones then res >16
  x = x>>bit16; 

  bit8= (!!(x>>8)) <<3 ;
  x = x>>bit8;
  
  bit4= (!!(x>>4)) <<2;
  x= x>>bit4;

  bit2= (!!(x>>2)) <<1;
  x = x>>bit2;

  bit1= (!!(x>>1));
  x = x>>bit1;

  bit0=x;
  res= bit16+bit8+bit4+bit2+bit1+bit0+1;
  return res;
}
//float
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  // IEEE format: [1: sign bit][8: exp][23: Mantissa]
  // you will treat num as float so there is some condition you should take care 
  // 1-if most signifit bit it 1 then num is negative single persicion(signBitMask= uf>>31)
  // 2-if exp value is equal 255 this mean f is infinity and return itself 
    //(exp=(uf>>23)&0xff)    (special case ) 
  // 3-if exp value is equal 0   and f bits(Mtail)=0 then return num it self (because num is equvilant to zero)
      //(Mtail= (uf<<9)>>9) if Mtail not equal 0 what is equevilant value for this representation ?
      // M=f E=1-Bias   v=M*2^E   fractional value so 2*f = uf<<1 | (signBitMask) to  save signbit as it was 
      //(denormalize case)
  // 4-if exp != 255 or 0 then 2*f=M*2^(E+1)  E=exp-bias  then newexp=exp+1 (oneexp=0x00800000)
  // but if exp+oneexp is equal 255 2*f= infinity so Mtail should become zeros (tricky poingt)
  // let's go for coding  (keep going you are hero...i will keep trying untill death  )
  unsigned signBitMask= 0x80000000;    // logic bit because uf is unsigned 
  unsigned exp=(uf>>23) & (0xff);
  unsigned infinityFlag= !(exp^0xff);
  unsigned expAllZeroFlag= !(exp);
  unsigned Mtail= (uf<<9)>>9;
  unsigned MtailAllZeroFlag= !(Mtail);
  unsigned oneExp=0x00800000;
  unsigned KeepSignBit = uf & signBitMask;
  if(infinityFlag)
  {
    // uf is infinity 
    // return itself;
  }else if (expAllZeroFlag)
  {
    if(MtailAllZeroFlag)
    {
      //num is equal =0 return 0
    }else{
      // num is fractional , denormalized case
      uf = uf <<1;
      uf = uf | KeepSignBit;   //to remain sign as it was  
    }
  }else{
    //normalized case
    // to doublicate num exp=exp+1;
    //2*f=M*2^(E+1)  E=exp-bias  E+1 =exp-bias+1   exp= exp+1;
    if(!((exp+1)^0xff))  // infinity case 
    {
      uf = uf + oneExp ; // increase exp by one 
      uf = uf & (0xff800000);
    }else{
      uf = uf + oneExp;
    }
  }
  return uf;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  unsigned MtailBitMask,expBitMask,firstRemovedBitIndex,removedBitsMask,Bias=127,uf;
  unsigned sign=x>>31;
  unsigned signBitMask= 0x80000000 & x;
  unsigned ux= (~sign&x) | (sign&(~x+1));  // make ux = |x| always positive
  // compute index of first nonzero bit from  most significant bit 
  int index=31;
  for(;index>=0 && !(0x1 << index)&ux;)
  {
    index = index-1;
  }
  unsigned uxwithoutfirstonetozero=ux-(1<<index);
  // compute exp and fractial part (Mtail)
  // special case you should put it in your eyes :
  // 1-Denormalized case can't exist because we represent int num  and this case to represent fractions only
  // 2-if index =-1 this mean ix=0 so exp =0 , Mtail =0
  // 3-else Mtailbits = index   MtailBitMask=(ux<<(31-index))>>(31-index)  E=index exp=E+127;
  if(index==-1) 
  {
    // num is equal zero 
    ux=0;
  }else if (index<=23)
  {
    // fraction bit should expands to 23 bit and subtract one in index from num 
    MtailBitMask=uxwithoutfirstonetozero <<(23-index);
    // E=index ;
    expBitMask= (index+Bias) <<23;
    ux= expBitMask | MtailBitMask | signBitMask;

  }else{
    //in this case frac bit are more than 23 so num will be rounded(least significant bits=(index-23)bits will be shifted right )
    //least significant bit should be rounded (round to even mode )
    // firstRemovedBitIndex : index of first removed bit 
    // REmoved bit mask to check if more than halfway or not 
    // firstremovedBitMask: value of firstremoved bit 
    // roundedbit : value of bit which will be rounded (0,1)
    firstRemovedBitIndex=(index-24);
    removedBitsMask= ux<<(32-firstRemovedBitIndex);
    unsigned firstRemovedBitMask = (ux>>firstRemovedBitIndex) & 1 ;
    unsigned roundedBit = (ux>>index) & 1;
    MtailBitMask = (uxwithoutfirstonetozero>>(index-23)) & (0x007fffff);  // 0x007fffff to reset expbits
    if(firstRemovedBitMask)
    {
      if(roundedBit)
      {
        MtailBitMask +=1;
      }else{
        if(removedBitsMask)
        {
          MtailBitMask +=1;
        }
      }
    }
    expBitMask=(index+Bias)<<23;
    uf= expBitMask | MtailBitMask | signBitMask;
  }
  return uf;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
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
int float_f2i(unsigned uf) {
  //steps :
  //1-sign flag to indicate if num is megative
  //2-calculate exp(expBitMask) , there are three conditions :
  //  normalize denormalized (exp=0) special (exp=255)
  //  in Denormalized case return 0
  //  in special case return 0x80000000u. (nan - infinity)
  //3-to calculate int num in normalized case :
  //  v=(1+f)*(2^E)  if E -ve return 0 
  //  if E >30 this mean that int number need more than 32 bit for representation
  //  else M= 0x0800000 + frac; 
  //  E > 23 (res= M <<(E-23))  else (res= M >> (23-E))
  unsigned expMask,outOfRange = 0x80000000,fracMask,frac,M,signBitMask = 0x80000000;
  int bias = 127,E,res;
  int signflag = signBitMask &  uf;

  expMask = 0x7f800000;
  int exp = (uf&expMask)>>23;
 

  fracMask = 0x007fffff;
  frac = uf & fracMask;
  if(!exp)
  {
       return 0;
  }
  else if (exp==255)
  {
        return outOfRange;
  }else
  {
      E=exp-bias;

      if(E<0)
      {
           return 0;
      }
      else if(E > 30)  //tricky point 
      {
          return outOfRange;
      }

      M = 0x0800000 + frac;
      if(E>23)
      {
           res = M << (E-23);
      }else
      {
           res = M >> (23-E);
      }
  }

  // handel sign bit
  if(signflag)
  {
     res = -res;
  }
  return res;
}
