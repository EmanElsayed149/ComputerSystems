long absdiff(long x,long y)
{
    long rval=x-y;
    long eval=y-x;
    long ntest= (x<y);
    if(ntest) rval=eval;
    return rval;
}
long fast_do(long n)
{
    long result=1;
    do
    {
        result*=n;
        n-=1;
    }while(n>1);
    return result;
}
long fact_while(long n)
{
    long result =1;
    while(n>1)
    {
        result*=n;
        n-=1;
    }
    return result;
}
//code for switch
void switch_eg_impl(long x,long n,long *dest)
{
    static void *jt[7]={
        &&loc_A, &&loc_def, &&loc_B,
        &&loc_C, &&loc_D, &&loc_def,
        &&loc_D 
    };
    unsigned long index=n-100;
    long val=x;
    if (index>6) goto loc_def;
    goto *jt[index];
    loc_A: //case of 100
        val*=13;
        goto done;
    loc_B: //case of 102
        val+=10;
        //fall through
    loc_C: //case of 103
        val+=11;
        goto done;
    loc_D: //case of 104 and 106
        val*=val;
        goto done;
    loc_def: //case of defualt 
        val=0;
    done:
        *dest = val;
}
//switch proble.31
void switcher(long a,long b,long c,long *dest)
{
    long val;
    switch(a)
    {
        case 5:
            c=a^15;
        case 0:
            val=c+112;
            break;
        case 2:
        case 7:
            val=(a+c)<<2;
            break;
        case 4:
            val=b;
            break;
        defualt:
            val=a;
    }
    *dest =val;

 }
 // aray fixed size pointer based 
 typedef int fix_matrix[16][16];
 int fix_prod_ele(fix_matrix A,fix_matrix B,long i,long k)
 {
    long j;
    int result=0;
    for(j=0;j<16;j++){
        result+=A[i][j] * B[j][k];
    }
    return result;
 }
 /*it's equivilabt to optimized c code*/
 // array variabel-size array-based
 int var_prod_ele (long n,int A[n][n],int B[n][n],long i,long k)
 {
    long j;
    int result=0;
    for(j=0;j<n;j++)
    {
        result+= A[i][j] * B[j][k];
    }
    return result;
 }