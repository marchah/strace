/*
** print.c for print in /home/marcha_j//test/c/strace/proj
** 
** Made by hugo marchadier
** Login   <marcha_j@epitech.net>
** 
** Started on  Fri May  4 15:01:10 2012 hugo marchadier
** Last update Fri May  4 18:13:40 2012 hugo marchadier
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include <sys/user.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <asm/unistd_64.h>

#include "print.h"
#include "xfct.h"
#include "defines.h"
#include "get_str.h"

unsigned long	size_tab_syscall(void)
{
  int	i = 0;

  while (g_tab_syscall[i].nargs != -1)
    i++;
  return (i);
}

static void	print_arg_string(pid_t pid, struct user_regs_struct r,
				  unsigned long arg)
{
  char	*str;

  if (r.orig_rax == __NR_read || r.orig_rax == __NR_write)
    {
      if (r.rax != 0)
	str = get_str(pid, arg, r.rax);
      else
	str = strdup("\"\"");
    }
  else
    str = get_str(pid, arg, 0);
  printf("%s", str);
  free(str);
}

void	print_arg(pid_t pid, unsigned int pos,
		  struct user_regs_struct r, unsigned long arg)
{
  if (strlen(g_tab_syscall[(int)r.orig_rax].token) < pos)
    return ;
  if (pos > 0 && pos != (unsigned int)g_tab_syscall[(int)r.orig_rax].nargs)
    printf(", ");
  if (g_tab_syscall[(int)r.orig_rax].token[pos] == NUM)
    printf("%ld", arg);
  else if (g_tab_syscall[(int)r.orig_rax].token[pos] == STR)
    print_arg_string(pid, r, arg);
  else if (g_tab_syscall[(int)r.orig_rax].token[pos] == ADDR)
    {
      if (arg == 0)
	printf("NULL");
      else
	printf("0x%lx", arg);
    }
  else if (g_tab_syscall[(int)r.orig_rax].token[pos] == VOID)
    printf("void");
  else if (g_tab_syscall[(int)r.orig_rax].token[pos] == CHAR)
    printf("%c", (char)arg);
}

void	print_all_args(pid_t pid, struct user_regs_struct r)
{
  if (g_tab_syscall[(int)r.orig_rax].token != NULL)
    {
      printf("%s(", g_tab_syscall[(int)r.orig_rax].sys_name);
      if (g_tab_syscall[(int)r.orig_rax].nargs > 0)
	print_arg(pid, 0, r, r.rdi);
      if (g_tab_syscall[(int)r.orig_rax].nargs > 1)
	print_arg(pid, 1, r, r.rsi);
      if (g_tab_syscall[(int)r.orig_rax].nargs > 2)
	print_arg(pid, 2, r, r.rdx);
      if (g_tab_syscall[(int)r.orig_rax].nargs > 3)
	print_arg(pid, 3, r, r.rcx);
      if (g_tab_syscall[(int)r.orig_rax].nargs > 4)
	print_arg(pid, 4, r, r.r8);
      if (g_tab_syscall[(int)r.orig_rax].nargs > 5)
	print_arg(pid, 5, r, r.r9);
      printf(")\t=\t");
      print_arg(pid, g_tab_syscall[(int)r.orig_rax].nargs, r, r.rax);
      printf("\n");
    }
  else
    printf("Unimplemented system calls: %s().\n",
	   g_tab_syscall[(int)r.orig_rax].sys_name);
}
