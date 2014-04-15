/*
** print.h for print in /home/marcha_j//test/c/strace/proj
** 
** Made by hugo marchadier
** Login   <marcha_j@epitech.net>
** 
** Started on  Fri May  4 15:03:58 2012 hugo marchadier
** Last update Fri May  4 18:12:04 2012 hugo marchadier
*/

#ifndef PRINT_H_
# define PRINT_H_

unsigned long	size_tab_syscall(void);
void	print_arg(pid_t pid, unsigned int pos,
		  struct user_regs_struct r, unsigned long arg);
void	print_all_args(pid_t pid, struct user_regs_struct r);

# endif /* PRINT_H_ */
