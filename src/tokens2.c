/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:09:41 by mbany             #+#    #+#             */
/*   Updated: 2025/01/05 15:21:20 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
static int	ft_single_redirection(char x, t_token **tokens, char *str);

static int	ft_append_redir(char *input, int *i, t_token **tokens, char *str)
{
	int	error;

	if (input [*i] == '<')
		str = ft_strdup("<<");
	else
		str = ft_strdup(">>");
	if (!str)
		return (ft_perror_message());
	if (input[*i] == '<')
		error = create_token(str, T_HEREDOC, tokens);
	else
		error = create_token(str, T_APPEND, tokens);
	if (error == -1)
	{
		free(str);
		return (-1);
	}
	*i = *i + 2;
	return (0);
}

int	ft_is_redir(char *input, int *i, t_token **tokens)
{
	int		error;
	char	*str;

	str = NULL;
	if (ft_strchr("<>", input[*i]))
	{
		if (input[*i] == input [*i + 1])
		{
			if (ft_append_redir(input, i, tokens, str) == -1)
				return (-1);
			return (0);
		}
		error = ft_single_redirection(input [*i], tokens, str);
		if (error != 0)
			return (-1);
		(*i)++;
		return (0);
	}
	return (0);
}
/*
Funkcja `ft_is_pipe` sprawdza, czy w danym miejscu ciągu wejściowego `input` (indeks wskazany przez `*i`) znajduje się znak `|`. Jeśli tak, kopiuje ten znak do nowo utworzonego ciągu `str` za pomocą `ft_strdup`, a następnie tworzy nowy token typu `T_PIPE`, przekazując go do listy tokenów za pomocą `create_token`. W przypadku błędów (np. brak pamięci podczas tworzenia `str` lub niepowodzenie w `create_token`), funkcja obsługuje błąd przez zwrócenie odpowiedniej wartości (`-1`). Gdy token zostanie utworzony pomyślnie, funkcja zwiększa indeks `*i` (pomija przetworzony znak w `input`) i zwraca `0`. Funkcja działa, by identyfikować znaki `|` jako operator rurociągu w procesie tokenizacji.
*/
int	ft_is_pipe(char *input, int *i, t_token **tokens)
{
	int		error;
	char	*str;

	if (input[*i] == '|')
	{
		str = ft_strdup("|");
		if (!str)
			return (ft_perror_message());
		error = create_token(str, T_PIPE, tokens);
		if (error == -1)
		{
			free(str);
			return (-1);
		}
		(*i)++;
	}
	return (0);
}
/*
Funkcja `ft_is_word` sprawdza, czy znak w ciągu wejściowym `input` na pozycji `*i` nie jest jednym ze znaków specjalnych `|`, `<`, `>` lub spacji. Jeśli warunek jest spełniony, wywołuje funkcję `ft_create_word_tok`, która tworzy token typu "słowo" i dodaje go do listy tokenów. W przypadku błędu w `ft_create_word_tok` funkcja zwalnia pamięć przydzieloną dla `input` i zwraca `-1`, aby zasygnalizować niepowodzenie. W przeciwnym razie funkcja zwraca `0`. Ma na celu identyfikację i tokenizację zwykłych słów w procesie analizy leksykalnej wejścia.*/
int	ft_is_word(char *input, int *i, t_token **tokens, t_data *data)
{
	if (!(ft_strchr("| <>", input[*i])))
	{
		if (ft_create_word_tok(input, i, tokens, data) == -1)
		{
			free(input);
			return (-1);
		}
	}
	return (0);
}
/*
Funkcja `ft_single_redirection` obsługuje pojedyncze znaki przekierowań wejścia (`<`) lub wyjścia (`>`), tworząc odpowiedni token. Na podstawie znaku `x` przypisuje odpowiedni typ (`T_IN_REDIR` lub `T_OUT_REDIR`) oraz kopiuje znak do nowego łańcucha za pomocą `ft_strdup`. Następnie wywołuje `create_token`, aby dodać nowy token do listy `tokens`. Funkcja zwraca `0` w przypadku powodzenia lub `-1`, jeśli wystąpi błąd (np. brak pamięci). Jej celem jest poprawne rozpoznawanie i dodawanie tokenów dla operatorów przekierowań w analizatorze leksykalnym.
*/
static int	ft_single_redirection(char x, t_token **tokens, char *str)
{
	int	type;
	int	error;

	if (x == '<')
	{
		type = T_IN_REDIR;
		str = ft_strdup("<");
	}
	else
	{
		type = T_OUT_REDIR;
		str = ft_strdup(">");
	}
	if (!str)
		return (ft_perror_message());
	error = create_token(str, type, tokens);
	if (error == -1)
	{
		free(str);
		return (-1);
	}
	return (0);
}
/*
Funkcja `ft_create_word_tok` tworzy token reprezentujący słowo w ciągu wejściowym `str`, zaczynając od pozycji `*i`. Oblicza długość słowa `n`, uwzględniając sekwencje znaków wewnątrz pojedynczych (`'`) i podwójnych (`"`) cudzysłowów, oraz ignoruje spacje jako separatory. Gdy długość słowa zostanie wyznaczona, wyodrębnia jego treść i tworzy odpowiedni token za pomocą `ft_extract_word`. Po zakończeniu aktualizuje wartość `*i`, przesuwając wskaźnik na koniec przetworzonego słowa. Funkcja zwraca `0` w przypadku sukcesu lub `-1`, gdy wystąpi błąd. Celem jest poprawne przetwarzanie słów w analizatorze leksykalnym.
*/

