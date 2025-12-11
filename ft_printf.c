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

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (write(1, &str[i], 1) < 1)
			return (0);
		i++;
	}
	return (1);
}

int	ft_putnbr(size_t *count, long long n)
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
		ft_putnbr(count, (n / 10));
	if (write(1, &c, 1) < 1)
		return (0);
	*count += 1;
	return (1);
}

int	no_case(t_strc *s)
{
	if (s->str[s->i] == '\0')
		return (0);
	if (perce_case(s) == 0)
		return (0);
	if (write(1, &s->str[s->i], 1) < 1)
		return (0);
	s->count += 1;
	return (1);
}

int	parser(t_strc *s, va_list *args)
{
	int	check;

	s->i += 1;
	check = 1;
	if (s->str[s->i] == 'c')
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
	else if (s->str[s->i] == '%')
		check = perce_case(s);
	else
		check = no_case(s);
	s->i += 1;
	return (check);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	t_strc	s;

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
/*
#include <stdio.h>
int main()
{
    int num = 9775807;
    int my = ft_printf(" % @_%d", num);
    int tru = printf("\n % @_%d", num);
	printf("\nmy: %d tru: %d\n", my, tru);
}
*/
/*
#include <limits.h>
#include <stdio.h>
int	main()
{
	
	char car = 'c';
	char *str = "coucou toi";
	int	cool_value = 914141392;
	int value = 2147483647;
	unsigned int uvalue = 4147483647;
	int *ptn = NULL;
	
//	int temp = 0;
int temp = printf
("\nTRU: |%c|%%c |%s|%%s |%p|%%pn |%p|%%p 
|%d|%%d |%i|%%i |%x|%%x |%X|%%X |%u|%%u %"
, car, str, ptn, &ptn, value, value, cool_value, cool_value, uvalue);

	  printf("\n");

int temp2 = ft_printf
("\nMY_: |%c|%%c |%s|%%s |%p|%%pn |%p|%%p 
|%d|%%d |%i|%%i |%x|%%x |%X|%%X |%u|%%u %"
, car, str, ptn, &ptn, value, value, cool_value, cool_value, uvalue);

	printf("\nTRUV:%d |MYV:%d\n", temp, temp2);


//	int *p;
//	printf(" NULL %s NULL \n", NULL);
//	ft_printf(" NULL %s NULL ", NULL);
	
	

	return (0);
}
*/
