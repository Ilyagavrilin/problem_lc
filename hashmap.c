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

int LRU(int cash_num, int *arr);

chain_t* CreateChain(int max_length) {
  chain_t* res;
  res = (chain_t*) malloc(sizeof(chain_t));
  assert(res != NULL);

  res->cond = ROOT;
  res->max_cnt = max_length;
  res->cur_cnt = 0;
  res->next = NULL;
  res->prev = NULL;

  return res;
}

void AddToChain(chain_t* root ,chain_t* to_add , W_ADD place) {
  chain_t* tmp;
  assert(root->cond == ROOT);

  if (root->cur_cnt == 0) {
    root->next = to_add;
    root->prev = to_add;
    root->cur_cnt++;
    assert(root->cur_cnt < root->max_cnt);
  } else {
    switch (place) {
      case HEAD:
        tmp = root->next;
        root->next = to_add;
        to_add->prev = root;
        to_add->next = tmp;
        break;
      case TAIL:
        tmp = root->prev;
        root->prev = to_add;
        to_add->prev = tmp;
        to_add->next = root;
        break;
      default:
        assert("Undefined data value" == 0);
    }
  }
}

void RemoveChainElem(chain_t* root, chain_t* to_remove) {
  assert(root != NULL && to_remove != NULL);
  assert(root->cond == ROOT);
  assert(root->cur_cnt > 0);

  if ((root->cur_cnt == 1) && (root->next == root->prev) && (root->next == to_remove)) {
    free(to_remove);
    root->next = NULL;
    root->prev = NULL;
    root->cur_cnt--;
  } else {
    chain_t* prev_tmp, *next_tmp;
    prev_tmp = to_remove->prev;
    next_tmp = to_remove->next;
    next_tmp->prev = prev_tmp;
    prev_tmp->next = next_tmp;
    free(to_remove);
  }
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

