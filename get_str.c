/*
** get_str.c for  in /home/l-huil_o//test/strace/tp/tp2/proj
** 
** Made by olivier l-huillier
** Login   <l-huil_o@epitech.net>
** 
** Started on  Fri May  4 17:39:02 2012 olivier l-huillier
** Last update Fri May  4 18:10:06 2012 olivier l-huillier
*/

#include	<string.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<ctype.h>

#include	<sys/ptrace.h>
#include	<sys/user.h>

#include	"get_str.h"
#include	"xfct.h"
#include	"print.h"

static void		strnadd(char **s1, char *s2, size_t len2)
{
  size_t	len1;

  len1 = 0;
  if (*s1 != NULL)
    len1 = strlen(*s1);
  if ((*s1 = realloc(*s1, len1 + len2 + 1)) == NULL)
    {
      fprintf(stderr, "Error: realloc failed\n");
      exit(EXIT_FAILURE);
    }
  strncpy(&(*s1)[len1], s2, len2);
  (*s1)[len1 + len2] = '\0';
}

static int	get_str_init(char **str, int *max,
			     unsigned long *size, size_t *total)
{
  *str = NULL;
  *max = 0;
  if (*size > MAX_STRLEN)
    {
      *size = MAX_STRLEN;
      *max = 1;
    }
  *total = 0;
  return (1);
}

static void	get_one_char(char **str, char c)
{
  int		slen;
  char		nb[8];

  if (isprint(c))
    strnadd(str, &c, 1);
  else
    {
      if (c == '\n')
	strnadd(str, "\\n", 2);
      else if (c == '\t')
	strnadd(str, "\\t", 2);
      else
	{
	  slen = sprintf(nb, "\\%o", c);
	  strnadd(str, nb, slen);
	}
    }
}

static void	get_str_end(char **str, int max)
{
  strnadd(str, "\"", 1);
  if (max)
    strnadd(str, "...", 3);
}

char		*get_str(pid_t pid, unsigned long reg, unsigned long size)
{
  char		*peek;
  size_t	i;
  size_t	total;
  int		cont;
  int		max;
  char		*str;

  cont = get_str_init(&str, &max, &size, &total);
  strnadd(&str, "\"", 1);
  while (cont)
    {
      peek = (char*)xptrace(PTRACE_PEEKDATA, pid, (char*)(reg + total), 0);
      i = 0;
      while (i < 8 && ((((char*)&peek + i)[0] != '\0'
			&& size == 0) || size != 0))
	{
	  get_one_char(&str, ((char*)&peek + i)[0]);
	  ++i;
	}
      total += i;
      if ((i < 8 && size == 0) || (total >= size && size > 0))
	cont = 0;
    }
  get_str_end(&str, max);
  return (str);
}
