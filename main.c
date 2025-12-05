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
#include <stdint.h>
#include <stdlib.h>

//int ft_printf(const char *, ...);

typedef struct s_strc
{
	const char	*str;
	size_t		i;
	size_t		count;
} s_strc;

/*-HELPERS------------------------------------------------------------------*/

int	ft_putstr_fd(char *str, int fd)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (write(fd, &str[i], 1) < 1)
			return (0);
		i++;
	}
	return (1);
}

int	ft_putnbr_fd(size_t *count, long long n, int fd)
{
	char	c;

	if (n < 0)
	{
		if (write(1, "-", 1) < 1)
			return (0);
		*count += 1;
		n = n * -1;
	}
	c = (n % 10 + '0');
	if (n > 9)
		ft_putnbr_fd(count, (n / 10), fd);
	if (write(fd, &c, 1) < 1)
		return (0);
	*count += 1;
	return (1);
}

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
	if (quot == 0)
		*dest = tbl[rest];
	if (num / base != 0)
	{
		convert_base(quot, base, tbl, (dest - 1));
		*dest = tbl[rest];
	}
}

char	*convertor(s_strc *s, long long n, char indice)
{
	char	*dest;
	int		len;

	len = 0;
	hex_len(n, &len);
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (0);
	if (indice == 'p')
	{
		if (write(1, "0x", 2) < 1)
			return (NULL);
		s->count += 2;
	}
	if (indice != 'X')
		convert_base(n, 16, "0123456789abcdef", (dest + len - 1));
	else
		convert_base(n, 16, "0123456789ABCDEF", (dest + len - 1));
	dest[len] = '\0';
	s->count += (len);
	return (dest);
}

/*-CASES---------------------------------------------------------------------*/

int	void_case(s_strc *s)
{
	if (write(1, "(nil)", 5) < 1)
		return (0);
	s->count += 5;
	return (1);
}

int	perce_case(s_strc *s)
{
	if (write(1, "%", 1) < 1)
		return (0);
	s->count += 1;
	return (1);
}

int	c_case(s_strc *s, va_list *args)
{
	char	temp;

	temp = va_arg(*args, int);
	if (write(1, &temp, 1) < 1)
		return (0);
	s->count += 1;
	return (1);
}

int	s_case(s_strc *s, va_list *args)
{
	char	*temp;
	size_t	len;

	len = 0;
	temp = va_arg(*args, char *);
	if (ft_putstr_fd(temp, 1) < 1)
		return (0);
	while (temp[len])
		len++;
	s->count += len;
	return (1);
}

int	p_case(s_strc *s, va_list *args)
{
	void		*temp;
	char		*str_adr;
	uintptr_t	adress;

	temp = va_arg(*args, void *);
	adress = (uintptr_t)temp;
	if (adress == 0)
		return (void_case(s));
	str_adr = convertor(s, adress, 'p');
	if (str_adr == NULL)
		return (0);
	ft_putstr_fd(str_adr, 1);
	free(str_adr);
	return (1);
}

/*-CASES---------------------------------------------------------------------*/

int	di_case(s_strc *s, va_list *args)
{
	int	temp;

	temp = va_arg(*args, int);
	if (ft_putnbr_fd(&s->count, temp, 1) < 1)
		return (0);
	return (1);
}

int	u_case(s_strc *s, va_list *args)
{
	unsigned int	temp;

	temp = va_arg(*args, unsigned int);
	if (ft_putnbr_fd(&s->count, temp, 1) < 1)
		return (0);
	return (1);
}

int	x_cases(s_strc *s, va_list *args, char indice)
{
	unsigned int	temp;
	char			*str;

	temp = va_arg(*args, unsigned int);
	if (indice == 'X')
		str = convertor(s, temp, 'X');
	else
		str = convertor(s, temp, 'x');
	if (str == NULL)
		return (0);
	ft_putstr_fd(str, 1);
	free(str);
	return (1);
}

int	parser(s_strc *s, va_list *args)
{
	int	check;

	s->i += 1;
	check = 1;
	if (s->str[s->i] == '%')
		check = perce_case(s);
	else if (s->str[s->i] == 'c')
		check = c_case(s, args);
	else if (s->str[s->i] == 's')
		check = s_case(s, args);
	else if (s->str[s->i] == 'p')
		check = p_case(s, args);
	else if (s->str[s->i] == 'd' || s->str[s->i] == 'i')
		check = di_case(s, args);
	else if (s->str[s->i] == 'x')
		check = x_cases(s, args, 'x');
	else if (s->str[s->i] == 'X')
		check = x_cases(s, args, 'X');
	else if (s->str[s->i] == 'u')
		check = u_case(s, args);
	s->i += 1;
	return (check);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	s_strc	s;

	va_start(args, input);
	s.i = 0;
	s.str = input;
	s.count = 0;
	while (s.str[s.i])
	{
		if (s.str[s.i] == '%')
		{
			if (parser(&s, &args) == 0)
				return (-1);
		}
		else
		{
			if (write(1, &s.str[s.i], 1) < 1)
				return (-1);
			s.count += 1;
			s.i++;
		}
	}
	va_end(args);
	return (s.count);
}

// MAIN--------------------------------------------------//

#include <stdio.h>
int	main()
{
	char car = 'c';
	char *str = "coucou toi";
	int	cool_value = 914141392;
	int value = 2147483648;
	int uvalue = 4147483648;
	int *ptn = NULL;
		
	int temp = printf("TRU: |%c|%%c |%s|%%s |%p|%%pn |%p|%%p |%d|%%d |%i|%%i |%x|%%x |%X|%%X |%u|%%u\n\n"
			, car, str, ptn, &ptn, value, value, cool_value, cool_value, uvalue);
	int temp2 = ft_printf("MY_: |%c|%%c |%s|%%s |%p|%%pn |%p|%%p |%d|%%d |%i|%%i |%x|%%x |%X|%%X |%u|%%u\n\n"
			, car, str, ptn, &ptn, value, value, cool_value, cool_value, uvalue);

	printf("TRU:%d |MY:%d\n", temp, temp2);
	

	return (0);
}

/*
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
*/
