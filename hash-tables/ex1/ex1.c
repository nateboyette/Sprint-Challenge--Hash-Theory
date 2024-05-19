#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "ex1.h"

Answer *get_indices_of_item_weights(int *weights, int length, int limit)
{

  // If there are less than two items in weights there can't be a matching pair
  if (length < 2)
  {
    return NULL;
  }

  // if the weights list only has two weights
  // check if they match the limit, if so return the answer
  if (length == 2)
  {

    if ((weights[0] + weights[1]) == limit)
    {
      Answer *answer = malloc(sizeof(Answer));

      if (weights[0] < weights[1] || weights[0] == weights[1])
      {
        answer->index_1 = 1;
        answer->index_2 = 0;
      }
      else if (weights[0] < weights[1])
      {
        answer->index_1 = 0;
        answer->index_2 = 1;
      }
      return answer;
    }
  }

  HashTable *ht = create_hash_table(16);

  /* YOUR CODE HERE */
  for (int i = 0; i < length; i++)
  {

    // not storing any weight over the limit
    if (weights[i] <= limit)
    {

      // storing the weight as the key and index in array as the value in the hash table;
      hash_table_insert(ht, weights[i], i);
    }

    // printf("Weight: %d\nWeight Index: %d\n", weights[i], i);
  }

  for (int i = 0; i < ht->capacity - 1; i++)
  {

    // Only checking indices with a value
    if (ht->storage[i] != NULL)
    {
      // printf("HASH INDEX: %d\n", i);

      // printf("Hash KEY/WEIGHT: %d\n", ht->storage[i]->key);

      // Since the weight is being stored as the key in the hash table
      // We need to find what keys will equal the limit
      // By subtracting the limit from the current key
      int weight_value = limit - ht->storage[i]->key;
      // printf("WEIGHT VALUE: %d\n", weight_value);

      // We then pass that key into hash table retrieve
      // Which will return the value of the key if it exists in the hash table
      // That value is the index of the weight in the weight array
      int weight_index = hash_table_retrieve(ht, weight_value);
      // printf("WEIGHT INDEX: %d\n", weight_index);
      // printf("LIMIT: %d\n", limit);
      // printf("*****\n\n");

      // if the key + the weight value equal the limit AND the weight exists
      // in the hash table, assign the values to the answer struct and return

      if ((ht->storage[i]->key + weight_value) == limit && weight_index != -1)
      {

        // printf("LIMIT = %d\n", limit);
        // printf("WEIGHT INDEX: %d\n", weight_index);
        // printf("HASH TABLE KEY:VALUE - %d:%d\n", ht->storage[i]->key, ht->storage[i]->value);
        Answer *answer = malloc(sizeof(Answer));

        if (ht->storage[i]->key < weights[weight_index])
        {
          answer->index_1 = weight_index;
          answer->index_2 = ht->storage[i]->value;
        }
        else if (ht->storage[i]->key > weights[weight_index])
        {
          answer->index_1 = ht->storage[i]->value;
          answer->index_2 = weight_index;
        }

        // printf("ANSWER INDEX_1: %d\n", answer->index_1);

        return answer;
      }
    }
  }

  // int test = hash_table_retrieve(ht, 0);

  return NULL;
}

void print_answer(Answer *answer)
{
  if (answer != NULL)
  {
    printf("%d %d\n", answer->index_1, answer->index_2);
  }
  else
  {
    printf("NULL\n");
  }
}

#ifndef TESTING
int main(void)
{
  // TEST 1
  int weights_1 = {9};
  Answer *answer_1 = get_indices_of_item_weights(&weights_1, 1, 9);
  print_answer(answer_1); // NULL

  // TEST 2
  int weights_2[] = {4, 4};
  Answer *answer_2 = get_indices_of_item_weights(weights_2, 2, 8);
  print_answer(answer_2); // {1, 0}

  // TEST 3
  int weights_3[] = {4, 6, 10, 15, 16};
  Answer *answer_3 = get_indices_of_item_weights(weights_3, 5, 21);
  print_answer(answer_3); // {3, 1}

  // TEST 4
  int weights_4[] = {12, 6, 7, 14, 19, 3, 0, 25, 40};
  Answer *answer_4 = get_indices_of_item_weights(weights_4, 9, 7);
  print_answer(answer_4); // {6, 2}

  return 0;
}

#endif
