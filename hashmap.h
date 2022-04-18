#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>



typedef struct chain_t_ {
  int value;
  struct chain_t_* next;
  struct chain_t_* prev;
} chain_t;

typedef struct list_t_ {
  chain_t* value;
  struct list_t_* next;
} list_t;

typedef struct {
  list_t** arr;
  int table_size;
} hashmap_t;

enum HASH_CONSTS {
  A = 0xB1BA,
  B = 0x0A0A0A,
  P = 0xFFBB,
};
//-------------------------------------------

hashmap_t* CreateHashmap(int table_size);
int DeleteHashmap(hashmap_t* hashmap);
static void DeleteList(list_t* list);
int HashmapCounter(int num, int table_size);
int compare_elems(chain_t* list_el, int val);
void InsertToHashmap(hashmap_t* hashmap, hash_t word);
