/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor_handlers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:51:13 by mbany             #+#    #+#             */
/*   Updated: 2025/01/19 12:37:43 by mbany            ###   ########.fr       */
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
/*
Funkcja `get_output_fd` ustala deskryptor pliku wyjściowego dla danej komendy. Jeśli komenda ma przypisany plik wyjściowy, otwiera go w trybie nadpisywania lub dołączania w zależności od flagi `append`. Jeśli nie ma pliku wyjściowego i komenda jest ostatnia, używa standardowego wyjścia. W przeciwnym razie używa końca zapisu w potoku. Zapewnia, że każda komenda w potoku ma odpowiednio zdefiniowany cel wyjściowy, a w przypadku błędu otwarcia pliku generuje komunikat diagnostyczny.
*/
int	get_output_fd(t_cmd *cmd, int *fd_pipe)
{
	int	output_fd;

	if (cmd->outfile && cmd->append == false)
		output_fd = open(cmd->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (cmd->outfile && cmd->append == true)
		output_fd = open(cmd->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0664);
	else if (cmd->next == NULL)
		output_fd = STDOUT_FILENO;
	else
		output_fd = fd_pipe[1];
	if (output_fd < 0 && cmd->outfile)
		perror(cmd->outfile);
	else if (output_fd < 0 && !cmd->outfile)
		perror("output_fd");
	return (output_fd);
}