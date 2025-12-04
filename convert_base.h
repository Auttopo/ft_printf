#ifndef WRKPLS
#define WRKPLS

long long	sizer(char *str);
void	relock(char **base, char add);
void	convert(long long num, long long base, char *tbl, char **dest);
char	*ft_convert_base(char *nbr, char *base_from, char *base_to);

long long	is_ok(char *str);
long long	convert_long(char *str, char *index, long long pos, long long base);
long long	atoi_start(char *str, long long *pos_neg, long long *i);
long long	ft_atoi_base(char *str, char *base, long long n_from);

#endif
