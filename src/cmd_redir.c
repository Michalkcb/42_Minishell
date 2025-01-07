/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:27:24 by mbany             #+#    #+#             */
/*   Updated: 2025/01/07 18:48:50 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
static void	ft_here_doc_cmd(t_cmd *current_cmd, char *str);
static void	ft_append_cmd(t_cmd *current_cmd, char *str);
static void	ft_redir_out_cmd(t_cmd *current_cmd, char *str);
static void	ft_redir_in_cmd(t_cmd *current_cmd, char *str);

int ft_set_redir(t_token **current_tok, t_cmd *current_cmd)
{
	char *str;

	if(current_cmd->redir_error == true)
		return (0);
	if (!str)
		return (ft_perror_message());
	if ((*current_tok)->type == T_IN_REDIR)
		ft_redir_in_cmd(current_cmd, str);
	if ((*current_tok)->type == T_OUT_REDIR)
		ft_redir_in_cmd(current_cmd, str);
	if ((*current_tok)->type == T_APPEND)
		ft_append_cmd(current_cmd, str);
	if ((*current_tok)->type == T_HEREDOC)
		ft_here_doc_cmd(current_cmd, str);
	return (0);
}
/*
Funkcja `ft_redir_in_cmd` obsługuje ustawianie pliku wejściowego dla polecenia w strukturze `t_cmd`. Sprawdza, czy plik `str` jest dostępny do odczytu; jeśli nie, ustawia błąd redirekcji w polu `redir_error`, zwalnia pamięć dla `str` i kończy działanie. Jeśli dostęp jest poprawny, zwalnia poprzedni plik wejściowy (jeśli istnieje), przypisuje nowy plik do `infile` i ustawia `here_doc` na `false`, aby oznaczyć brak użycia heredoc.
*/
static void	ft_redir_in_cmd(t_cmd *current_cmd, char *str)
{
	if (ft_check_access(str, READ) < 0)
	{
		current_cmd->redir_error = true;
		free(str);
		return ;
	}
	if (current_cmd->infile)
		free(current_cmd->infile);
	current_cmd->infile = str;
	current_cmd->here_doc = false;
}
