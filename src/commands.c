/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:04:18 by mbany             #+#    #+#             */
/*   Updated: 2025/01/05 14:18:11 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
static int	ft_create_cmds(t_token *tokens, t_cmd *commands, int i);
static int	ft_free_args(int i, char **cmds);

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
