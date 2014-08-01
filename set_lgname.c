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
{
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
	int user_id_current_proc = td->td_proc->p_ucred->cr_uid;
	int user_id_process_param=0;
	int is_current_process_root=0;
	int lgname_exists=0;
	int pid_to_set_lgname;

	if(user_id_current_proc==0)
		is_current_process_root =1;

	

	rc = copyin(uap->lgn, kOutBuf, (sizeof(char)*8));

	LIST_FOREACH(node1, &head, list){
		if(strcmp(node1->lgname,kOutBuf)==0)
		{
			lgname_exists=1;
		}

	}

	if(uap->pid!=0){
		p = pfind(uap->pid);
	if (p == NULL)
		return(ESRCH);
	user_id_process_param = p->p_ucred->cr_uid;

		if((lgname_exists==0 && is_current_process_root==1) ||(lgname_exists==0 && user_id_process_param == user_id_current_proc))
		{
			copystr(kOutBuf,p->p_lgname,8,NULL);
			node1 = malloc(sizeof(struct list_entry),M_FOOBAR,M_NOWAIT);
			copystr(kOutBuf,node1->lgname,8,NULL);
			node1->user_id = user_id_process_param;
			node1->count_of_lock = 0;
			LIST_INIT(&node1->llhead);
			LIST_INSERT_HEAD(&head, node1, list);
		}
		else if(lgname_exits!=0 && is_current_process_root==1 ||lgname_exists!=0 && user_id_process_param == user_id_current_proc)
		{
			copystr(kOutBuf,p->p_lgname,8,NULL);

		}
		else{
			return (ESRCH); // cannot set lck group name for the pid
		}
	}
	else
	{
		user_id_process_param = td->td_proc->p_ucred->cr_uid;
		if(lgname_exists==0)
		{
			copystr(kOutBuf,td->td_proc->p_lgname,8,NULL);
			node1 = malloc(sizeof(struct list_entry),M_FOOBAR,M_NOWAIT);
			copystr(kOutBuf,node1->lgname,8,NULL);
			node1->user_id = user_id_current_proc;
			node1->count_of_lock = 0;
			LIST_INSERT_HEAD(&head, node1, list);
		}
		else if(lgname_exists!=0 && is_current_process_root==1||lgname_exists!=0 && user_id_process_param == user_id_current_proc)
		{
			copystr(kOutBuf,td->td_proc->p_lgname,8,NULL);

		}
		else
		{
			return (ESRCH); 
		}
	}
	PROC_UNLOCK(p);
	return(EPERM) ;
}

