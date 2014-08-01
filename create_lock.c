#include <sys/param.h>
#include <sys/systm.h>
#include <sys/sysproto.h>
#include <sys/priv.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/lock.h>
#include <sys/mutex.h>
#include <sys/types.h>
#include <sys/malloc.h>
#include "locklist.h"
MALLOC_DEFINE(M_FOOBAR,"abs","iabs");
extern struct listhead head;

// int create_lock(char *name, int perms);

int sys_create_lock(struct thread *td, struct set_lgname_args *uap)
{
	struct list_entry *node1;
	struct lock_list_entry *internal_node;
	struct locklisthead locks;
	char *kOutBuf = "Nikhilkh";

	copyin(uap->name, kOutBuf, (sizeof(char)*255));
	LIST_FOREACH(node1, &head, list){

		if(strcmp(node1->lgname,td->td_proc->p_lgname)==0){
			if(node1->count_of_lock<32){
				locks = node1->llhead;
				internal_node = malloc(sizeof(struct lock_list_entry),M_FOOBAR,M_NOWAIT);
				copystr(kOutBuf,internal_node->lgname,255,NULL);
				internal_node->perm = uap->perms;
				internal_node->status = 0;
				LIST_INSERT_HEAD(&locks, internal_node, llist);
			}
		}
	}

	LIST_FOREACH(internal_node, &locks, llist){

		uprintf("The lock name inserted: %s",internal_node->name);
	}
}

