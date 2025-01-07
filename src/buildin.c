/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:40:51 by mbany             #+#    #+#             */
/*   Updated: 2025/01/07 19:43:14 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_bltin(t_data *data)
{
	int	exit_status;
	int	i;

	if (data->cmd->cmd[1] != NULL)
	{
		i = 0;
		while (data->cmd->cmd[1][i] != '\0')
		{
			if (!ft_isdigit(data->cmd->cmd[1][i])
				&& !(i == 0 && data->cmd->cmd[1][i] == '-'))
			{
				msg_error(NUM_REQ_ERR);
				free_resources(data);
				exit(2);
			}
			i++;
		}
		exit_status = ft_atoi(data->cmd->cmd[1]);
	}
	else
		exit_status = data->cmd_exit_status;
	free_resources(data);
	exit(exit_status);
}