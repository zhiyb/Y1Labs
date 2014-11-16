/*
 list.h - header file
 for a toy list library to be used as an example in the
 ECS ELEC1201 module
                             -------------------
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


#ifndef __EC_LIST
#define __EC_LIST


typedef struct list_item_struct
{
    char word[32];
    int freq;
    struct list_item_struct * next;
} list_item;


typedef struct list_struct
{
    int size;
    list_item * first;
    list_item * current;
} list;


list_item * list_item_create(const char * word, const int freq);
void list_item_print(const list_item * self);

list * list_create();
void list_destroy(list * self);
void list_empty(list * self);
int list_remove_current(list * self);

list_item * list_find_last(list * self);
list_item * list_find_item(list * self, list_item *target);
list_item * list_find_word(list * self, const char * target, int * found);

int list_insert_item(list * self, list_item * item);
int list_insert_sorted(list * self, const char * word, const int freq);

int list_remove_word(list * self, const char * word);

void list_print(const list * self);
int list_check(const list * self, const char expected[][32]);
int list_test(void);

//

#endif //ndef __EC_LIST
