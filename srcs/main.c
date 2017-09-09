#include "../includes/computorv1.h"

void resolv(t_crd coord)
{
	printf("0 = %f, 1 = %f, 2 = %f\n", coord.x, coord.y, coord.z);
}

static int	ft_inbase(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= ('A' + base - 10)));
}

int			ft_atoi_base(char *str, int base)
{
	int		value;
	int		sign;

	value = 0;
	if (base <= 1 || base > 36)
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
			|| *str == '\r' || *str == '\v')
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_inbase(*str, base))
	{
		if (*str - 'A' >= 0)
			value = value * base + (*str - 'A' + 10);
		else
			value = value * base + (*str - '0');
		str++;
	}
	return (value * sign);
}

int			issp(char c)
{
	return (c == ' ' || c == '\t' || c == '\0');
}

int			ft_count_s(char *str)
{
	int		i;
	int		s;

	i = 0;
	s = 0;
	while (str[i])
	{
		if (issp(str[i]))
			s++;
		i++;
	}
	return (s);
}

int			get_next_nbr(char *str, int *i, int base)
{
	*i = *i + 1;
	while (!(!issp(str[*i]) && issp(str[*i - 1])))
		*i = *i + 1;
	if (base == 16)
		*i = *i + 2;
	return (ft_atoi_base(&str[*i], base));
}

double ft_get_next_nbr(char *str, int *i)
{
	int a;
	int b;
	double c;

	while (str[*i] && !ft_isdigit(str[*i]))
		*i = *i + 1;
	a = ft_atoi(&str[*i]);
	while (str[*i] && ft_isdigit(str[*i]))
		*i = *i + 1;
	if (str[*i] == '.')
		*i = *i + 1;
	b = ft_atoi(&str[*i]);
	while (str[*i] && ft_isdigit(str[*i]))
		*i = *i + 1;
	c = b;
	while (c > 1)
		c /= 10;
	c += a;
	return (c);
}

t_crd parse(char *str)
{
	double tab[3];
	int i;
	int neg;
	double val;
	int pw;

	val = 0;
	i = 0;
	while (i < 3)
		tab[i++] = 0;
	i = 0;
	while (str[i])
	{
		neg = 1;
		while (str[i] && !ft_isdigit(str[i]))
		{
			if (str[i] == '-')
				neg = -1;
			i++;
		}
		val = ft_get_next_nbr(&str[i], &i);
		// val = ft_atoi(&str[i]);
		// while (ft_isdigit(str[++i])) ;
		printf("--- %f ---\n", val);
		printf("%s\n", &str[i]);
		while (!ft_strncmp(&str[i], "X^", 2))
			i++;
		pw = ft_atoi(&str[i]);
		printf("-- %d --\n", pw);
		tab[pw] = tab[pw] + neg * val;
		while (str[i] && ft_isdigit(str[i]))
			i++;
	}
	return ((t_crd){tab[0], tab[1], tab[2]});
}

int main(int argc, char **argv)
{
	t_crd coord;

	if (argc == 2)
	{
		coord = parse(argv[1]);
		resolv(coord);
	}
	return (0);
}
