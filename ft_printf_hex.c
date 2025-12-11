/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenabde <abenabde@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:47:30 by abenabde          #+#    #+#             */
/*   Updated: 2025/12/08 14:48:14 by abenabde         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

void	hex_len(unsigned long long n, int *len)
{
	if (n > 15)
		hex_len(n / 16, len);
	*len += 1;
}

void	convert_base(unsigned long long num,
		unsigned long long base, char *tbl, char *dest)
{
	unsigned long long	quot;
	unsigned long long	rest;

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

char	*convertor(t_strc *s, unsigned long long n, char indice)
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

int	p_case(t_strc *s, va_list *args)
{
	char				*str_adr;
	unsigned long long	adress;

	adress = (unsigned long long)va_arg(*args, void *);
	if (adress == 0)
	{
		if (write(1, "(nil)", 5) < 1)
			return (0);
		s->count += 5;
		return (1);
	}
	str_adr = convertor(s, adress, 'p');
	if (str_adr == NULL)
		return (0);
	ft_putstr(str_adr);
	free(str_adr);
	return (1);
}

int	x_cases(t_strc *s, va_list *args, char indice)
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
	ft_putstr(str);
	free(str);
	return (1);
}
