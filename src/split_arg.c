#include "../pipex.h"

void	free_memerror(char **data)
{
	printf("doing free()...");
	exit(1);
}

size_t		count_arg(const char *s)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	if (!s[i])
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != '\0')
			size++;
		if (s[i] == 34 || s[i] == 39)
		{
			while (s[i] == 34 || s[i] == 39)
				i++;
			while (s[i] != 34 && s[i] != 39 && s[i] != '\0')
				i++;
			while (s[i] == 34 || s[i] == 39)
				i++;
		}
		else
		{
			while (s[i] != ' ' && s[i] != '\0')
				i++;
		}
	}
	return (size);
}

char	**add_value(char **arg, const char *s, int size)
{
	int			flag;
	size_t		j;
	size_t		i;
	size_t		count;
	char		*start_str;

	i = -1;
	while (++i < size)
	{
		count = 0;
		flag = 0;
		while (*s == ' ')
			s++;
		if (*s == 34 || *s == 39)
		{
			while (*s == 34 || *s == 39)
			flag = 1;
		}
		else
			start_str = s;
		while (*s != ' ' && *s != '\0')
		{
			count++;
			s++;
		}
		arg[i] = ft_substr(start_str, 0, count);
		if (!arg[i])
		{
			free_memerror(arg);
			return (NULL);

		}
	}

}

char	**split_arg(const char *s)
{
	char	**arg;
	size_t		size;

	if (!s)
		return (NULL);
	printf("incoming split : %s\n", s);
	size = count_arg(s);
	printf("total argument: %d", size);
	arg = ft_calloc((size + 1), sizeof(char *));
	if (!arg)
		return (NULL);
	arg = get_data(arg, s, size);
	return (arg);
}
