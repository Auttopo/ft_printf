/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenabde <abenabde@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:43:13 by abenabde          #+#    #+#             */
/*   Updated: 2025/12/08 12:43:13 by abenabde         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <aio.h>
#include <stdarg.h>
#include <stdint.h>

typedef struct s_strc
{
	const char	*str;
	size_t		i;
	size_t		count;
} s_strc;

int	ft_putstr_fd(char *str, int fd);
int	ft_putnbr_fd(size_t *count, long long n, int fd);
void	hex_len(unsigned long long n, int *len);
void	convert_base(unsigned long long num, unsigned long long base, char *tbl, char *dest);
char	*convertor(s_strc *s, unsigned long long n, char indice);
int	void_case(s_strc *s);
int	perce_case(s_strc *s);
int	c_case(s_strc *s, va_list *args);
int	s_case(s_strc *s, va_list *args);
int	p_case(s_strc *s, va_list *args);
int	di_case(s_strc *s, va_list *args);
int	u_case(s_strc *s, va_list *args);
int	x_cases(s_strc *s, va_list *args, char indice);
int	parser(s_strc *s, va_list *args);
int	ft_printf(const char *, ...);

#endif

