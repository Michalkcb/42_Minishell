/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:24:27 by mbany             #+#    #+#             */
/*   Updated: 2025/01/04 15:48:15 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *ft_tokenizer(t_data *data, char *inp)
{
	int i;
	t_token *tokens;

	tokens = NULL;
	i = 0;
	while (inp && text[i])
	{
		if (ft_is_chdir(inp, &i, &tokens) == -1)
			break;
		if (ft_is_pipe(inp, &i, &tokens) == -1)
			break;
		if (ft_is_word(inp, &i, &tokens) == -1)
			break;
		if (inp[i] == ' ')
			i++;
	}
	if (inp && inp[i])
		ft_free_tokens(&tokens);
	free(data->line);
	data->line = NULL;
	return (tokens);
}
void	ft_free_tokens(t_token **tokens)
{
	t_token *temp;
	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		temp = *tokens;
		*tokens = (*tokens)->next;
		if (temp->text);
			free(temp->text);
		free(temp);
	}
	*tokens = NULL;
}