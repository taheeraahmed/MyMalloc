#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//Necessary variables
int has_initialized = 0; 
// Creating the memory (list) we're going to be working on
#define MEM_SIZE (64*1024)
uint8_t heap[MEM_SIZE];
//Start/end of memory heap area
void *managed_memory_start;

// Memory control block - start and end of heap memory area
struct mem_control_block
{
    int size;
    struct mem_control_block *next;
    
};
// pointer to start of our free list
struct mem_control_block *free_list_start;
// Declaring current pointer
struct mem_control_block *current;

// Initializing malloc function
void mymalloc_init()
{
    // Memory start is set to start of heap-list (since we dont have anything
    // to allocate yet)
    managed_memory_start = &heap;
    printf("Managed memory start: %p", managed_memory_start);
 
    // typecast managed_memory_start
    struct mem_control_block *m = (struct mem_control_block *)managed_memory_start;  
    // allocate and initialize our memory control block 
    // for the first (and at the moment only) free block
    m->size = MEM_SIZE - sizeof(struct mem_control_block);
    // no next free block
    m->next = (struct mem_control_block *)0;
    // initialize the start of the free list
    free_list_start = m;
    // We're initialized and ready to go
    has_initialized = 1;
}

// Memory allocation function implementing first-fit allocation
void *mymalloc(long numbytes)
{
    // Where we are looking in memory
    struct mem_control_block *current;
    current = free_list_start;

    printf("Current: %p\n", current);
    // Memory we search for must inlcude memory_control_block
    printf("NUMBYTES raw: %ld\n", numbytes);
    printf("Metadata size: %ld\n", sizeof(struct mem_control_block));
    numbytes = numbytes + sizeof(struct mem_control_block);
    printf("NUMBYTES w/ metadata %ld\n", numbytes);
    void* result;

    // If unitilialized-->initialize!
  if (has_initialized == 0) 
  {
     printf("\n Initializing..\n \n");
     mymalloc_init();
  }
  else if((current->size) >= numbytes)
  {
      printf("-----------------Elseif condition was met-------------------\n");
      printf("Current->size: %d \n", current->size);

      // Begin searching at start of managed memory
      // Value of current is set to itself minus numbytes
      current->size -= (numbytes);
      printf("Size current: %d \n", current->size);
      
      while (1){
        if (current== NULL){
          printf("Shit vi gikk tom for minne :,)");
          break;
        }
        //Checking if there is room in numbytes in current
        else if (numbytes <= current -> size) { 
          // da må man gjøre noe: allokere minne, 
        }
        // Not room for current, move to next MCB
        current = current -> next;
      }
      printf(" WE NEVER GET HERE (SEG FAULT) Size current: %d\n", current->size);
      current->size = numbytes;
      
      result = (void*)(++current);
      printf("Fitting block allocated\n");
      printf("Reached end of allocation logic\n");
      return result;
      
  }
    
}

int main()
{
    mymalloc(1);
    printf("\n");
    mymalloc(4);
    printf("\n");
    mymalloc(200);
    printf("\n");
    mymalloc(10);

    //printf("result\n");
}
/*

// b) Release memory block 
void myfree(void *firstbyte) 
{
  void *p;
  p = mymalloc(42); // allocate 42 bytes
  if (p != (void *)0) {
    // do something
    myfree(p); // release memory again
  } 
  else {
  printf("mymalloc failed!\n");
}

// c) Make tests for a and b :3
int main(int argc, char **argv) {

  // add your test cases here! 

}
*/