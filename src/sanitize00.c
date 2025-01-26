/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:34:28 by mbany             #+#    #+#             */
/*   Updated: 2025/01/26 10:20:30 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Funkcja `optimize_str_final` tworzy nową 
kopię łańcucha znaków `str_final` za pomocą `ft_strdup`, 
zwalnia pamięć zajmowaną przez oryginalny łańcuch 
i zwraca wskaźnik do nowej kopii. 
Służy do zarządzania pamięcią, 
aby zastąpić oryginalny wskaźnik nowym, 
niezależnym łańcuchem znaków.
*/
static char	*optimize_str_final(char *str_final)
{
	char	*new_str;

	if (!str_final)
		return (NULL);
	new_str = ft_strdup(str_final);
	free(str_final);
	if (!new_str)
		return (NULL);
	return (new_str);
}

/*
Funkcja `is_operator` sprawdza, czy znak `c` 
jest jednym z operatorów (`>`, `<`, `|`). 
Jeśli tak, zwraca `1`; w przeciwnym razie zwraca `0`. 
Służy do rozpoznawania operatorów w analizowanym tekście.
*/
static int	is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	else
		return (0);
}

/*
Funkcja `handle_quotes` przetwarza ciągi ujęte w cudzysłowy w łańcuchu `str`. 
Ustala początek (`i_cp`) i koniec cudzysłowu, 
kopiując jego zawartość do `str_final`. 
Następnie aktualizuje pozycje wskaźników `i` i `j`. 
Jeśli znak po cudzysłowie jest operatorem, 
dodaje spację do `str_final`, aby oddzielić operator od reszty tekstu. 
Funkcja pomaga obsługiwać poprawne 
przetwarzanie cudzysłowów w wejściowych danych.
*/
static void	handle_quotes(char *str, char *str_final, int *i, int *j)
{
	int	i_cp;

	i_cp = *i;
	go_to_next_quote(str, i, false);
	(*i)++;
	ft_strlcpy(&str_final[*j], &str[i_cp], *i - i_cp + 1);
	*j += *i - i_cp;
	if (is_operator(str[*i]))
	{
		str_final[*j] = ' ';
		(*j)++;
		str_final[*j] = '\0';
	}
}

/*
Funkcja `handle_operators` kopiuje operator z `str` do `str_final`, 
przesuwając wskaźniki `i` i `j`, 
a następnie dodaje spację po operatorze. 
Ułatwia to poprawne rozdzielanie 
operatorów w analizowanym ciągu znaków.
*/
static void	handle_operators(const char *str, char *str_final, int *i, int *j)
{
	str_final[(*j)++] = str[(*i)++];
	str_final[(*j)++] = ' ';
}

/*
Funkcja `realloc_str_final` zwiększa dwukrotnie 
rozmiar bufora `str_final`, 
aby pomieścić więcej danych. Tworzy nowy, większy bufor, 
kopiuje dotychczasową zawartość do nowego bufora, 
zwalnia stary bufor i aktualizuje wskaźnik. 
W przypadku błędu alokacji pamięci zwraca `-1`, 
a przy sukcesie zwraca nową długość bufora. 
Używana jest do dynamicznego zarządzania pamięcią dla rosnącego ciągu.
*/
static int	realloc_str_final(char **str_final,
int j, int str_final_len)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * (str_final_len * 2));
	if (!new_str)
	{
		free(*str_final);
		return (-1);
	}
	ft_strlcpy(new_str, *str_final, j);
	free(*str_final);
	*str_final = new_str;
	return (str_final_len * 2);
}
