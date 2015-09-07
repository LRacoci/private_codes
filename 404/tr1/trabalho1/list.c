#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "list.h"

void list_new(list *list, int elementSize, freeFunction freeFn) {
    assert(elementSize > 0);
    list->logicalLength = 0;
    list->elementSize = elementSize;
    list->head = list->tail = NULL;
    list->freeFn = freeFn;
}

void list_destroy(list *list) {
    listNode *current;
    while(list->head != NULL) {
        current = list->head;
        list->head = current->next;

        if(list->freeFn) {
            list->freeFn(current->data);
        }

        free(current->data);
        free(current);
    }
}

void list_prepend(list *list, void *element) {
    listNode *node = malloc(sizeof(listNode));
    node->data = malloc(list->elementSize);
    memcpy(node->data, element, list->elementSize);

    node->next = list->head;
    list->head = node;

    /* first node? */
    if(!list->tail) {
        list->tail = list->head;
    }

    list->logicalLength++;
}

void list_append(list *list, void *element) {
    listNode *node = malloc(sizeof(listNode));
    node->data = malloc(list->elementSize);
    node->next = NULL;

    memcpy(node->data, element, list->elementSize);

    if(list->logicalLength == 0) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->logicalLength++;
}

void list_for_each(list *list, listIterator iterator) {
    listNode *node;
    bool result;
    assert(iterator != NULL);

    node = list->head;
    result = TRUE;
    while(node != NULL && result) {
        result = iterator(node->data);
        node = node->next;
    }
}

void list_head(list *list, void *element, bool removeFromList) {
    listNode *node = list->head;
    assert(list->head != NULL);


    memcpy(element, node->data, list->elementSize);

    if(removeFromList) {
        list->head = node->next;
        list->logicalLength--;

        free(node->data);
        free(node);
    }
}

void list_tail(list *list, void *element) {
    listNode *node;
    assert(list->tail != NULL);
    node = list->tail;
    memcpy(element, node->data, list->elementSize);
}

int list_size(list *list) {
    return list->logicalLength;
}





size_t __List_size(Info i){
    return size_list((List)i);
}
void __List_print(Data d){
    print_list(d->info);
}
void __List_free(Info i){
    free_list(i);
}
Info __List_copy(Info i){
    return copy_list(i);
}
Hash __List_hash(Info i){
    return hash_list(i);
}
