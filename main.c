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
//#include "convert_base.h"

#include <stdio.h>

#include <stdint.h>












int ft_printf(const char *, ...);

typedef struct s_strc
{
	const char	*str;
	size_t	i;
	size_t	count;
} s_strc;

/*-HELPERS------------------------------------------------------------------*/

void	ft_uputnbr_fd(size_t *count, unsigned int n, int fd)
{
	char	c;

	c = (n % 10 + '0');
	if (n > 9)
		ft_uputnbr_fd(count ,(n / 10), fd);
	write(fd, &c, 1);
	*count += 1;
}



/*
void	n_len(long long n, long long *len)
{
	if (n > 0)
		n *= -1;
	if (n < -9)
		n_len(n / 10, len);
	*len += 1;
}
*/
/*
char	*giant_itoa(long long n)
{
	char		*value;
	long long	size;

	size = 0;
	n_len(n, &size);
	if (n < 0)
		size += 1;
	value = malloc(sizeof(char) * (size + 1));
	if (value == NULL)
		return (0);
	if (n < 0)
		value[0] = '-';
	else
		n *= -1;
	value[size] = '\0';
	while (size > 0)
	{
		if (value[size - 1] == '-')
			break ;
		value[size - 1] = ('0' - (n % 10));
		n = n / 10;
		size--;
	}
	return (value);
}
*/

void	hex_len(uintptr_t n, int *len)
{
	if (n > 15)
		hex_len(n / 16, len);
	*len += 1;
}

void	convert_base(long long num, long long base, char *tbl, char *dest)
{
	long long	quot;
	long long	rest;

	quot = num / base;
	rest = num % base;
	if (rest < 0)
		rest *= -1;
	if (quot == 0)
	{
		*dest = tbl[rest];
	}
	if (num / base != 0)
	{
		convert_base(quot, base, tbl, (dest - 1));
		*dest = tbl[rest];
	}
}

char	*convertor(s_strc *s, uintptr_t n)
{
	char *dest;
	int	len;

	len = 0;
	hex_len(n, &len);
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (0);
	write(1, "0x", 2);
	convert_base(n, 16, "0123456789abcdef", (dest + len - 1));
	dest[len] = '\0';
	s->count += (len + 2);

	return (dest);
}




/*-CASES---------------------------------------------------------------------*/

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
	unsigned int temp = va_arg(*args, unsigned int);
	ft_uputnbr_fd(&s->count, temp, 1);
}


void	p_case(s_strc *s, va_list *args)
{
	int TEST = 0;


//
	void *temp = NULL;
	temp = va_arg(*args, void *);

	uintptr_t adress = 0;
	adress = (uintptr_t)temp;

//	printf("%x\n", &temp);
/*	char *dest = NULL;
	dest = malloc(sizeof(char));
	dest[0] = '\0';
	char *index = "0123456789abcdef";
	convert2(adress, 16, index, &dest);
	if (dest == NULL)
		return ;

	ft_putstr_fd(dest, 1);
	free(dest);*/

	char *str_adr = convertor(s, adress);
	if (str_adr == NULL)
	{
		printf("ERRRORRR");
		return ;
	}
	ft_putstr_fd(str_adr, 1);




	free(str_adr);
}


/*-MAIN---------------------------------------------------------------------*/

int	parser(s_strc *s, va_list *args)
{
	s->i += 1;
	if (s->str[s->i] == '%')
	{
		printf("WRONG WAY \n");
		perce_case(s);
	}
	else if (s->str[s->i] == 'c')
		c_case(s, args);
	else if (s->str[s->i] == 'u')
		u_case(s, args);
	else if (s->str[s->i] == 'p')
	{
		p_case(s, args);
	}


	s->i += 1;
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


int	main()
{
//	float tt = 5.11;
//	char str[] = "voici";
//	printf("%-9fflot\n", tt);
//	printf("%-4d", 511);
//	printf("%dp2", printf("%dcoucou|%*d|\n", 55, 3, 10));
	int value = 0;
	int *pt = &value;

		
	int temp = printf("TRU:%pG\n", pt);
	int temp2 = ft_printf("MY_:%pG\n", pt);
	printf("TRU:%d |MY:%d\n", temp, temp2);


	

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
