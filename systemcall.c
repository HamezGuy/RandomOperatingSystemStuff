int getiocounts(struct iostat* iostat)
{
    //TODO do here
}

struct iostat {
    int readcount;  // total number of times read() is invoked by the current running process (including failed calls)
    int writecount; // total number of times write() is invoked by the current running process (including failed calls)
}