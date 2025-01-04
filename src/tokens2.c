/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:09:41 by mbany             #+#    #+#             */
/*   Updated: 2025/01/04 16:36:12 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_is_chdir(char *inp,int &i,t_token &tokens)
{
	int error;
	char *str;

	str = NULL;
	if (ft_strchr("<>", inp[*i]))
	{
		if (inp[*i] == inp[*i +1])
		{
			if (ft_add_redir(inp, i, tokens, str) == -1)
				return (-1);
			return (0);
		}
		error = ft_single_redir(inp[*i], tokens, str);
		if (error != 0)
			return (-1);
		(*i)++;
		return (0);
	}
	return (0);
}

ft_is_pipe(inp, &i, &tokens)
{

}
ft_is_word(inp, &i, &tokens)
{
	
}

static int ft_add_redir(char *inp, int *i, t_token **tokens, char *str)
{
	int error;

	if (inp[*i] == '<')
		str = ft_strdup("<<");
	else
		str = ft_strdup(">>");
	if (!str)
		return (ft_perror_message());
	if (inp[*i] == '<')
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
