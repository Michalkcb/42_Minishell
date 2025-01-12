/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:04:18 by mbany             #+#    #+#             */
/*   Updated: 2025/01/12 15:15:07 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
static int	ft_create_cmds(t_token *tokens, t_cmd *commands, int i);
static int	ft_free_args(int i, char **cmds);
/*
Funkcja `ft_count_tok` liczy liczbę tokenów typu `T_WORD` (słowo) w łańcuchu tokenów, zatrzymując się, gdy napotka token typu `T_PIPE`. Działa w następujący sposób: zaczyna od pierwszego tokena, sprawdza jego typ, a jeśli jest różny od `T_WORD`, przeskakuje o dwa tokeny do przodu (przeskakuje przez inne typy tokenów), jeśli napotka token `T_WORD`, inkrementuje licznik, zmienia jego typ na `T_ARG`, a następnie przechodzi do następnego tokena. Funkcja zwraca liczbę tokenów `T_WORD` przed napotkaniem `T_PIPE`.
*/
static int	ft_count_tok(t_token *tokens)
{
	int i;

	i = 0;
	while (tokens && tokens->type != T_PIPE)
	{
		if (tokens->type != T_WORD)
		{
			tokens = tokens->next->next;
			continue;
		}
		i++;
		tokens->type = T_ARG;
		tokens = tokens->next;
	}
	return (i);
}
/*
Funkcja `ft_commands_creation` odpowiada za tworzenie struktury komend na podstawie wejściowego ciągu znaków w `data->line`. Tokenizuje linię przy użyciu `ft_tokenizer`, sprawdza poprawność tokenów poprzez `ft_check_tokens`, a następnie generuje strukturę komend za pomocą `ft_commands`. Jeśli na którymkolwiek etapie wystąpi błąd (tokenizacja, weryfikacja lub tworzenie komend), funkcja ustawia kod wyjścia `cmd_exit_status` na `1` i zwraca `-1`. W przypadku sukcesu zwraca `0`.
*/
int	ft_commands_creation(t_data *data)
{
	t_token *tokens;

	tokens = ft_tokenizer(data, data->line);
	if(tokens == NULL)
	{
		data->cmd_exit_status = 1;
		return (-1);
	}
	if (ft_check_tokens(&tokens) == -1)
	{
		data->cmd_exit_status = 1;
		return (-1);
	}
	if (tokens == NULL)
		return (-1);
	data->cmd = ft_commands(tokens);
	if (data->cmd == NULL)
	{
		data->cmd_exit_status = 1;
		return (-1);
	}
	return (0);
}
/*
Funkcja `ft_commands` przekształca listę tokenów na listę struktur poleceń. Tworzy początkowy element listy poleceń, a następnie iteruje przez tokeny, obsługując redirekcje, argumenty poleceń i operatory potoków przy użyciu funkcji pomocniczych. Jeśli wystąpi błąd w trakcie przetwarzania, funkcja przerywa działanie i zwraca `NULL`. Po zakończeniu tokeny są zwalniane, a lista poleceń zwracana. Funkcja strukturalizuje dane wejściowe do dalszego przetwarzania poleceń.
*/
t_cmd	*ft_commands(t_token *tokens)
{
	t_cmd *commands;
	t_cmd *current_cmd;
	t_token *current_token;

	commands = NULL;
	current_token = tokens;
	if (ft_set_command(&commands) == -1)
	{
		ft_free_tokens(&tokens);
		return (NULL);
	}
	current_cmd = commands;
	while (current_token)
	{
		if (ft_redir(&current_token, tokens, &current_cmd, commands) == -1)
			return (NULL);
		if (ft_command(&current_token, tokens, &current_cmd, commands) == -1)
			return (NULL);
		if (ft_pipe(&current_token, tokens, &current_cmd, commands) == -1)
			return (NULL);
	}
	if (!tokens)
		return (NULL);
	ft_free_tokens(&tokens);
	return (commands);
}
/*
Funkcja `ft_set_command` tworzy nową strukturę polecenia (`t_cmd`), inicjalizuje jej pola wartościami domyślnymi i dodaje ją na koniec listy `commands`. Jeśli lista poleceń jest pusta, nowa struktura staje się jej pierwszym elementem. Funkcja służy do dynamicznego budowania listy poleceń, a w przypadku błędu alokacji pamięci zwraca wartość sygnalizującą błąd.
*/
int	ft_set_command(t_cmd **commands)
{
	t_cmd *new;
	t_cmd *tmp;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (ft_perror_message());
	new->next = NULL;
	new->append = false;
	new->infile = NULL;
	new->outfile = NULL;
	new->cmd = NULL;
	new->redir_error = false;
	new->here_doc  =false;
	if (!(*commands))
		*commands = new;
	else
	{
		tmp = *commands;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}
/*
Funkcja `ft_redir` obsługuje redirekcje w procesie przetwarzania tokenów. Sprawdza, czy bieżący token jest typu innego niż `T_WORD` lub `T_PIPE`, co wskazuje na potencjalną redirekcję. Jeśli kolejny token istnieje i jest słowem (`T_WORD`), wywołuje funkcję `ft_set_redir`, aby ustawić odpowiednią redirekcję dla bieżącego polecenia. W razie błędu lub braku poprawnych tokenów zwalnia zasoby (tokeny i polecenia) i zwraca kod błędu, co zapobiega błędnej konfiguracji poleceń w przypadku problemów z redirekcjami.
*/
int	ft_redir(t_token **current_tok, t_token *head_tok,t_cmd **current_cmd, t_cmd *head_cmd)
{
	if (!*current_tok)
		return (0);
	if ((*current_tok)->type != T_WORD && (*current_tok)->type != T_PIPE)
	{
		if ((*current_tok)->next && (*current_tok)->next->type == T_WORD)
		{
			if (ft_set_redir(current_tok, *current_cmd) == -1)
			{
				ft_free_tokens(&head_tok);
				ft_free_commands(&head_cmd);
				return (-1);
			}
			(*current_tok) = (*current_tok)->next->next;
		}
		else
		{
			ft_free_tokens(&head_tok);
			ft_free_commands(&head_cmd);
			return (ft_error_message(REDIR_TO_OPR, -1));
		}
	}
	return (0);
}
/*
Funkcja `ft_command` analizuje token wskazywany przez `*cur_token` i przetwarza go jako część polecenia. Jeśli token ma typ `T_WORD`, liczy kolejne związane tokeny (`ft_count_tok`), a następnie tworzy polecenie w bieżącej strukturze `t_cmd` za pomocą `ft_create_cmds`. W razie błędu zwalnia pamięć dla tokenów i poleceń oraz zwraca błąd. Jeśli token ma typ `T_ARG`, przeskakuje przez wszystkie argumenty, aktualizując wskaźnik `*cur_token`. Funkcja zwraca `0`, gdy zakończy swoje działanie bez błędów.
*/
int	ft_command(t_token **cur_token, t_token *tokens, t_cmd **cur_command, t_cmd *cmds)
{
	int i;

	if (!(*cur_token))
		return (0);
	if ((*cur_token)->type == T_WORD)
	{
		i = ft_count_tok(*cur_token);
		if (ft_create_cmds(*cur_token, *cur_command, i) == 1)
		{
			ft_free_tokens(&tokens);
			ft_free_commands(&cmds);
			return (-1);
		}
	}
	if ((*cur_token)->type == T_ARG)
	{
		while (*cur_token && (*cur_token)->type == T_ARG)
			*cur_token = (*cur_token)->next;
	}
	return (0);
}
/*
Funkcja `ft_create_cmds` tworzy tablicę argumentów dla polecenia, przetwarzając tokeny typu `T_ARG` aż do napotkania tokenu typu `T_PIPE`. Dla każdego tokena typu `T_ARG` tworzy jego kopię i zapisuje ją w tablicy `cmds`. Jeśli napotka błąd (np. nie uda się skopiować tekstu tokenu), zwalnia już przydzieloną pamięć i kończy działanie funkcji. Na końcu przypisuje tablicę argumentów do struktury polecenia (`commands->cmd`) i zwraca `0`, oznaczając sukces.
*/
static int	ft_create_cmds(t_token *tokens, t_cmd *commands, int i)
{
	char **cmds;
	char *arg;
	int n;

	n = 0;
	cmds = malloc(sizeof(char *) * (i + 1));
	if (!cmds)
		return (ft_perror_message());
	while (tokens && tokens->type != T_PIPE)
	{
		if (tokens->type != T_ARG)
		{
			tokens = tokens->next;
			continue;
		}
		arg = ft_strdup(tokens->text);
		if (!arg)
			return (ft_free_args(n, cmds));
		cmds[n++] = arg;
		tokens = tokens->next;
	}
	cmds[n] = NULL;
	commands->cmd = cmds;
	return (0);
}
/*
Funkcja `ft_free_args` zwalnia pamięć przydzieloną dla tablicy argumentów `cmds`. Iteruje po elementach tablicy, zwalniając każdą z jej pozycji, a potem zwalnia samą tablicę. Na początku wywołuje funkcję `ft_perror_message`, prawdopodobnie w celu wyświetlenia komunikatu o błędzie, a na końcu zwraca `-1`, sygnalizując błąd.
*/
static int	ft_free_args(int i, char **cmds)
{
	int j;

	ft_perror_message();
	j  = 0;
	while (j < i)
		free(cmds[j++]);
	free(cmds);
	return (-1);
}
/*
Funkcja `ft_pipe` obsługuje tokeny typu `T_PIPE`, przechodząc do następnego tokena i aktualizując polecenie po napotkaniu tego tokenu. Jeśli token jest typu `T_PIPE`, wywołuje funkcję `ft_set_command` w celu ustawienia polecenia, a jeśli ta funkcja zakończy się błędem, zwalnia zasoby (tokeny i polecenia) i zwraca `-1`. W przeciwnym razie, jeśli wszystko przebiegnie pomyślnie, przechodzi do kolejnego tokena i kolejnego polecenia. Jeśli początkowy token jest `NULL`, zwraca `0`.
*/
int	ft_pipe(t_token **current_tok, t_token *head_tok,t_cmd **current_cmd, t_cmd *head_cmd)
{
	if (!*current_tok)
		return (0);
	if ((*current_tok)->type == T_PIPE)
	{
		if (ft_set_command(current_cmd) == -1)
		{
			ft_free_tokens(&head_tok);
			ft_free_commands(&head_cmd);
			return (-1);
		}
		(*current_tok) = (*current_tok)->next;
		(*current_cmd) = (*current_cmd)->next;
	}	
	return (0);
}
