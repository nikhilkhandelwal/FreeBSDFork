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
struct listhead head;

void listinit(void);
void listinit(void)

        LIST_INIT(&head);
}
SYSINIT(listinitialization, SI_SUB_CREATE_INIT, SI_ORDER_FIRST, listinit, NULL);
int sys_set_lgname(struct thread *td, struct set_lgname_args *uap)
{
//char *kOutBuf = (char *) malloc (sizeof(char) * 8,M_FOOBAR,M_NOWAIT | M_ZERO);
char *kOutBuf = "Nikhilkh";
 int rc;
//LIST_HEAD_INITIALIZER(&head);

struct list_entry *node1,*node2;
int count =100;
struct proc *p;
rc = copyin(uap->lgn, kOutBuf, (sizeof(char)*8));
if (uap->pid != 0) {
p = pfind(uap->pid);
if (p == NULL)
return(ESRCH);
copystr(kOutBuf,p->p_lgname,8,NULL);
node1 = malloc(sizeof(struct list_entry),M_FOOBAR,M_NOWAIT);/* Inserthe head. */
copystr(kOutBuf,node1->lgname,8,NULL);
     LIST_INSERT_HEAD(&head, node1, list);
LIST_FOREACH(node2, &head, list)
{
        count++;
}
PROC_UNLOCK(p);
return(count);

}
return(EPERM) ;
}

