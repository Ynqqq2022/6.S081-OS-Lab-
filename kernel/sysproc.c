#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sysinfo.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_trace(void)
{
  int n;
  if(argint(0, &n) < 0)
  { 
    printf("argint 0 :%d\n",n);
    return -1;
  }
  myproc()->trace_mask = n;
  return 0;
}

uint64
sys_info(void)
{
  //the virtual address of sysinfo struct in user space
  uint64 info_user_address; 
  if(argaddr(0,&info_user_address)<0) { 
    printf("argint 0 :%x\n",info_user_address);
    return -1;
  }
  
  struct proc *p = myproc();
  struct sysinfo temp;
  temp.freemem = get_free_mem_count();
  temp.nproc = get_proc_count();

  if(copyout(p->pagetable, info_user_address, (char *)&temp, sizeof(temp)) < 0){
    //printf("copy out error\n");
    return -1;  
  }
  
  return 0;
}
