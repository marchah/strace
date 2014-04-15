/*
** strace.c for strace in /home/marcha_j//test/c/strace/proj
** 
** Made by hugo marchadier
** Login   <marcha_j@epitech.net>
** 
** Started on  Fri May  4 14:54:50 2012 hugo marchadier
** Last update Fri May  4 17:58:19 2012 hugo marchadier
*/

#include <stdlib.h>
#include <stdio.h>

#include <sys/user.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "xfct.h"
#include "print.h"

int	g_attached_pid;

void	strace(pid_t pid, int flag)
{
  struct user_regs_struct	r;
  int				status;

  xwait(&status);
  if (flag == 1)
    {
      xptrace(PT_STEP, pid, NULL, 0);
      xwait(&status);
    }
  while (!WIFEXITED(status))
    {
      xptrace(PT_GETREGS, pid, NULL, &r);
      if ((int)r.orig_rax != -1 && r.orig_rax < size_tab_syscall())
	print_all_args(pid, r);
      else if ((int)r.orig_rax != -1)
	printf("Unknow syscall: %ld\n", r.orig_rax);
      xptrace(PT_STEP, pid, NULL, 0);
      xwait(&status);
    }
}

void	hand(int s)
{
  (void)s;
  printf(" <unfinished ...>\nProcess %d detached\n", g_attached_pid);
  xptrace(PTRACE_CONT, g_attached_pid, 0, 0);
  exit(EXIT_SUCCESS);
}

void	ptrace_attach(pid_t pid)
{
  printf("Process %d attached - interrupt to quit\n", pid);
  xptrace(PTRACE_ATTACH, pid, NULL, 0);
  g_attached_pid = pid;
  signal(SIGINT, hand);
  strace(pid, 0);
}
