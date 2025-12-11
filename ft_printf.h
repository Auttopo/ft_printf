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

# include <unistd.h>
# include <stdarg.h>

typedef struct s_strc
{
	const char	*str;
	size_t		i;
	size_t		count;
}	t_strc;

int		perce_case(t_strc *s);
int		di_case(t_strc *s, va_list *args);
int		u_case(t_strc *s, va_list *args);
int		c_case(t_strc *s, va_list *args);
int		s_case(t_strc *s, va_list *args);

void	convert_base(unsigned long long num,
			unsigned long long base, char *tbl, char *dest);
char	*convertor(t_strc *s, unsigned long long n, char indice);
void	hex_len(unsigned long long n, int *len);
int		p_case(t_strc *s, va_list *args);
int		x_cases(t_strc *s, va_list *args, char indice);

int		ft_putstr(char *str);
int		ft_putnbr(size_t *count, long long n);
int		no_case(t_strc *s);
int		parser(t_strc *s, va_list *args);
int		ft_printf(const char *intput, ...);

#endif
