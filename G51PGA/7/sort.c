#include <stdlib.h>
#include "sort.h"
#include "list.h"

struct list *divide(struct list *x)
{
  struct list *y      = NULL;
  struct list *curr   = NULL;

  if( x == NULL )
    return y;
  else {
    y       = x->next;
    curr    = x->next;
    x->next = NULL;
  }
  
  while( curr != NULL && curr->next != NULL ) {
    x->next    = curr->next;
    curr->next = curr->next->next;
    x          = x->next;
    x->next    = NULL;
    curr       = curr->next;
  }

  return y;
}


struct list *merge(struct list *x, struct list *y, int (*comp)(void *a, void *b))
{

  struct list *tmp  = NULL;
  struct list *head = NULL;
  struct list *curr = NULL;
  
  if( x == NULL )
    head = y;

  else if( y == NULL )
    head = x;

  else {
   
    while( x != NULL && y != NULL ) {

      // Swap x and y if x is not largest.
      if( comp(y->val, x->val) ) {
	tmp = y;
	y   = x;
	x   = tmp;
      }
      
      if( head == NULL ) { // First element?
	head = x;
	curr = x;
      } else {
	curr->next = x;
	curr = curr->next;
      }
      x = x->next;
    }

    // Either x or y is empty.
    if( x != NULL )
      curr->next = x;

    else if( y != NULL )
      curr->next = y;
      
  }

  return head;
}

struct list *sort(struct list *x, int (*comp)(void *a, void *b))
{
  struct list *y = NULL;
  if ( x == NULL || x->next == NULL )
    return x;

  y = divide(x);
  return merge( sort(x, comp),
		sort(y, comp),
		comp );
}
