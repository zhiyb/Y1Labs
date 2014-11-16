/*
 list.c - source file
 for a toy list library to be used as an example in the
 ECS ELEC1201 module

 begin                : 01/12/2011.
 Copyright (C) 2011 by Enrico Costanza @ ECS, University of Southampton
 email                : e.costanza@ieee.org
*/

/*
 * This file is part of ELEC1201-examples.
 *
 * COMP1010-examples is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * COMP1010-examples is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ELEC1201-examples. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "list.h"

list_item * list_item_create(const char * word, const int freq)
{
    list_item * item = (list_item *) malloc(sizeof(list_item));

    /* check that allocation was succesful */
    if (item != NULL)
    {
        strcpy(item->word, word);
        item->freq = freq;
        item->next = NULL;
    }

    return item;
}

void list_item_print(const list_item * self)
{
    printf("%s %g\n", self->word, self->freq);
    return;
}

/* this function transfers ownership */
list * list_create()
{
    list * self = (list *) malloc(sizeof(list));
    if (self != NULL)
    {
		self->size = 0;
		self->first = NULL;
		self->current = NULL;
    }

    return self;
}

void list_destroy(list * self)
{
	list_empty(self);
	// assert size is zero
	free(self);
	return;
}

void list_empty(list * self){
	self->current = self->first;
	while (self->current != NULL) {
		list_remove_current(self);
	}
	return;
}

int list_remove_current(list * self)
{
	list_item * tmp = NULL;
	if (self->current == NULL)
	{
		return -1;
	}

	if (self->first == self->current) {
		self->first = self->current->next;
		free(self->current);
		self->current = self->first;
		self->size--;
		return 0;
	}

	tmp = self->current;
	list_find_item(self, tmp);
	self->current->next = tmp->next;
	free(tmp);

    self->size--;

    return 0;
}

/* this function takes ownership */
int list_insert_item( list * self, list_item * item )
{
    if (self->current == NULL)
    {
		/* insert at the beginning */
        item->next = self->first;
		self->first = item;
    }
    else
	{
		item->next = self->current->next;
		self->current->next = item;
	}

    self->size++;

    return 0;
}

int list_insert_sorted( list * self, const char * word, const int freq )
{
	/* is the word in the list? */
	int found;
	list_find_word(self, word, &found);

	if (found != 0)
	{
		/* insert the element */
		// create a new list item
		list_item * li = list_item_create(word, freq);

		if (li == NULL)
		{
			return -1;
		}

		list_insert_item( self, li );
		return 0;
    }
	else
	{
		return 1;
	}
}


list_item * list_find_item(list * self, list_item *target)
{
    self->current = self->first;
    if (self->current != NULL)
    {
        while (self->current->next != target)
        {
            self->current = self->current->next;
        }
    }
    return self->current;
}


list_item * list_find_word(list * self, const char * target, int * found)
{
	list_item * tmp = NULL;
	int cmp;

    *found = 1;
    self->current = self->first;
    if (self->current != NULL)
    {
		cmp = strcmp(self->current->word, target);
        while (cmp < 0 && self->current->next != NULL)
        {
            self->current = self->current->next;
			cmp = strcmp(self->current->word, target);
        }

        if (cmp == 0)
        {
            /* we found the target */
            *found = 0;
        }
		else {
			/* we passed the target */

			/* special case 1: the item is the first, and we have passed the target */
			if (self->current == self->first && cmp > 0) {
				self->current = NULL;
				return self->current;
			}

			/* special case 2: the item is the last and we have NOT passed the target */
			/* if we are at the end of the list */
			if (self->current->next == NULL && cmp < 0)
			{
				return self->current;
			}

			/* if we get here, it means we have passed the target,
			   so we need to step back */
			tmp = self->current;
			list_find_item(self, tmp);
		}
    }
    return self->current;
}

void list_print(const list * self)
{
    list_item * ptr = self->first;
	int counter = 0;

    while(ptr!=NULL)
    {
		printf("%3d ", counter);
        list_item_print(ptr);
		ptr = ptr->next;
		counter++;
    }
    printf("%d items\n\n", self->size);
    return;
}

int list_check(const list * self, const char expected[][32])
{
    list_item * ptr = self->first;
	int counter = 0;

    while(ptr!=NULL)
    {
		if (strcmp(ptr->word, expected[counter]) != 0) {
			printf("item %d, found: %s\n", counter, ptr->word);
			printf("expected: %s", expected[counter]);
			return -1;
		}
		assert(strcmp(ptr->word, expected[counter]) == 0);
		ptr = ptr->next;
		counter++;
    }
    /*printf("%d items\n", self->size);*/

    return 0;
}


int list_test(void)
{
	int result;
    list * l = list_create();

    list_insert_sorted(l, "alpha", 0);
    list_insert_sorted(l, "charlie", 0);
    list_insert_sorted(l, "bravo", 0);

	//list_print(l);
	const char test1[][32] = {"alpha", "bravo", "charlie"};

	result = list_check(l, test1);
	assert(result == 0);

	list_item * item = list_find_word(l, "brava", &result);
	assert(item == l->first);

	item = list_find_word(l, "aa", &result);
	assert(item == NULL);

	list_insert_sorted(l, "aa", 0);

	const char test2[][32] = {"aa", "alpha", "bravo", "charlie"};
	result = list_check(l, test2);
	assert(result == 0);

	item = list_find_word(l, "delta", &result);
	list_insert_sorted(l, "delta", 0);

	const char test3[][32] = {"aa", "alpha", "bravo", "charlie", "delta"};
	result = list_check(l, test3);
	assert(result == 0);

	item = list_find_word(l, "bravo", &result);
	list_remove_current(l);
	const char test4[][32] = {"aa", "alpha", "charlie", "delta"};
	result = list_check(l, test4);
	assert(result == 0);

	item = list_find_word(l, "brava", &result);
	list_insert_sorted(l, "brava", 0);

	const char test5[][32] = {"aa", "alpha", "brava", "charlie", "delta"};
	result = list_check(l, test5);
	assert(result == 0);

	list_empty(l);
	printf("list size: %d\n", l->size);
	assert(l->size == 0);

	free(l);

	printf("*** test passed ***\n\n");
	return 0;
}

//
