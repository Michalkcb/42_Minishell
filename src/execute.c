/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:34:09 by mbany             #+#    #+#             */
/*   Updated: 2025/01/18 12:39:14 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
Funkcja `execute_cmds` odświeża tablicę zmiennych środowiskowych na podstawie aktualnej listy połączonej, a następnie wywołuje funkcję `recursive_pipeline`, aby wykonać polecenia w potoku. Jest używana w projekcie *Minishell*, aby zapewnić synchronizację stanu zmiennych środowiskowych i obsłużyć złożone struktury potoków w trakcie wykonywania poleceń.
*/
void	execute_cmds(t_data *data)
{
	if (data->envp_arr)
	{
		free_ft_split(data->envp_arr);
		data->envp_arr = NULL;
	}
	data->envp_arr = convert_envp_llist_to_array(data->envp);
	recursive_pipeline(0, data, data->cmd);
}