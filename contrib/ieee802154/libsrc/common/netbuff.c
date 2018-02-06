#include "common/netbuff.h"
#include "common/sralloc.h"

/* Init the buffer structures */
void netbuff_init(struct netbuff *netb, EE_UINT8 nbuffs, EE_UINT16 buffdim)
{
	int i;
	
	SRAMInitHeap();
	//kern_cli();
	netb->b = (EE_UINT8 *)SRAMalloc(nbuffs * buffdim);
	netb->pb = (EE_UINT8 **)SRAMalloc(nbuffs * sizeof(void *));
	netb->free = (EE_UINT8 *)SRAMalloc(nbuffs * sizeof(char));
	//kern_sti();
	if ((netb->b == 0) || (netb->pb ==0) || (netb->free == 0)) {
		//kern_raise(XNETBUFF_INIT_EXC,exec_shadow);
		return;
	}
	netb->nbuffs = nbuffs;
	for (i = 0; i < nbuffs; i++) {
		netb->pb[i] = netb->b + (i * buffdim);
		netb->free[i] = 1;
	}
	
	//sem_init(&(netb->buffersem), 0, nbuffs);
}

/*
   Get the first free buffer in the netb pool. All the tasks can call this
   function, so a kern_cli is needed
*/
void *netbuff_get(struct netbuff *netb, EE_UINT8 to)
{
	int i, done;
	//static int mycount = 0;

	/*if (sem_xwait(&(netb->buffersem), 1, to) != 0) {
		return NULL;
	} else {
		mycount++;
	}*/

	done = 0; i = 0;
	//kern_cli();
	while ((i < netb->nbuffs) && !done) {
		if (netb->free[i]) {
			done = 1;
			netb->free[i] = 0;
		} else i++;
	}
	//kern_sti();
	if (!done) {
		//kern_raise(XNETBUFF_GET_EXC,exec_shadow);
		return;
	}
	return netb->pb[i];
}

/*
   Get the first free buffer in the netb pool. This function can be called
   only if netb is private of the process that wants to get the buffer, so
   kern_cli is not needed
*/
void *netbuff_sequentialget(struct netbuff *netb, EE_UINT8 to)
{
	int i, done;

	/*if (!sem_xwait(&(netb->buffersem), 1, to)) {
		return NULL;
	}*/

	done = 0; i = 0;
	while ((i < netb->nbuffs) && !done) {
		if (netb->free[i]) {
			done = 1;
			netb->free[i] = 0;
		} else i++;
	}
	/*if (!done) {
		kern_raise(XNETBUFF_GET_EXC,exec_shadow);
	}*/
	return netb->pb[i];
}

/* Release the buffer m of the pool netb */
void netbuff_release(struct netbuff *netb, void *m)
{
	int i, done;

	done = 0; i = 0;
	while ((i < netb->nbuffs) && !done) {
		if (netb->pb[i] == m) {
			if (netb->free[i] == 1) {
				//cprintf("Trying to free a free buffer :( \n");
				//kern_raise(XNETBUFF_ALREADYFREE_EXC,exec_shadow);
				return;
			}
			done = 1;
			netb->free[i] = 1;
		} else i++;
	}
	if (!done) {
		//cprintf("Trying to free a STRANGE buffer :( \n");
		//kern_raise(XNETBUFF_RELEASE_EXC,exec_shadow);
		return;
	}
	//sem_post(&(netb->buffersem));
}
