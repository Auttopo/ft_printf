/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenabde <abenabde@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:37:38 by abenabde          #+#    #+#             */
/*   Updated: 2025/09/01 15:34:29 by abenabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "convert_base.h"

long long	sizer(char *str)
{
	long long	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	relock(char **base, char add)
{
	char	*new;
	long long		i;

	i = 0;
	new = NULL;
	new = malloc(sizeof(char) * (sizer(base[0]) + 2));
	while (base[0][i] != '\0')
	{
		new[i] = base[0][i];
		i++;
	}
	new[i] = add;
	new[i + 1] = '\0';
	free(base[0]);
	base[0] = new;
}

void	convert(long long num, long long base, char *tbl, char **dest)
{
	long long	quot;
	long long	rest;

	quot = num / base;
	rest = num % base;
	if (rest < 0)
		rest *= -1;
	if (quot == 0)
	{
		relock(dest, tbl[rest]);
	}
	if (num / base != 0)
	{
		convert(quot, base, tbl, dest);
		relock(dest, tbl[rest]);
	}
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char	*ary;
	long long		n_to;
	long long		n_from;
	long long		value;

	n_to = is_ok(base_to);
	if (n_to == 0)
		return (NULL);
	n_from = is_ok(base_from);
	if (n_from == 0)
		return (NULL);
	value = ft_atoi_base(nbr, base_from, n_from);
	if (value < 0)
	{
		ary = malloc(sizeof(char) * 2);
		ary[0] = '-';
		ary[1] = '\0';
	}
	else
	{
		ary = malloc(sizeof(char));
		ary[0] = '\0';
	}
	convert(value, n_to, base_to, &ary);
	return (ary);
}

/*
#include <stdio.h>
long long main(int argc, char **argv)
{
	if (argc != 4)
		return (0);

//	(void)argv;
//	(void)argc;

	char *out = ft_convert_base(argv[1], argv[2], argv[3]);
//	char *nbr = "          --+-//==       ";
//	char *from = "=_/";
//	char *to = "0123456789";
//	char *out = ft_convert_base(nbr, from, to);

	prlong longf("%s\n", out);
	free(out);
}
*/
