/*****************************************************************************
 *
 *              Simple SRAM Dynamic Memory Allocation
 *
 *****************************************************************************
 * FileName:        sralloc_dsPIC33.c
 * Dependencies:
 * Processor:       dsPIC33F
 * Complier:        C30 v2.05 or higher
 *
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * Author               Date    Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 ********************************************************************/

#include <stdlib.h>


/*********************************************************************
 * Function:        unsigned char * SRAMalloc(unsigned char length)
 *
 * PreCondition:    A memory block must be allocated in the linker,
 *                  and the memory headers and tail must already be
 *                  set via the function SRAMInitHeap().
 *
 * Input:           unsigned char nBytes - Number of bytes to allocate.
 *
 * Output:          unsigned char * - A pointer to the requested block
 *                  of memory.
 *
 * Side Effects:
 *
 * Overview:        This functions allocates a chunk of memory from
 *                  the heap. The maximum segment size for this
 *                  version is 126 bytes. If the heap does not have
 *                  an available segment of sufficient size it will
 *                  attempt to create a segment; otherwise a NULL
 *                  pointer is returned. If allocation is succeessful
 *                  then a pointer to the requested block is returned.
 *
 * Note:            The calling function must maintain the pointer
 *                  to correctly free memory at runtime.
 ********************************************************************/
//unsigned char * SRAMalloc(unsigned char nBytes);
//#define  SRAMalloc(nBytes)   (unsigned char)(malloc(nBytes))
#define  SRAMalloc(nBytes)   malloc(nBytes)

/*********************************************************************
 * Function:        void SRAMfree(unsigned char * pSRAM)
 *
 * PreCondition:    The pointer must have been returned from a
 *                  previously allocation via SRAMalloc().
 *
 * Input:           unsigned char * pSRAM - pointer to the allocated
 *
 * Output:          void
 *
 * Side Effects:
 *
 * Overview:        This function de-allocates a previously allocated
 *                  segment of memory.
 *
 * Note:            The pointer must be a valid pointer returned from
 *                  SRAMalloc(); otherwise, the segment may not be
 *                  successfully de-allocated, and the heap may be
 *                  corrupted.
 ********************************************************************/
//void SRAMfree(unsigned char * pSRAM);
#define SRAMfree(pSRAM) free(pSRAM)
/*#define free(p) {                                   \
                    SRAMfree( (unsigned char *)p ); \
                    p = NULL;                       \
                }
*/

