#include <sys/param.h>
#include <sys/systm.h>
#include <sys/sysproto.h>
#include <sys/priv.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/queue.h>
#include "locklist.h"
extern struct listhead head;
int
sys_get_lgname(struct thread *td, struct get_lgname_args *uap)
{
//extern struct listhead head;
struct list_entry *node1;
int rc=0;int count=0;
//struct proc *p = td->td_proc;

LIST_FOREACH(node1, &head, list){
if(count ==0)
rc=copyout(node1->lgname, uap->lgn, (sizeof(char)*8));
count++;

}
return(rc);
}
