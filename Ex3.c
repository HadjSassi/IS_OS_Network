#define N 5

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int *NULL_POINTER = NULL;


int square(int x) {
    return x * x;
}

struct Node* createNode(int data) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insert(int data, struct Node *node, struct Node *head) {
    struct Node *newNode = createNode(data);
    if (head->next == NULL) {
        head->next = newNode;
    } else
        node->next = newNode;
}

struct Node *getLastNode(struct Node *head) {
    struct Node *current = head;
    while (current->next != NULL)
        current = current->next;
    return current;
}

void fillOrderedLinkedList(struct Node *head) {
    for (int i = 0; i < N; i += 1) {
        struct Node *lastNode = getLastNode(head);
        insert(i + 1, lastNode, head);
    }
}

void showList(struct Node *head) {
    struct Node *current = head->next;
    while (current != NULL) {
        printf("<%p> valeur: %d\n", current,current->data);
        current = current->next;
    }
    printf("\n");
}

int getListSize(struct Node *head) {
    int size = 0;
    struct Node *current = head->next;
    while (current != NULL) {
        size += 1;
        current = current->next;
    }
    return size;
}

int popFirstNode(struct Node *head) {
    if (head->next == NULL) {
        return *NULL_POINTER;
    }
    struct Node *firstNode = head->next;
    int data = firstNode->data;
    head->next = head->next->next;
    free(firstNode);
    return data;
}

int popLastNode(struct Node *head) {
    if (head->next == NULL) {
        return *NULL_POINTER;
    }
    struct Node *current = head;
    while (current->next->next != NULL)
        current = current->next;
    struct Node *lastNode = current->next;
    int data = lastNode->data;
    current->next = NULL;
    free(lastNode);
    return data;
}

void appendNodeInTheEnd(struct Node *head, struct Node *node) {
    if (head->next == NULL) {
        head->next = node;
    } else {
        struct Node *lastNode = getLastNode(head);
        lastNode->next = node;
    }
}

void appendNodeIntheStart(struct Node *head, struct Node *node) {
    node->next = head->next;
    head->next = node;
}

void concatenateTwoLists(struct Node *head1, struct Node *head2) {
    if (head1->next == NULL) {
        head1->next = head2->next;
    } else {
        struct Node *lastNode = getLastNode(head1);
        lastNode->next = head2->next;
    }
    head2->next = NULL;
}

struct Node* duplicateList(struct Node *head) {
    struct Node *newHead = (struct Node *) malloc(sizeof(struct Node));
    newHead->next = NULL;
    struct Node *current = head->next;
    while (current != NULL) {
        struct Node *newNode = createNode(current->data);
        appendNodeInTheEnd(newHead, newNode);
        current = current->next;
    }
    return newHead;
}

void applyFunctionToList(struct Node *head, int (*func)(int)) {
    struct Node *current = head->next;
    while (current != NULL) {
        current->data = func(current->data);
        current = current->next;
    }
}

struct Node* createSpecialList(struct Node *head, int(*func)(int)) {
    struct Node* newHead= duplicateList(head);
    applyFunctionToList(newHead, func);
    return newHead;
}

void main() {
    struct Node *head1 = NULL;
    head1 = (struct Node *) malloc(sizeof(struct Node));
    fillOrderedLinkedList(head1);
    popFirstNode(head1);
    popLastNode(head1);
    struct Node *newNode = createNode(99);
    appendNodeInTheEnd(head1, newNode);
    struct Node *newNode2 = createNode(100);
    appendNodeIntheStart(head1, newNode2);
    struct Node *head2 = createSpecialList(head1,square);
    concatenateTwoLists(head1, head2);
    printf("Size of the list: %d\n", getListSize(head1));
    showList(head1);
}