int	ft_create_word_tok(char *str, int *i, t_token **tokens, t_data *data)
{
	int	n;

	n = 0;
	while (str[*i + n] && str[*i + n] != ' ')
	{
		if (str[*i + n] == '\'')
			ft_skip_sq(&n, &str[*i]);
		else if (str[*i + n] == '\"')
		{
			n++;
			while (str[*i + n] && str[*i + n] != '\"')
				n++;
			n++;
		}
		else
		{
			while (str[*i + n] && !ft_strchr("\"\' ", str[*i + n]))
				n++;
		}
	}
	if (ft_extract_word(&str[*i], &n, tokens, data) == -1)
		return (-1);
	*i = *i + n;
	return (0);
}
/*
Funkcja `ft_extract_word` tworzy nowy token typu słowo (T_WORD) na podstawie ciągu znaków `str` o długości `*n`, alokując pamięć na nowy ciąg `word` i kopiując do niego odpowiedni fragment. Następnie sprawdza obecność symbolu `$` za pomocą `ft_check_for_dollar`, a później przetwarza słowo funkcją `ft_cross_word`. Jeśli żadna z tych operacji nie zwróci błędu, tworzy nowy token i dodaje go do listy `tokens`. Funkcja umożliwia rozdzielanie słów na tokeny przy analizie leksykalnej, z uwzględnieniem zmiennych środowiskowych i specjalnych modyfikacji.
*/
int	ft_extract_word(char *str, int *n, t_token **tokens, t_data *data)
{
	char	*word;
	int		value;

	word = malloc(sizeof(char) * (*n + 1));
	if (!word)
		return (ft_perror_message());
	ft_strlcpy(word, str, (*n) + 1);
	if (ft_check_for_dollar(&word, data) == -1)
		return (-1);
	value = ft_cross_word(&word, tokens);
	if (value == -1)
	{
		free(word);
		return (-1);
	}
	else if (value == 0)
		return (0);
	if (create_token(word, T_WORD, tokens) == -1)
	{
		free(word);
		return (-1);
	}
	return (0);
}
/*
Funkcja `ft_check_for_dollar` analizuje zawartość ciągu `*word` w poszukiwaniu znaków specjalnych: pojedynczych apostrofów (`'`), znaku dolara (`$`), oraz podwójnych cudzysłowów (`"`). W przypadku znalezienia: pomija zawartość w apostrofach, przetwarza zmienne środowiskowe za pomocą `ft_dollar`, oraz interpretuje zawartość w cudzysłowach przez `ft_cross_dq`. Funkcja modyfikuje zawartość `*word` zgodnie z kontekstem, zwracając -1 w razie błędu. Jej celem jest przetwarzanie i rozwiązywanie zmiennych środowiskowych i specjalnych sekwencji w analizowanym tekście.
*/
int	ft_check_for_dollar(char **word, t_data *data)
{
	int	i;

	i = 0;
	while ((*word)[i])
	{
		if ((*word)[i] == '\'')
			ft_skip_sq(&i, *word);
		else if ((*word)[i] == '$')
		{
			if (ft_dollar(&i, word, data) == -1)
				return (-1);
		}
		else if ((*word)[i] == '\"')
		{
			if (ft_cross_dq (&i, word, data) == -1)
				return (-1);
		}
		else
			i++;
	}
	return (0);
}
/*
Funkcja `ft_cross_word` przetwarza słowo, iterując po jego znakach. Jeśli natrafi na cudzysłów (pojedynczy lub podwójny), wywołuje funkcję `ft_clear_quote`, aby usunąć znaki cytatu. Jeśli napotka białe znaki (spacja, tabulator, itp.), wywołuje `ft_cut_token`, aby podzielić słowo na tokeny; jeśli zwróci błąd lub zakończy proces, odpowiednio przerywa działanie. W przypadku innych znaków po prostu przechodzi do następnego. Funkcja kończy się zwróceniem `1`, jeśli przetworzenie się powiodło.
*/
int	ft_cross_word(char **word, t_token **tokens)
{
	int	i;
	int	value;

	i = 0;
	while ((*word)[i])
	{
		if ((*word)[i] == '\'' || (*word)[i] == '\"')
		{
			if (ft_clear_quote(&i, word, (*word)[i]) == -1)
				return (-1);
		}
		else if (ft_strchr(" \t\r\n\v\f", (*word)[i]))
		{
			value = ft_cut_token(&i, word, tokens);
			if (value == -1)
				return (-1);
			if (value == 0)
				return (0);
		}
		else
			i++;
	}
	return (1);
}

