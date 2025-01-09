/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:34:28 by mbany             #+#    #+#             */
/*   Updated: 2025/01/09 20:05:55 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Funkcja `optimize_str_final` tworzy nową kopię łańcucha znaków `str_final` za pomocą `ft_strdup`, zwalnia pamięć zajmowaną przez oryginalny łańcuch i zwraca wskaźnik do nowej kopii. Służy do zarządzania pamięcią, aby zastąpić oryginalny wskaźnik nowym, niezależnym łańcuchem znaków.
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

static int is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	else
		return (0);
}
static void handle_quotes(char *str, char *str_final, int *i, int *j)
{
	int i_cp;

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

static void handle_operators(const char *str, char *str_final, int *i, int *j)
{
	str_final[(*j)++] = str[(*i)++];
	str_final[(*j)++] = ' ';
}
/*
Funkcja `realloc_str_final` zwiększa dwukrotnie rozmiar bufora `str_final`, aby pomieścić więcej danych. Tworzy nowy, większy bufor, kopiuje dotychczasową zawartość do nowego bufora, zwalnia stary bufor i aktualizuje wskaźnik. W przypadku błędu alokacji pamięci zwraca `-1`, a przy sukcesie zwraca nową długość bufora. Używana jest do dynamicznego zarządzania pamięcią dla rosnącego ciągu.
*/
static int realloc_str_final(char **str_final,int j,int str_final_len)
{
	char *new_str;

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

/*
Funkcja `process_str` przetwarza wejściowy ciąg znaków `str` i zapisuje zaktualizowaną wersję w `str_final`. Iteruje przez `str`, pomijając zbędne spacje i tabulatory oraz obsługując specjalne przypadki, takie jak cudzysłowy (`handle_quotes`) i operatory (`handle_operators`). Jeśli bufor `str_final` staje się za mały, jego rozmiar jest zwiększany za pomocą `realloc_str_final`. Funkcja kończy przetwarzanie, dodając znak null (`\0`) na końcu ciągu i zwracając wynik. Jej celem jest normalizacja i interpretacja wejściowego ciągu znaków w kontekście składni poleceń.
*/
char	*process_str(char *str, char *str_final, int str_final_len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (j + 1 >= str_final_len)
			str_final_len = realloc_str_final(&str_final, j, str_final_len);
		if (str_final_len == -1)
			return (NULL);
		if (str[i] == '"' || str[i] == '\'')
			handle_quotes(str, str_final, &i, &j);
		else if (ft_isspace(str[i]) && (i == 0 || ft_isspace(str[i + 1])))
			i++;
		else if ((ft_isalnum(str[i]) && is_operator(str[i + 1])) || (str[i] == '|' && (str[i + 1] == '$' || str[i + 1] == '<' || str[i + 1] == '>' )))
			handle_operators(str, str_final, &i, &j);
		else	str_final[j++] = str[i++];
	}
	str_final[j] = '\0';
	return (str_final);
}
/*
Funkcja `sanitize_line` czyści wprowadzoną linię tekstu w strukturze `data` poprzez usunięcie początkowych i końcowych spacji oraz tabulatorów za pomocą `ft_strtrim`, tworzy dynamicznie pamięć na zaktualizowany łańcuch o podwójnej długości, przetwarza ten łańcuch za pomocą `process_str`, a następnie optymalizuje go przy użyciu `optimize_str_final`. W razie błędów (np. alokacji pamięci) wyświetla komunikat o błędzie i zwalnia zajętą pamięć. Funkcja służy do przygotowania wprowadzonego tekstu do dalszego przetwarzania.
*/
void	sanitize_line(t_data *data)
{
	char *str;
	int str_len;

	str = ft_strtrim(data->line, " \t");
	free(data->line);
	if (!str)
		return ;
	str_len = ft_strlen(str) * 2;
	data->line = malloc(sizeof(char) * (ft_strlen(str) * 2));
	if (!data->line)
	{
		free(str);
		msg_error(SANITIZE_ERROR);
		return ;
	}
	data->line = process_str(str, data->line, str_len);
	data->line = optimize_str_final(data->line);
	if(!data->line)
	{
		free(str);
		msg_error(SANITIZE_ERROR);
		return ;
	}
	free(str);
}