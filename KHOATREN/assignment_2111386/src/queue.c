#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
	if (q == NULL) return 1;
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
	/* TODO: put a new process to queue [q] */	
	if (!q || !proc) return;
	if (q -> size == MAX_QUEUE_SIZE) return;
	
	q -> proc[q -> size] = proc;
	q -> size ++;	
}

struct pcb_t * dequeue(struct queue_t * q) {
	/* TODO: return a pcb whose priority is the highest
	 * in the queue [q] and remember to remove it from q
	 * */
	 
	// if the queue is empty
	if (empty(q)) return NULL;
	
	// Remove and return the process at the front of the queue
	struct pcb_t* proc_del = NULL;
	
	proc_del = q -> proc[0];
	for (int i = 0; i < (q -> size - 1); i++){
	  q -> proc[i] = q -> proc[i + 1];
	}
	q -> size --;

	return proc_del;
}
