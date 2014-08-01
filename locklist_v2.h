#include <sys/queue.h>
#include <sys/kernel.h>



#ifndef LOCKLIST_H_INCLUDED_GUARD
#define LOCKLIST_H_INCLUDED_GUARD

struct list_entry{
        char lgname[8];

        LIST_ENTRY(list_entry) list;
};

LIST_HEAD(listhead,list_entry);



#endif