/*
** xfct.h for xfct in /home/marcha_j//test/c/strace/proj
** 
** Made by hugo marchadier
** Login   <marcha_j@epitech.net>
** 
** Started on  Thu May  3 16:07:01 2012 hugo marchadier
** Last update Fri May  4 15:09:17 2012 hugo marchadier
*/

#ifndef XFCT_H_
# define XFCT_H_

long    xptrace(enum __ptrace_request request,
		pid_t pid, void *addr, void *data);
void    xexecvp(char *ex, char **arg);
void	xwait(int *status);

# endif /* XFCT_H_ */
