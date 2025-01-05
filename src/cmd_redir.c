/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:27:24 by mbany             #+#    #+#             */
/*   Updated: 2025/01/05 13:36:50 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

