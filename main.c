/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenabde <abenabde@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:32:44 by abenabde          #+#    #+#             */
/*   Updated: 2025/12/02 14:32:45 by abenabde         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "libft.h"

int ft_printf(const char *, ...);

typedef struct s_strc
{
	const char	*str;
	size_t	i;
	size_t	count;
} s_strc;

/*-------------------------------------------------------------------*/

void	ft_uputnbr_fd(unsigned int n, int fd)
{
	char	c;

	c = (n % 10 + '0');
	if (n > 9)
		ft_putnbr_fd((n / 10), fd);
	write(fd, &c, 1);
}

/*----------------------------------------------------------------------*/

void	perce_case(s_strc *s)
{
	ft_putchar_fd('%', 1);
	s->count += 1;
}

void	c_case(s_strc *s, va_list *args)
{
	char temp = va_arg(*args, int);
	ft_putchar_fd(temp, 1);
	s->count += 1;
}

void	u_case(s_strc *s, va_list *args)
{
	char temp = va_arg(*args, unsigned int);
	ft_uputnbr_fd(temp, 1);
	s->count += 1;
}


int	parser(s_strc *s, va_list *args)
{
	s->i += 1;
	if (s->str[s->i] == '%')
		perce_case(s);
	else if (s->str[s->i] == 'c')
		c_case(s, args);
	else if (s->str[s->i] == 'u')
		u_case(s, args);



	return (0);
}

int ft_printf(const char *input, ...)
{
	va_list args;
	s_strc s;

	va_start(args, input);
	s.i = 0;
	s.str = input; //va_arg(args, const char *);
	s.count = 0;
	while (s.str[s.i])
	{
		if (s.str[s.i] == '%')
		{
			parser(&s, &args);
		}
		else
		{
			ft_putchar_fd(s.str[s.i], 1);
			s.count += 1;
			s.i++;
		}
	}
	va_end(args);
	return (s.count);
}

#include <stdio.h>
int	main()
{
//	float tt = 5.11;
//	char str[] = "voici";
//	printf("%-9fflot\n", tt);
//	printf("%-4d", 511);
//	printf("%dp2", printf("%dcoucou|%*d|\n", 55, 3, 10));
	int value = 0;
	int *pt = &value;

		
	char *str = 							"E%uE%cE";
	printf("TRU_|val:%d|%s\n",pt ,printf(str, 500, 'u'));
	printf("MY__|val:%d|%s\n",pt ,ft_printf(str, 500, 'u'));
	return (0);
}



/*
 *
 *
 *
 *			printf + params
 *			if %  ---> lire flags          lire input <---
 *					-> format sortie   entrée formaté <-
 *								   sortie
 *									return (n) chars imprimés			
 *
 *	
 *   %(RIEN) + num place des espaces avant
 *	'+'		place un Plus avant le chiffre si il est positif (à la prio sur le 'space')
 *	'space' place un Espace avant le chiffre si il est positif
 *
 *   - avec un nombre  Place des Espaces apres la donnée pour le nombre de chars libres (à la prio sur le 0)
 *   0 avec un nombre  Place des Zeros apres la donnée pour le nombre de chars libres
 *   |2-> le nombre est à placé après les flags 
 *   * permet de prendre l'entrée paramètre (dans l'ordre de capture)
 *
 *	# conversion dans une autre base
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
*/
