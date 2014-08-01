#include <sys/queue.h>
#include <sys/kernel.h>



#ifndef LOCKLIST_H_INCLUDED_GUARD
#define LOCKLIST_H_INCLUDED_GUARD

struct list_entry{
        char lgname[8];
        int count_of_lock;
        int user_id;
        struct locklisthead llhead;
        LIST_ENTRY(list_entry) list;
};

struct lock_list_entry{
        char lockname[255];
        int perm;
        int status;:
         LIST_ENTRY(lock_list_entry) llist;
};


LIST_HEAD(listhead,list_entry);

LIST_HEAD(locklisthead,lock_list_entry);




#endif