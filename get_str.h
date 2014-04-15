/*
** get_str.h for  in /home/l-huil_o//test/strace/tp/tp2/proj
** 
** Made by olivier l-huillier
** Login   <l-huil_o@epitech.net>
** 
** Started on  Fri May  4 17:39:45 2012 olivier l-huillier
** Last update Fri May  4 17:46:18 2012 olivier l-huillier
*/

#ifndef GET_STR_H_
#define GET_STR_H_

# include	<unistd.h>

# define MAX_STRLEN	42

char		*get_str(pid_t pid, unsigned long reg, unsigned long size);

#endif /* GET_STR_H_ */
