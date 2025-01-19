/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor_handlers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:51:13 by mbany             #+#    #+#             */
/*   Updated: 2025/01/19 12:34:48 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
Funkcja `update_input_fd` obsługuje i aktualizuje deskryptor pliku wejściowego dla komendy, sprawdzając różne przypadki: jeśli `here_doc` jest ustawiony, wywołuje `get_heredoc`, aby utworzyć potok dla wprowadzenia; jeśli wystąpił błąd przekierowania, zwraca -1 jako sygnał błędu; jeśli podano plik wejściowy i nie ma błędu przekierowania, otwiera plik w trybie odczytu, aktualizując deskryptor. Funkcja zapewnia poprawne źródło danych wejściowych dla komend w potoku, obsługując pliki i here-dok.
*/
int	update_input_fd(t_cmd *cmd, int input_fd)
{
	if (cmd->here_doc)
	{
		input_fd = get_heredoc(cmd);
		if (input_fd < 0)
			ft_error_message(HEREDOC_ERR, -1);
		return (input_fd);
	}
	else if (cmd->redir_error == true)
		return (-1);
	else if (cmd->infile && cmd->redir_error == false)
	{
		input_fd = open(cmd->infile, O_RDONLY);
		if (input_fd < 0)
			perror(cmd->infile);
		return (input_fd);
	}
	return (input_fd);
}

