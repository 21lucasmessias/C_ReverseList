#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList LinkedList;   

struct LinkedList {
  char value;
  LinkedList *next;
};

int lenList(LinkedList *list){
  int i = 0;

  while(list != NULL){
    i++;

    list = list->next;
  }

  return i;
}

int addList(LinkedList **list, char value) {
  if(*list == NULL) {
    LinkedList *newPosition = NULL;
    
    newPosition = (LinkedList *)malloc(sizeof(LinkedList));
    
    if(newPosition == NULL) {
      return 0;
    }

    newPosition->value = value;
    newPosition->next = NULL;
    *list = newPosition;

    return 1;
  }

  return addList(&((*list)->next), value);
}

int _freeList(LinkedList **list){
  if(*list == NULL){
    return 1;
  }

  _freeList(&(*list)->next);

  free(*list);

  *list = NULL;

  return 1;
}

int freeList(LinkedList **list) {
  if(*list == NULL){
    printf("Lista Vazia\n");
    return 0;
  }
  
  return _freeList(list);
}

void printList(LinkedList *list) {
  int len = lenList(list);

  for(int i = 0 ; i < len ; i++) {
    printf("%c ", list->value);

    list = list->next;
  }
}

LinkedList * _reverseLinkedList(LinkedList **list){
  if((*list)->next == NULL){
    return *list; //retorna endereço do ultimo
  }

  LinkedList * newHead = NULL;

  newHead =  _reverseLinkedList(&(*list)->next);

  (*list)->next->next = *list;

  return newHead;
}

int reverseLinkedList(LinkedList **list){
  if(*list == NULL){
    return 0;
  }

  LinkedList *newLast = *list;
  *list = _reverseLinkedList(list);
  newLast->next = NULL;

  return 1;
}

void main() {
  LinkedList *list = NULL;

  addList(&list, 'a');
  addList(&list, 'b');
  addList(&list, 'c');
  addList(&list, 'd');
  addList(&list, 'e');
  addList(&list, 'f');

  printf("Input List: ");
  printList(list);

  reverseLinkedList(&list);

  printf("\nOut List: ");
  printList(list);

  freeList(&list);
}