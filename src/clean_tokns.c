/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:46:10 by mbany             #+#    #+#             */
/*   Updated: 2025/01/04 16:37:54 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_tokens(t_token **tokens)
{
	if (ft_rm_empty_tokens(tokens) == -1)
	{
		ft_free_tokens(tokens);
		return (-1);
	}
	return (0);
}