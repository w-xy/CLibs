#ifndef _CLIST_H
#define _CLIST_H

#include "ctype.h"
#include <stdio.h>

typedef struct clist_head
{
    struct clist_head *next, *prev;
} clist_head;


static inline void clist_init(clist_head *list)
{
    list->next = list;
    list->prev = list;
}

static inline void _clist_add(clist_head *new, clist_head *prev, clist_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline bool clist_isempty(const clist_head *head)
{
    return head->next == head;
}

static inline void clist_add(clist_head *new, clist_head *head)
{
    _clist_add(new, head, head->next);
}

static inline void clist_add_tail(clist_head *new, clist_head *head)
{
    _clist_add(new, head->prev, head);
}

static inline void _clist_del(clist_head *prev, clist_head *next)
{
    next->prev = prev;
    prev->next = next;
}

static inline void clist_del(clist_head *entry)
{
    _clist_del(entry->prev, entry->next);
}

static inline void clist_erase(clist_head *entry)
{
    _clist_del(entry->prev, entry->next);
    entry->next = NULL;
    entry->prev = NULL;
}

static inline void clist_repalce(clist_head *old, clist_head *new)
{
    new->next = old->next;
    new->next->prev = new;
    new->prev = old->prev;
    new->prev->next = new;
}

#define CLIST_ENTRY(head, type, member) \
    container_of(head, type, member)

#define CLIST_NEXT_ENTRY(entry, member) \
    CLIST_ENTRY((entry)->member.next, typeof(*(entry)), member)

#define CLIST_PREV_ENTRY(entry, member) \
    CLIST_ENTRY((entry)->member.prev, typeof(*(entry)), member)


#define CLIST_FOR_EACH(it_head, first) \
    for (it_head = (first)->next; it_head != (first); it_head = it_head->next)

#define CLIST_FOR_EACH_SAFE(it_head, tmp_head, first) \
    for (it_head = (first)->next, tmp_head = it_head->next; it_head != (first); it_head = tmp_head, tmp_head = it_head->next)

#define CLIST_FOR_EACH_REVERSE(it_head, first) \
    for (it_head = (first)->prev; it_head != (first); it_head = it_head->prev)

#define CLIST_FOR_EACH_REVERSE_SAFE(it_head, tmp_head, first) \
    for (it_head = (first)->prev, tmp_head = it_head->prev; it_head != (first); it_head = tmp_head, tmp_head = it_head->prev)


#define CLIST_FOR_EACH_ENTRY(it_entry, first, member) \
    for (it_entry = CLIST_NEXT_ENTRY(CLIST_ENTRY(first, typeof(*(it_entry)), member), member); \
        &((it_entry)->member) != (first); \
        it_entry = CLIST_NEXT_ENTRY(it_entry, member))

#define CLIST_FOR_EACH_ENTRY_SAFE(it_entry, tmp_entry, first, member) \
    for (it_entry = CLIST_NEXT_ENTRY(CLIST_ENTRY(first, typeof(*(it_entry)), member), member), \
        tmp_entry = CLIST_NEXT_ENTRY(it_entry, member); \
        &((it_entry)->member) != (first); \
        it_entry = tmp_entry, tmp_entry = CLIST_NEXT_ENTRY(tmp_entry, member))

#define CLIST_FOR_EACH_ENTRY_REVERSE(it_entry, first, member) \
    for (it_entry = CLIST_PREV_ENTRY(CLIST_ENTRY(first, typeof(*(it_entry)), member), member); \
        &((it_entry)->member) != (first); \
        it_entry = CLIST_PREV_ENTRY(it_entry, member))

#define CLIST_FOR_EACH_ENTRY_REVERSE_SAFE(it_entry, tmp_entry, first, member) \
    for (it_entry = CLIST_PREV_ENTRY(CLIST_ENTRY(first, typeof(*(it_entry)), member), member), \
        tmp_entry = CLIST_PREV_ENTRY(it_entry, member); \
        &((it_entry)->member) != (first); \
        it_entry = tmp_entry, tmp_entry = CLIST_PREV_ENTRY(tmp_entry, member))


static inline size_t clist_count_size(clist_head *head)
{
    clist_head *it;
    size_t count = 0;

    CLIST_FOR_EACH(it, head)
    {
        count++;
    }

    return count;
}



#endif