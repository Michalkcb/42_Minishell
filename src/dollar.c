/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:07:32 by mbany             #+#    #+#             */
/*   Updated: 2025/01/05 15:11:08 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Funkcja `ft_dollar` przetwarza wystąpienie zmiennej środowiskowej w słowie. Sprawdza poprawność zmiennej poprzez wywołanie `ft_valid_dollar` i uzyskuje jej wartość. Jeśli nie ma zmiennej do przetworzenia, zwraca `-1` i zwalnia pamięć. Gdy zmienna istnieje, indeks `i` jest odpowiednio aktualizowany. Następnie funkcja próbuje rozszerzyć zmienną środowiskową (funkcja `ft_expand_var`) i, jeśli uda się ją zmienić, wywołuje `ft_change_word` w celu zaktualizowania słowa. Jeśli którykolwiek z tych procesów zakończy się błędem (`value == -1`), funkcja zwraca `-1`. W przeciwnym razie, gdy wszystko przebiegnie poprawnie, zwraca `0`.
*/
int	ft_dollar(int *i, char **word, t_data *data)
{
	char	*var;
	int		value;

	value = ft_valid_dollar(i, *word, &var);
	if (value == -1)
	{
		free(word);
		return (-1);
	}
	else if (value >= 1)
		*i = *i + value;
	else
	{
		value = ft_expand_var(var, data->envp, word, i);
		if (value == 0)
		{
			value = ft_change_word(var, word, i, data);
			if (value == -1)
				return (-1);
		}
		else if (value == -1)
			return (-1);
	}
	return (0);
}