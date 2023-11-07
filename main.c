#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>

extern char etext, edata, end; //we'll need to get these from the linker for what I'm wanting to do.

char firstBSSVar[128]; //uninitialized will put this in the BSS
static int bssInt; //This also goes in the bss

static char dataSTR[] = "Banana"; // and then these guys will go in the Data segment
int dataInt = 32;

int main(int argc, char *argv[])
{

    char *stackStart, *heapStart, *dataStart, *bssStart, *textStart;
    char stackStr[] = "Hello World";

    int *heapInt = malloc(sizeof(int)); //Ok. So changing the order of the mallocs seems to change things here
    char *heapString = malloc(sizeof(char) * 17);
    char *heapString2 = malloc(sizeof(char) * 10);


    //tethering it to argv[0] essentially means we'll be at the highest point in the stack and not have to worry about our variable declaration order as much
    stackStart = (char*) &argv[0]; //This seems like it should be the first point in the stack that we should be able to reach, assuming _start is unreachable
        //since input parameters are loaded onto the stack in reverse order prior to return addreess and PFP

    heapStart = sbrk(0); //this should theoretically give us the end of the heap. But we may come back to that. This seems

    dataStart = (char*) &edata;
    bssStart = (char*) &end; //So the "end", is going up. That explains a lot. Thank god for these graphics
    textStart = (char*) &etext;

    printf("Stack start: %p\n\n", stackStart);
    printf("Addresses for our pointers declared within our stack frame:\n");
    printf("stackStart: %p\n", &stackStart);
    printf("heapstart: %p\n", &heapStart);
    printf("datastart: %p\n", &dataStart);
    printf("bssStart: %p\n", &bssStart);
    printf("textStart: %p\n\n", &textStart); //from &stackstart to &textstart, the memAddresses for each of these vars decrements by 8 bytes every time. Things make some sense here

    for (int i = 0; i < strlen(stackStr); i++) {
        printf("Address for stackStr[%d]: %p\n", i, &stackStr[i]); //so MSB gets highest address, lsb gets lowest
    }

    printf("\nHeap \"Starts\": %p\n\n", heapStart);

    printf("Address for heapString[0]: %p\n", heapString);
    printf("Address for heapstring[1]: %p\n", &heapString[1]);
    printf("Address for heapstring[1]: %p\n", &heapString[2]);
    printf("Address for heapString[16]: %p\n\n", &heapString[16]); //So it looks like the heap is growing "up" while the stack grows down

    printf("Address for heapString2[0]: %p\n", heapString2);
    printf("Address for heapString2[1]: %p\n", &heapString2[1]);
    printf("Address for last char in heapString2: %p\n\n", &heapString2[9]);

    printf("Address of heap Int: %p\n", heapInt);

    printf("\nBSS starts %p\n\n", bssStart);

    printf("Address of our first BSS Var: %p\n", &firstBSSVar);
    printf("Address of firstBSSVar[1]: %p\n", &firstBSSVar[1]);
    printf("Address of firstBSSVar[127]: %p\n", &firstBSSVar[127]); //and then the last slot in our firstVar is 1 below the first byte of our int
    printf("Address of our BSS int: %p\n", &bssInt);    //Int always seems to come first, always offset

    printf("\nData Starts: %p\n\n", dataStart);

    printf("Address of dataSTR: %p\n", &dataSTR);   //and dataSTR[0] is the lowest address
    printf("Address of dataSTR[1]: %p\n", &dataSTR[1]);
    printf("Address of the last character in dataSTR: %p\n", &dataSTR[5]);
    printf("Address of our data int: %p\n", &dataInt);  //looks like the int comes first again

    printf("\nText starts: %p\n\n", textStart); //and then this should only be read-only so I don't think we can pull much from here


    free(heapString);


    //This may come in handy for total memory. Tough to say as of right now though
    // struct rusage usage;
    // getrusage(RUSAGE_SELF, &usage);



    // printf("Memory used: %ld KB\n", usage.ru_maxrss);

    return 0;
}
