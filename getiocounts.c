#include "sysproc.c"
#include "syscall.h"
#include "syscall.h"
#include "types.h"
#include "stat.h"
#include "user.h"
//return 0 on completion, -1 on failure 
int getiocounts(struct iostat* iostat)
{
    //write is pid 16, read is 5
    if(iostat == NULL)
    {
        return -1;
    }

    int readCounter = 0;
    int writeCounter = 0;

    //for every readcounter and writecounter increment the value

    iostat->readcount = readCounter;
    iostat->writecount = writeCounter;

    return 0;
}

struct iostat {
    int readcount;  // total number of times read() is invoked by the current running process (including failed calls)
    int writecount; // total number of times write() is invoked by the current running process (including failed calls)
}