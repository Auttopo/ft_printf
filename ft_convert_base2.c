/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenabde <abenabde@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:37:53 by abenabde          #+#    #+#             */
/*   Updated: 2025/09/01 15:31:37 by abenabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert_base.h"

long long	is_ok(char *str)
{
	long long	i;
	long long	e;

	i = 0;
	while (str[i])
	{
		if (str[i] < 33 || str[i] > 126 || str[i] == '-' || str[i] == '+')
			return (0);
		e = i + 1;
		while (str[e])
		{
			if (str[i] == str[e])
				return (0);
			e++;
		}
		i++;
	}
	if (i < 2)
		return (0);
	return (i);
}

long long	convert_long(char *str, char *index, long long pos, long long base)
{
	long long	e;
	long long	num;
	long long	is_ok;

	num = 0;
	while ((str[pos] >= 33 && str[pos] <= 126) || str[pos] != '-'
		|| str[pos] != '+')
	{
		e = 0;
		is_ok = 0;
		while (index[e])
		{
			if (str[pos] == index[e])
			{
				num = base * num + e;
				is_ok = 1;
			}
			e++;
		}
		if (is_ok == 0)
			return (num);
		pos++;
	}
	return (num);
}

long long	atoi_start(char *str, long long *pos_neg, long long *i)
{
	while ((((str[*i] >= 9) && (str[*i] <= 13))
			|| str[*i] == 32) && str[*i])
	{
		*i = *i + 1;
	}
	while ((str[*i] == '-' || str[*i] == '+') && str[*i])
	{
		if (str[*i] == '-')
			*pos_neg = *pos_neg * -1;
		*i = *i + 1;
	}
	return (0);
}

long long	ft_atoi_base(char *str, char *base, long long n_from)
{
	long long	value;
	long long	i;
	long long	pos_neg;

	i = 0;
	value = 0;
	pos_neg = 1;
	atoi_start(str, &pos_neg, &i);
	value = convert_long(str, base, i, n_from);
	value *= pos_neg;
	return (value);
}
