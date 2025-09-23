/*
* In this algorithm, we consider the head as a pointer on a regular node. Not just its next pointer.
 * So that's why we use **head in some functions to be able to modify it.
 * Otherwise, all the rest is pretty much the same as in Ex3.c, except the logic of creating, adding and removing nodes.
 * Also we found the use of Do while loops more relevant than for and while loops in this case.
 */

#define N 5
#define STARTING_VALUE 0
#define INCREMENT 1

#define BLOC_DIVIDER "----------------------------------------\n"
#define LIST_SIZE_STRING "Size of the list: "
#define Q1 "1. Créez une liste chaînée contenant les n premiers entiers dans l’ordre croissant. "
#define Q2 "2. Créez une fonction qui renvoie la longueur d’une liste."
#define Q3 "3. Créez une fonction qui affiche chaque élémet de votre liste sous la forme : <adresse du maillon> valeur du maillon."
#define Q4 "4. Retirez le premier élément d’une liste."
#define Q5 "5. Retirez le dernier élément d’une liste."
#define Q6 "6. Ajoutez un élément à la fin d’une liste."
#define Q7 "7. Ajoutez un élément au début d’une liste."
#define Q8 "8. Écrivez une fonction qui concatène deux listes."
#define Q9 "9. Écrivez une fonction qui retourne une nouvelle liste, après application d’une fonction à chaque élément (par exemple : élévation au carré)."
#define Q10 "10. Transformez votre liste en une liste doublement chaînée: On a fait une fonctoin qui affiche l'inverse de la liste avec les pionteurs previous."

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

int *NULL_POINTER = NULL;


int square(int x) {
    return x * x;
}

struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = newNode->prev = newNode;
    return newNode;
}

void insert(struct Node **head, int data) {
    struct Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node *last = (*head)->prev;
        last->next = newNode;
        newNode->prev = last;
        newNode->next = *head;
        (*head)->prev = newNode;
    }
}

void fillOrderedLinkedList(struct Node **head) {
    for (int i = STARTING_VALUE; i < N; i += INCREMENT) {
        insert(head, i);
    }
}

void showList(struct Node *head, char* name) {
    printf("%s%s\n", BLOC_DIVIDER, name);
    struct Node *current = head;
    do {
        printf("<%p> -> %d\n", current, current->data);
        current = current->next;
    } while (current != head);
    printf("%s\n",BLOC_DIVIDER);
}

int getListSize(struct Node *head) {
    if (!head) return 0;
    int size = 0;
    struct Node *current = head;
    do {
        size += 1;
        current = current->next;
    } while (current != head);
    return size;
}

int popFirstNode(struct Node **head) {
    if (!*head) return *NULL_POINTER;
    struct Node *firstNode = *head;
    int data = firstNode->data;
    if (firstNode->next == firstNode) {
        free(firstNode);
        *head = NULL;
    } else {
        struct Node *last = firstNode->prev;
        *head = firstNode->next;
        last->next = *head;
        (*head)->prev = last;
        free(firstNode);
    }
    return data;
}

int popLastNode(struct Node **head) {
    if (!*head) return *NULL_POINTER;
    struct Node *lastNode = (*head)->prev;
    int data = lastNode->data;
    if (lastNode == *head) {
        free(lastNode);
        *head = NULL;
    } else {
        struct Node *beforeLast = lastNode->prev;
        beforeLast->next = *head;
        (*head)->prev = beforeLast;
        free(lastNode);
    }
    return data;
}

void appendNodeInTheEnd(struct Node **head, struct Node *node) {
    if (!*head) {
        node->next = node->prev = node;
        *head = node;
    } else {
        struct Node *lastNode = (*head)->prev;
        lastNode->next = node;
        node->prev = lastNode;
        node->next = *head;
        (*head)->prev = node;
    }
}

void appendNodeIntheStart(struct Node **head, struct Node *node) {
    appendNodeInTheEnd(head, node);
    *head = node;
}
/*
void concatenateTwoLists(struct Node *head1, struct Node *head2) {
    if (head1->next == NULL) {
        head1->next = head2->next;
        if (head2->next != NULL)
            head2->next->prev = head1;
    } else {
        struct Node *lastNode = getLastNode(head1);
        lastNode->next = head2->next;
        if (head2->next != NULL)
            head2->next->prev = lastNode;
    }
    head2->next = NULL;
}

struct Node* duplicateList(struct Node *head) {
    struct Node *newHead = (struct Node *) malloc(sizeof(struct Node));
    newHead->next = NULL;
    newHead->prev = NULL;
    struct Node *current;
    for (current = head->next; current != NULL; current = current->next) {
        struct Node *newNode = createNode(current->data);
        appendNodeInTheEnd(newHead, newNode);
    }
    return newHead;
}

void applyFunctionToList(struct Node *head, int (*func)(int)) {
    struct Node *current;
    for (current = head->next; current != NULL; current = current->next) {
        current->data = func(current->data);
    }
}

struct Node* createSpecialList(struct Node *head, int(*func)(int)) {
    struct Node* newHead= duplicateList(head);
    applyFunctionToList(newHead, func);
    return newHead;
}

void showInvertedList(struct Node *head, char* name) {
    printf("%s%s\n", BLOC_DIVIDER, name);
    struct Node *lastNode = getLastNode(head);
    struct Node *current = lastNode;
    while (current != head) {
        printf("<%p> -> %d\n", current,current->data);
        current = current->prev;
    }
    printf("%s\n",BLOC_DIVIDER);
}
*/

void main() {
    struct Node *head1 = NULL;

    fillOrderedLinkedList(&head1);
    showList(head1, Q1);

    printf("%s\n%s %d\n\n",Q2,LIST_SIZE_STRING, getListSize(head1));

    showList(head1, Q3);

    popFirstNode(&head1);
    showList(head1, Q4);

    popLastNode(&head1);
    showList(head1, Q5);

    struct Node *newNode = createNode(99);
    appendNodeInTheEnd(&head1, newNode);
    showList(head1, Q6);

    struct Node *newNode2 = createNode(100);
    appendNodeIntheStart(&head1, newNode2);
    showList(head1, Q7);

    // struct Node *head2 = createSpecialList(head1,square);
    // showList(head2, Q9);
    //
    // concatenateTwoLists(head1, head2);
    // showList(head1, Q8);
    //
    // showInvertedList(head1, Q10);
}
