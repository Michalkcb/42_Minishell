/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:24:27 by mbany             #+#    #+#             */
/*   Updated: 2025/01/04 13:35:33 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *ft_tokenizer(t_data *data, char *text)
{
	int i;
	t_token *tokens;

	tokens = NULL;
	i = 0;
	while (text && text[i])
	{
		if (ft_is_dir(text, &i, &tokens) == -1)
			break;
		if (ft_is_pipe(text, &i, &tokens) == -1)
			break;
		if (ft_is_word(text, &i, &tokens) == -1)
			break;
		if (text[i] == ' ')
			i++;
	}
	
}