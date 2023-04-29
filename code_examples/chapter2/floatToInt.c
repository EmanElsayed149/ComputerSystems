#include <stdio.h>
int float_f2i(unsigned uf) {
  //steps :
  //1-sign flag to indicate if num is megative
  //2-calculate exp(expBitMask) , there are three conditions :
  //  normalize denormalized (exp=0) special (exp=255)
  //  in Denormalized case return 0
  //  in special case return 0x80000000u. (nan - infinity)
  //3-to calculate int num in normalized case :
  //  v=(1+f)*(2^E)   = (2^E)+(2^E)*f 
  unsigned expMask,outOfRange = 0x80000000,fracMask,frac,M,signBitMask = 0x80000000;
  int bias = 127,E,res;
  int signflag = signBitMask & uf;

  expMask = 0x7f8fffff;
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
int main(){
    int res=float_f2i(0xbf800000);
    printf("res= 0x%08x",res);
    return 0;
}