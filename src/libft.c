/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:20:20 by ltomasze          #+#    #+#             */
/*   Updated: 2025/01/25 16:41:16 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
	{
		i++;
	}
	if (s1[i] == s2[i])
		return (0);
	else
		return (s1[i] - s2[i]);
}

char	*ft_strdup(const char *s)
{
	char	*s2;
	int		s_len;
	int		i;

	s_len = 0;
	while (s[s_len] != '\0')
		s_len++;
	s2 = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	if (!dst)
		return (0);
	i = 0;
	while (src[i] != '\0' && i + 1 < size)
	{
		dst[i] = src[i];
		i++;
	}
	if (size == 1)
		dst[0] = '\0';
	else if (size > 1)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * result);
}

static char	*ft_char(char *s, unsigned int number, long int len)
{
	while (number > 0)
	{
		s[len--] = 48 + (number % 10);
		number = number / 10;
	}
	return (s);
}

static long int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char				*s;
	long int			len;
	unsigned int		number;
	int					sign;

	sign = 1;
	len = ft_len(n);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!(s))
		return (NULL);
	s[len--] = '\0';
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		sign *= -1;
		number = n * -1;
		s[0] = '-';
	}
	else
		number = n;
	s = ft_char(s, number, len);
	return (s);
}

char	*ft_strchr(const char *s, int c)
{
	const char	*p;
	int			i;

	p = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			p = &s[i];
			break ;
		}
		i++;
	}
	if (c == '\0')
		p = &s[i];
	return ((char *)p);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*dest;

	while (!s1)
		return (0);
	while (!set)
		return ((char *)s1);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[end] && ft_strchr(set, s1[end]) && end >= start)
		end--;
	dest = (char *)malloc(sizeof(char) * ((end - start + 1) + 1));
	if (!dest)
		return (0);
	ft_strlcpy(dest, s1 + start, (end - start + 1) + 1);
	return (dest);
}

int	ft_isalnum(int c)
{
	return ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'));
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
	{
		return (1);
	}
	return (0);
}

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	else
		return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	int		l;

	ptr = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start || !len)
	{
		ptr = malloc(sizeof(char));
		if (!ptr)
			return (NULL);
		*ptr = 0;
		return (ptr);
	}
	if (len <= ft_strlen(s) - start)
		l = len + 1;
	else
		l = ft_strlen(s) - start + 1;
	ptr = (char *)malloc(sizeof(char) * l);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s + start, l);
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_join;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	s_join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s_join)
		return (NULL);
	ft_strlcpy(s_join, s1, ft_strlen(s1) + 1);
	i = 0;
	while (i < ft_strlen(s2))
	{
		s_join[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	s_join[ft_strlen(s1) + i] = '\0';
	return (s_join);
}

static int	num_words_count(char const *s, char c)
{
	int	num_words;
	int	i;

	num_words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			num_words++;
		i++;
	}
	return (num_words);
}

static void	split_words(char **result, char const *s, char c, int i)
{
	int	start;
	int	j;
	int	k;

	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			result[j] = malloc((i - start + 1) * sizeof(char));
			if (!result[j])
				return ;
			k = 0;
			while (start < i)
				result[j][k++] = s[start++];
			result[j++][k] = '\0';
		}
		else
			i++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		num_words;
	char	**result;
	int		i;

	i = 0;
	num_words = num_words_count(s, c);
	result = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	split_words(result, s, c, i);
	result[num_words] = NULL;
	return (result);
}
