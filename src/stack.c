#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

// Функция для создания нового элемента
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Функция для инициализации стека
void initStack(Stack* stack) {
    stack->top = NULL;
}

void destroyStack(Stack* stack) {
    Node* current = stack->top;
    while (current != NULL) {
        Node *tmp = current;
        current = current->next;
        free(tmp);
    }
}

void push(Stack* stack, int data) {
    Node* newNode = createNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
}

bool pop(Stack* stack) {
    if (stack->top == NULL) {
        return false;
    }
    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return true;
}

const Node* searchByValue(const Stack* stack, int value) {
    Node* current = stack->top;
    while (current != NULL) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

const Node* searchByIndex(const Stack* stack, int index) {
    if (index < 0) {
        return NULL;
    }

    Node* current = stack->top;
    int count = 0;
    while (current != NULL) {
        if (count == index) {
            return current;
        }
        count++;
        current = current->next;
    }
    return NULL;
}

const Node* getTop(const Stack* stack) {
    return stack->top;
}

void traverseStack(const Stack* stack) {
    Node* current = stack->top;
    printf("Stack elements: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

bool isEmpty(const Stack* stack) {
    return stack->top == NULL;
}
