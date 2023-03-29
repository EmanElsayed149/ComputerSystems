#include <stdio.h>
#include <stdlib.h>
#include "cachelab.h"
#include <getopt.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
void parse(unsigned *sptr,unsigned *Sptr,unsigned *Eptr,unsigned *bptr,unsigned *Bptr,char **tracefileptr,int argc,char *argv[])
{
    int opt;
    //getopt for parsing arsing elements on the unix commandline(s,E,b,t)
    while((opt=getopt(argc,argv,"s:E:b:t:"))!=-1)
    {
        switch(opt)
        {
            case 's' :
                *sptr = atoi(optarg);
                *Sptr = pow(2,*sptr);
                break;
            case 'E' :
                *Eptr = atoi(optarg);
                break;
            case 'b' :
                *bptr = atoi(optarg);
                *Bptr = pow(2,*bptr);
                break;
            case 't' :
                *tracefileptr = optarg;
                break;
            default :
                printf("error: unrecognized option\n");

        }
    }
}
typedef struct 
{
    int valid;
    int tag;
    int accesstime;
}cacheline;
int cachehit(cacheline *cache, unsigned setindex, unsigned tagnumber, unsigned E,int time)
{
    int Bias = E * setindex ;  //to arrive at first line in setindex 
    cacheline *lineptr = cache + Bias; 
    //check if there is tag match with tagnumber in address
    for(int line=0;line <E;line++)
    {
        cacheline* currentlineptr = lineptr+line;
        int check = (currentlineptr->tag==tagnumber ) && (currentlineptr->valid==1);
        if (check) 
        {
            currentlineptr->accesstime = time;
            return 1;
        }
    }
    return 0;
}
int emptyline(cacheline *cache, unsigned setindex, unsigned tagnumber, unsigned E,int time )
{   
    int Bias = E * setindex ;  //to arrive at first line in setindex 
    cacheline *lineptr = cache + Bias;
    //check if there is empty line
    for(int line=0;line <E;line++)
    {
        
        cacheline* currentlineptr = lineptr+line;
        int check = (currentlineptr->valid==0);
        if (check)
        {
            currentlineptr->accesstime = time;
            currentlineptr->valid = 1;
            currentlineptr->tag = tagnumber;
            //printf("%d %d %d\n",currentlineptr->accesstime,currentlineptr->valid,currentlineptr->tag);
            return 1;
        }
    }
    return 0;
}
void replace(cacheline *cache, unsigned setindex, unsigned tagnumber, unsigned E,int time )
{
    
    int Bias = E * setindex ;  //to arrive at first line in setindex 
    cacheline *lineptr = cache + Bias;
    int leastaccesstime= lineptr->accesstime;

    //target line (with least used line)
    cacheline* targetlineptr=lineptr ;

    //search for  Least Recently Used line
    for(int line=0;line <E;line++)
    {
        cacheline* currentlineptr = lineptr+line;
        int check = (currentlineptr->accesstime < leastaccesstime);
        if (check)
        {
            leastaccesstime = currentlineptr->accesstime;
            targetlineptr =currentlineptr;
        }
    }
    targetlineptr->tag = tagnumber;
    targetlineptr->accesstime = time;
    targetlineptr->valid = 1;
    return;
}
void loadtocache(cacheline *cache,unsigned setindex,unsigned tagnumber,unsigned S,unsigned E,unsigned* hit_countptr,unsigned* miss_countptr,unsigned* eviction_countptr,int accesstime)
{
    
    
    if(cachehit(cache,setindex,tagnumber,E,accesstime))
    {
        printf(" hit\n");
        (*hit_countptr)++;
        return ;
    }
    // if cache not hit (miss case) find empty line in the same set
    if(emptyline(cache,setindex,tagnumber,E,accesstime))
    {
        printf(" miss\n");
        (*miss_countptr)++;
        //printf("%d \n",*miss_countptr);
        return;
    } 
    // if there isn't empty space s0 it must replace line using (Least Recently Used replacement policy)
    
    replace(cache,setindex,tagnumber,E,accesstime);
    printf(" miss eviction\n");
    (*eviction_countptr)++;
    (*miss_countptr)++;
    return;


}
cacheline *initcache(unsigned S,unsigned E)
{
    cacheline *cache = (cacheline *)malloc(sizeof(cacheline)*S*E);
    for(int set=0;set<S;set++)
    {
        for(int line=0;line<E;line++)
        {
            (cache+set*E+line)->valid = 0;
            (cache+set*E+line)->tag = 0;
            (cache+set*E+line)->accesstime = 0;
        }
    }
    return cache;
}

void (*storetomemory)(cacheline *cache,unsigned setindex,unsigned tagnumber,unsigned S,unsigned E,unsigned* hit_countptr,unsigned* miss_countptr,unsigned* eviction_countptr,int accesstime);
void (*modifydata)(cacheline *cache,unsigned setindex,unsigned tagnumber,unsigned S,unsigned E,unsigned* hit_countptr,unsigned* miss_countptr,unsigned* eviction_countptr,int accesstime);

int main(int argc,char *argv[])
{
    unsigned hit_count=0,miss_count=0,eviction_count=0,s,E,b,S,B,size;
    long long address;
    int accesstime=0;
    char stringoperation[3];//=malloc(sizeof(char)*2); 
    char operation;
    FILE *file;   //for open file
    char *tracefile;  //filename 

    parse(&s,&S,&E,&b,&B,&tracefile,argc,argv);  //getopt for parsing arsing elements on the unix commandline(s,E,b,t)
    //printf("%d %d %d \n",S,E,B);  fflush(stdout);

    //init cache (allocate space for each cacheline and clear valid bit and access time)
    cacheline* cache = initcache(S,E);

    ///reading file 
    //each line in trace files contain operation , address , size 
    file = fopen (tracefile, "r");
    while(fscanf(file,"%s %llx,%d\n",stringoperation,&address,&size)!=EOF)
    {
        accesstime++;
        //maping address to identify setindex,tagnumber
        unsigned setmask = ~(-1 << s);  //make first s bits =1 and other =0
        unsigned setindex = setmask & (address>>b);
        unsigned tagnumber = address >>(s+b) ;
        //printf("%d  %d\n",setindex,tagnumber);

        operation = strlen(stringoperation)>1 ? stringoperation[1] : *stringoperation; //because space in some operations
        if(operation !='I'){printf("%c %llx %d",operation,address,size);}
        //all operation are same according to simulater (check if hit if not check for empty line else evict)
        //but I have different name for readability
        storetomemory = loadtocache;
        modifydata = loadtocache;
        switch(operation)
        {
            case 'L' : 
                loadtocache(cache,setindex,tagnumber,S,E,&hit_count,&miss_count,&eviction_count,accesstime);
                break;
            case 'S' :
                storetomemory(cache,setindex,tagnumber,S,E,&hit_count,&miss_count,&eviction_count,accesstime);
                break;
            case 'M' :
                hit_count++;
                modifydata(cache,setindex,tagnumber,S,E,&hit_count,&miss_count,&eviction_count,accesstime);
                break;
            
        }
    }
    
    printSummary(hit_count,miss_count,eviction_count);
    return 0;
    
}
