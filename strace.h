/*
** strace.h for strace in /home/marcha_j//test/c/strace/proj
** 
** Made by hugo marchadier
** Login   <marcha_j@epitech.net>
** 
** Started on  Fri May  4 14:56:39 2012 hugo marchadier
** Last update Fri May  4 14:57:34 2012 hugo marchadier
*/

#ifndef STRACE_H_
# define STRACE_H_

void	strace(pid_t pid, int flag);
void	hand(int s);
void	ptrace_attach(pid_t pid);

# endif /* STRACE_H_ */
