#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>

extern char etext, edata, end; //we'll need to get these from the linker for what I'm wanting to do.

char firstBSSVar; //uninitialized will put this in the BSS

int main(int argc, char *argv[])
{

    char *stackStart, *heapStart, *dataStart, *bssStart, *textStart;

    stackStart = (char*) &argv[0]; //This seems like it should be the first point in the stack that we should be able to reach, assuming _start is unreachable
        //since input parameters are loaded onto the stack in reverse order prior to return addreess and PFP

    heapStart = sbrk(0); //this should theoretically give us the end of the heap. But we may come back to that.

    dataStart = (char*) &edata;
    bssStart = (char*) &end; //So the "end", is going up. That explains a lot. Thank god for these graphics
    textStart = (char*) &etext;

    printf("Stack start: %p\n", stackStart);

    printf("Heap \"Starts\": %p\n", heapStart);

    printf("BSS starts %p\n", bssStart);

    printf("Data Starts: %p\n", dataStart);

    printf("Text starts: %p\n", textStart);





    //This may come in handy for total memory. Tough to say as of right now though
    // struct rusage usage;
    // getrusage(RUSAGE_SELF, &usage);



    // printf("Memory used: %ld KB\n", usage.ru_maxrss);

    return 0;
}
