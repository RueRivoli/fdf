# include "fdf.h"

static char		convert(int i)
{
	if (i >= 0 && i <= 9)
		return (i + 48);
	else if (i >= 10 && i <= 15)
		return (i + 55);
	return (-1);
}
static int		length(int i)
{
	int count;
	int nb;

	count = 1;
	while (i > 15)
	{
		nb = i / 16;
		i = i - nb * 16;
		count++;
	}
	return (count);
}

char	*ft_itohex(int i)
{
	int len;
	int fact;
	char *str;
	int k;
	int a;

	k = 0;
	fact = 1;
	len = length(i);
	a = len;
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (len > 1)
	{
		fact = fact * 16;
		len--;
	}
	//ft_putnbr(fact);
	//ft_putstr(" et le resultat de fac\n");
	while (a > 0)
	{
		//ft_putnbr(i/fact);
		//ft_putchar('\n');
		str[k] = convert(i/fact);
		i = i - (i/fact) * fact;
		fact = fact / 16;
		a--;
		k++;
	}
	return (str);	
}
