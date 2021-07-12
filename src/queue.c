#include <stdlib.h>
#include <stdio.h>

struct queue_t
{
		int array_size;
		int index;
		int16_t *array;
};


void insert(struct queue_t *queue, int16_t element)
{
		queue->array[queue->index] = element;

		queue->index = queue->index + 1;

		if (queue->index > queue->array_size - 1) {

				queue->index = 0;

		}

}

int16_t read_queue(struct queue_t *queue, int read_position)
{

		if (read_position >= queue->array_size) {

				printf("Invalid argument\n");
				abort();
		}
		else {

				if (read_position + queue->index >= queue->array_size) {

						return queue->array[(read_position + queue->index) - queue->array_size];

				}
				else {

						return queue->array[read_position + queue->index];

				}
		}

}
