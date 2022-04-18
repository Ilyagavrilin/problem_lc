#include "hashmap.h"

hashmap_t *CreateHashmap(int table_size){
  assert(table_size >= 0);

  hashmap_t *res;
  res = (hashmap_t *)malloc(sizeof(hashmap_t));
  assert(res != NULL);

  res->table_size = table_size;
  res->arr = (list_t **)malloc(table_size * sizeof(list_t *));
  assert(res->arr != NULL);
  for (int i = 0; i < table_size; i++){
    res->arr[i] = NULL;
  }

  return res;
}

int DeleteHashmap(hashmap_t *hashmap){
  assert(hashmap != NULL);
  int cleaned = 0;

  if (hashmap->arr != NULL){
    for (int i = 0; i < hashmap->table_size; i++){
      if (hashmap->arr[i] != NULL){
        DeleteList(hashmap->arr[i]);
        cleaned++;
      }
    }
  }
  else{
    return -1;
  }

  return cleaned;
}

static void DeleteList(list_t *list){

  while (list->next != NULL){
    DeleteList(list->next);
  }

  free(list);
}

chain_t* Find_num(hashmap_t* hashmap, int value) {
  int hash = HashmapCounter(value, hashmap->table_size);
  list_t* curr = hashmap->arr[hash];
  while (curr != NULL) {
    if (compare_elems(curr->value, value)) {
      return curr->value;
    }else {
      curr = curr->next;
    }
  }
  return NULL;
}

int compare_elems(chain_t* list_el, int val) {
  return (list_el->value == val)? 1:0;
}

void InsertToHashmap(hashmap_t* hashmap, chain_t* elem) {
  assert(hashmap != NULL);
  int hash = HashmapCounter(elem->value, hashmap->table_size);
  list_t* res;
  res = (list_t*) malloc(sizeof(list_t));
  assert(res != NULL);
  res->value = elem;
  res->next = NULL;

  list_t* insertion_point = hashmap->arr[hash];
  if (insertion_point == NULL) {
    hashmap->arr[hash] = res;
  }
  else {
    while (insertion_point->next != NULL) {
      insertion_point = insertion_point->next;
    }
    insertion_point->next = res;
  }
}

//-------------------------
// Hash counting functions


int HashmapCounter(int num, int table_size){
  return ((A * num + B) % P) % table_size;
}

