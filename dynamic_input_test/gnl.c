#include "dynamic_input.h"

int	ft_safe_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		return (0);
	}
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static int	is_newline(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (str[i] == '\n')
			return (i + 1);
	return (0);
}

static int	read_buffer(int fd, char *buffer)
{
	if (buffer[0] != '\0')
	{
		return (1);
	}
	if (read(fd, buffer, BUFFER_SIZE) > 0)
	{
		return (1);
	}
	return (0);
}

void	*ft_gnl_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (!dest && !src)
		return (NULL);
	while (++i < BUFFER_SIZE)
	{
		if (n && i < BUFFER_SIZE - n)
		{
			((char *)dest)[i] = ((char *)src)[i];
		}
		else
			((char *)dest)[i] = '\0';
	}
	return (dest);
}

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	len1 = ft_safe_strlen(s1);
	if (n)
		len2 = n;
	else
		len2 = ft_safe_strlen(s2);
	str = malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (free(s1), NULL);
	str[len2 + len1] = '\0';
	while (len2--)
		str[len1 + len2] = s2[len2];
	while (len1--)
		str[len1] = s1[len1];
	free(s1);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*tmp;
	int			nl;

	tmp = NULL;
	while ((!is_newline(tmp)) && read_buffer(fd, (char *)buffer) > 0)
	{
		nl = is_newline(buffer);
		tmp = ft_strnjoin(tmp, buffer, nl);
		if (!tmp)
			return (NULL);
		ft_gnl_memmove(buffer, &buffer[nl], nl);
	}
	return (tmp);
}

char	*get_all_lines(int fd)
{
	char	*string = NULL;
	char	*tmp = get_next_line(fd);

	while (tmp)
	{
		string = ft_strnjoin(string, tmp, 0);
		(free(tmp), tmp = NULL);
		printf("+1\n");
		tmp = get_next_line(fd);
	}

	return (string);
}
