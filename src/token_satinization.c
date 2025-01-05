/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_satinization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:49:12 by mbany             #+#    #+#             */
/*   Updated: 2025/01/05 15:16:48 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Funkcja `ft_skip_sq` przeskakuje przez zawartość pojedynczych cudzysłowów (`'`) w ciągu znaków `str`, zaczynając od pozycji `*n`. Najpierw zwiększa `*n`, by pominąć otwierający cudzysłów, następnie iteruje aż do napotkania zamykającego cudzysłowu lub końca łańcucha, a na końcu zwiększa `*n`, by przejść za zamykający cudzysłów. Funkcja umożliwia poprawne ignorowanie zawartości pojedynczych cudzysłowów przy analizie leksykalnej.
*/
void	ft_skip_sq(int *n, char *str)
{
	(*n)++;
	while (str[*n] && str[*n] != '\'')
		(*n)++;
	(*n)++;
}
/*
Funkcja `ft_cross_dq` przetwarza ciąg znaków między podwójnymi cudzysłowami, zaczynając od indeksu `i+1`. Jeśli napotka znak `$`, wywołuje funkcję `ft_dollar` w celu przetworzenia zmiennej środowiskowej; w przypadku błędu zwraca `-1`. Po przetworzeniu każdego znaku (innego niż `$`), funkcja przechodzi do następnego, aż osiągnie zamykający cudzysłów. Na końcu inkrementuje `i` o 1, aby wskazać pozycję za cudzysłowem i zwraca `0`, informując o zakończeniu.
*/
int	ft_cross_dq(int *i, char **word, t_data *data)
{
	(*i)++;
	while ((*word)[*i] != '\"')
	{
		if ((*word)[*i] == '$')
		{
			if (ft_dollar(i, word, data) == -1)
				return (-1);
			continue ;
		}
		(*i)++;
	}
	(*i)++;
	return (0);
}

int	ft_clear_quote(int *i, char **word, char del)
{
	int		n;
	char	*new_word;
	int		len;

	n = 1;
	len = ft_strlen(*word);
	while ((*word)[*i + n] && (*word)[*i + n] != del)
		n++;
	new_word = malloc(sizeof(char) * (len - 1));
	if (!new_word)
		return (ft_perror_message());
	ft_strlcpy(new_word, *word, *i + 1);
	ft_strlcpy(&new_word[*i], &(*word)[*i + 1], n);
	ft_strlcpy(&new_word[*i + n - 1], &(*word)[*i + n + 1], (len - *i - n));
	free(*word);
	*word = new_word;
	*i = *i + n - 1;
	return (0);
}