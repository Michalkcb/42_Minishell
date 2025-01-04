/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:04:18 by mbany             #+#    #+#             */
/*   Updated: 2025/01/04 16:51:18 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (ft_add_redir(&current_token, tokens, &current_cmd, commands) == -1)
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
int	ft_command(t_token **cur_token, t_token *tokens, t_cmd **cur_command, t_cmd *cmds)
{
	
}
