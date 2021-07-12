#include <stdlib.h>
#include <stdio.h>

#include "queue.c"

struct queue_t;
void insert(struct queue_t * queue, int16_t element);
int16_t read_queue(struct queue_t *queue, int read_position);

