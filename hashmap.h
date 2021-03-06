#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef enum IS_ROOT_{
  ROOT,
  NOT_ROOT,
} IS_ROOT;

typedef enum W_ADD_{
  HEAD,
  TAIL,
} W_ADD;

typedef struct chain_t_ {
  IS_ROOT cond;
  union {
    long value; //use long instead of int because struct uses two 4 bytes (integer) fields
    struct {
      int max_cnt;
      int cur_cnt;
    };
  };

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
void InsertToHashmap(hashmap_t* hashmap, chain_t* elem);
chain_t* Find_num(hashmap_t* hashmap, int value);
chain_t* CreateChain(int max_length);
void AddToChain(chain_t* root ,chain_t* to_add , W_ADD place);
void RemoveChainElem(chain_t* root, chain_t* to_remove);
int LRU(int cache_length, int arr_length, int *arr);
chain_t* CreateChainElement(int value);