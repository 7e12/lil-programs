/**
 * @author:  7e12
 * @file:    linked_list_queue.c
 * @date:    19 Jul 2021
 * @version: v1.0.0
 * @brief:   Linked-list queue
**/

#include "linked_list_queue.h"

// Create empty linked list queue
LLQueueTypeDef* createLLQueue(void) {
    LLQueueTypeDef *queue = (LLQueueTypeDef*) malloc(sizeof(LLQueueTypeDef));
    queue->front = queue->rear = NULL;
    return queue;
}

// Check linked list queue is empty or not (empty when rear node is NULL)
int isEmpty(LLQueueTypeDef *queue) {
    return (NULL == queue->rear);
}

// Add data to linked list queue
void enQueue(LLQueueTypeDef *queue, LLQueueDataTypeDef *input) {
    // Create new linked list queue node data
    LLQueueDataTypeDef *data = (LLQueueDataTypeDef*) malloc(sizeof(LLQueueDataTypeDef));
    memcpy(data, input, sizeof(LLQueueDataTypeDef));

    // Create new linked list queue node
    LLQueueNodeTypeDef *node = (LLQueueNodeTypeDef*) malloc(sizeof(LLQueueNodeTypeDef));
    node->data = data;
    node->next = NULL;

    // If linked list queue is empty, then new node is both front and rear
    if (NULL == queue->rear) {
        queue->front = queue->rear = node;
        return;
    }

    // Add new linked list queue node at the end of linked list queue and change rear node
    queue->rear->next = node;
    queue->rear = node;
}

// Remove data from linked list queue
void deQueue(LLQueueTypeDef *queue) {
    // If linked list queue is empty, return NULL
    if (NULL == queue->front) return;

    // Store previous front node and move front node one step ahead
    LLQueueNodeTypeDef* temp = queue->front;
    queue->front = queue->front->next;

    // If front node becomes NULL, then change rear node as NULL also
    if (queue->front == NULL) queue->rear = NULL;

    free(temp->data);
    free(temp);
}

// For testing, delete for using
int main(int argc, char const *argv[]) {
    // Create empty linked list queue
    LLQueueTypeDef *queue = createLLQueue();

    if (isEmpty(queue)) {
        printf("Linked list queue is empty\n\n");
    }

    // Create linked list queue data
    LLQueueDataTypeDef data = {
        .number = 1,
        .string = "Aa1",
    };
    enQueue(queue, &data);

    data.number = 2;
    sprintf(data.string, "Bb2");
    enQueue(queue, &data);

    data.number = 3;
    sprintf(data.string, "Cc3");
    enQueue(queue, &data);

    deQueue(queue);
    // deQueue(queue);

    // Print front and rear data
    printf("Linked list queue front data:\n");
    printf("Number: %d\n", queue->front->data->number);
    printf("String: %s\n", queue->front->data->string);
    printf("Linked list queue rear data:\n");
    printf("Number: %d\n", queue->rear->data->number);
    printf("String: %s\n", queue->rear->data->string);

    return 0;
}
