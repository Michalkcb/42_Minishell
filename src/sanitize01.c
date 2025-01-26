/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:34:28 by mbany             #+#    #+#             */
/*   Updated: 2025/01/26 10:21:31 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Funkcja `process_str` przetwarza wejściowy ciąg znaków `str` 
i zapisuje zaktualizowaną wersję w `str_final`. 
Iteruje przez `str`, pomijając zbędne spacje 
i tabulatory oraz obsługując specjalne przypadki, 
takie jak cudzysłowy (`handle_quotes`) 
i operatory (`handle_operators`). 
Jeśli bufor `str_final` staje się za mały, 
jego rozmiar jest zwiększany za pomocą `realloc_str_final`. 
Funkcja kończy przetwarzanie, 
dodając znak null (`\0`) na końcu ciągu i zwracając wynik. 
Jej celem jest normalizacja i interpretacja wejściowego 
ciągu znaków w kontekście składni poleceń.
*/
char	*process_str(char *str, char *str_final,
int str_final_len)
{
	int	i;
	int	j;

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
		else if
			((ft_isalnum(str[i]) && is_operator(str[i + 1]))
			|| (str[i] == '|' && (str[i + 1] == '$'
			|| str[i + 1] == '<' || str[i + 1] == '>' )))
			handle_operators(str, str_final, &i, &j);
		else
			str_final[j++] = str[i++];
	}
	str_final[j] = '\0';
	return (str_final);
}

/*
Funkcja `sanitize_line` czyści wprowadzoną 
linię tekstu w strukturze `data` poprzez 
usunięcie początkowych i końcowych spacji 
oraz tabulatorów za pomocą `ft_strtrim`, 
tworzy dynamicznie pamięć na zaktualizowany łańcuch o podwójnej długości, 
przetwarza ten łańcuch za pomocą `process_str`, 
a następnie optymalizuje go przy użyciu `optimize_str_final`. 
W razie błędów (np. alokacji pamięci) wyświetla komunikat 
o błędzie i zwalnia zajętą pamięć. 
Funkcja służy do przygotowania wprowadzonego tekstu do dalszego przetwarzania.
*/
void	sanitize_line(t_data *data)
{
	char	*str;
	int		str_len;

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
	if (!data->line)
	{
		free(str);
		msg_error(SANITIZE_ERROR);
		return ;
	}
	free(str);
}
