#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

/* 

===============
===============

*/

char **reconstruct_trip(Ticket **tickets, int length)
{
  HashTable *ht = create_hash_table(length);
  char **route = malloc(length * sizeof(char *));

  /* YOUR CODE HERE */

  // Create hash table out of tickets
  for (int i = 0; i < length; i++)
  {

    hash_table_insert(ht, tickets[i]->source, tickets[i]->destination);
  }

  // Need to keep track of which ticket we're on
  // in order to find the next destination
  // Start from the first ticket with source NONE
  int current = 0;
  char *current_ticket = hash_table_retrieve(ht, "NONE");

  // Loop through the the ht changing the current ticket whenever
  // as long as destination is found
  // add each destination to the route array
  while (strcmp(current_ticket, "NONE") != 0)
  {
    route[current] = current_ticket;
    current++;
    current_ticket = hash_table_retrieve(ht, current_ticket);
  }

  // once we reach the end, add NONE as the final destination in the array
  route[current] = "NONE";

  destroy_hash_table(ht);

  return route;
}

void print_route(char **route, int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("%s\n", route[i]);
  }
}

#ifndef TESTING
int main(void)
{
  // Short test
  Ticket **tickets = malloc(3 * sizeof(Ticket *));

  Ticket *ticket_1 = malloc(sizeof(Ticket));
  ticket_1->source = "NONE";
  ticket_1->destination = "PDX";
  tickets[0] = ticket_1;

  Ticket *ticket_2 = malloc(sizeof(Ticket));
  ticket_2->source = "PDX";
  ticket_2->destination = "DCA";
  tickets[1] = ticket_2;

  Ticket *ticket_3 = malloc(sizeof(Ticket));
  ticket_3->source = "DCA";
  ticket_3->destination = "NONE";
  tickets[2] = ticket_3;

  print_route(reconstruct_trip(tickets, 3), 3); // PDX, DCA, NONE

  // reconstruct_trip(tickets, 3);

  for (int i = 0; i < 3; i++)
  {
    free(tickets[i]);
  }

  free(tickets);

  return 0;
}
#endif