/*
Funkcja `ft_cut_token` przetwarza słowo, tworząc jego token. Zaczyna od alokacji pamięci na nowy ciąg znaków `tok_str` i kopiuje część `*word` do tego ciągu. Następnie wywołuje `create_token`, by utworzyć token typu `T_WORD`. Jeśli to się nie uda, zwraca błąd i zwalnia pamięć. Następnie funkcja ignoruje białe znaki, aż napotka kolejny token lub koniec słowa. Jeśli nie ma więcej znaków, zwalnia pamięć i kończy. Jeśli napotka kolejne znaki, alokuje nową pamięć dla reszty słowa, kopiuje ją do `new_word`, aktualizuje `*word`, a indeks `i` ustawia na 0, by przetwarzać nowe słowo. Funkcja zwraca `1`, gdy słowo jest kontynuowane, lub `0`, gdy nie ma nic więcej do przetworzenia.
*/
int	ft_cut_token(int *i, char **word, t_token **tokens)
{
	char	*tok_str;
	char	*new_word;

	tok_str = malloc(sizeof(char) * (*i + 1));
	if (!tok_str)
		return (ft_perror_message());
	ft_strlcpy(tok_str, *word, *i + 1);
	if (create_token(tok_str, T_WORD, tokens) == -1)
		return (ft_perror_free(tok_str, NULL, NULL));
	while ((*word)[*i] && ft_strchr(" \t\r\n\v\f", (*word)[*i]))
		(*i)++;
	if (!(*word)[*i])
	{
		free(*word);
		return (0);
	}
	new_word = malloc(sizeof(char) * (ft_strlen(&(*word)[*i]) + 1));
	if (!new_word)
		return (ft_perror_message());
	ft_strlcpy(new_word, &(*word)[*i], (ft_strlen(&(*word)[*i]) + 1));
	free(*word);
	*word = new_word;
	*i = 0;
	return (1);
}