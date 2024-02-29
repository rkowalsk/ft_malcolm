#include "ft_malcolm.h"

void free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

int	nbchr(const char *str, const char c)
{
	int	i;
	int nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == c)
			nb++;
		i++;
	}
	return (nb);
}

int	splitlen(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	get_digit_value(char c)
{
	int i;
	char	symbols[] = "0123456789abcdef";

	i = 0;
	while (symbols[i])
	{
		if (symbols[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	parse_hex_value(char *str, unsigned char *value)
{
	int		len;
	int		i;
	char	c;
	int		digit_value;

	len = ft_strlen(str);
	if (len < 1 || len > 2)
		return (1);
	*value = 0;
	i = 0;
	while (i < len)
	{
		*value *= 16;
		c = ft_tolower(str[i]);
		digit_value = get_digit_value(c);
		if (digit_value < 0)
			return (1);
		*value += digit_value;
		i++;
	}
	return (0);
}

int	parse_mac(char *str, unsigned char *dst)
{
	char **split;
	int i;
	(void) dst;

	if (nbchr(str, ':') != 5)
		return (1);
	split = ft_split(str, ':');
	if (!split)
	{
		dprintf(2, "ft_split: %s\n", strerror(errno));
		return (2);
	}
	if (splitlen(split) != 6)
	{
		free_split(split);
		return (1);
	}
	i = 0;
	while (i < 6)
	{
		if (parse_hex_value(split[i], dst + i))
		{
			free_split(split);
			return (1);
		}
		i++;
	}
	return (0);
}
