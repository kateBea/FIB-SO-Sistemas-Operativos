/*SOME NOTES ABOUT malloc()*/
/*
Normally,  malloc() allocates memory from the heap, and adjusts
the size of the heap as required, using sbrk(2).  When allocat‐
ing blocks of memory larger than MMAP_THRESHOLD bytes, the glibc 
malloc() implementation allocates  the  memory  as  a  private
anonymous  mapping using mmap(2).  MMAP_THRESHOLD is 128 kB by 
default, but is adjustable using mallopt(3).  Prior to Linux 4.7
allocations performed using mmap(2) were unaffected by the RLIMIT_DATA 
resource limit; since Linux 4.7, this limit is also  enforced for 
allocations performed using mmap(2).

To avoid corruption in multithreaded applications, mutexes are 
used internally to protect the memory-management data structures
employed by these functions.  In a multithreaded application 
in which threads simultaneously allocate and  free  memory,  there
could be contention for these mutexes.  To scalably handle memory 
allocation in multithreaded applications, glibc creates addi‐
tional memory allocation arenas if mutex contention is detected.  
Each arena is a large region of memory that is internally al‐
located by the system (using brk(2) or mmap(2)), and managed with 
its own mutexes.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_ITERATIONS 3
#define REGION_SIZE 4096

char globalArray[REGION_SIZE];

int main(int argc, char *argv[])
{
  char buff[80];
  int niterations = DEFAULT_ITERATIONS;
  int i;
  char localArray[REGION_SIZE];
  char *p;

  if (argc > 2)
  {
    sprintf(buff, "Usage: mem1 [numMallocs]\n");
    write(2, buff, strlen(buff));
    exit(1);
  }

  if (argc == 2)
  {
    niterations = atoi(argv[1]);
  }

  sprintf(buff, "Addresses:\n");
  write(1, buff, strlen(buff));
  sprintf(buff, "\tglobalArray: %p\n", globalArray);
  write(1, buff, strlen(buff));
  sprintf(buff, "\tlocalArray: %p\n", localArray);
  write(1, buff, strlen(buff));
  sprintf(buff, "\tp: %p\n", &p);
  write(1, buff, strlen(buff));

  for (i = 0; i < niterations; i++)
  {
    p = malloc(REGION_SIZE);
    sprintf(buff, "\tp: %p, region %d: %p\n", &p, i, p);
    write(1, buff, strlen(buff));
  }

  while (1);
}
