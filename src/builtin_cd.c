/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:34:11 by mbany             #+#    #+#             */
/*   Updated: 2025/01/14 19:37:17 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
Funkcja `cd_bltin` obsługuje polecenie `cd` w shellu, zmieniając bieżący katalog roboczy. Jeśli podano więcej niż jeden argument, zwraca błąd „Too many arguments”. Jeśli brak argumentów, próbuje przejść do katalogu `HOME`, wyszukując go w zmiennych środowiskowych. Jeśli podano jeden argument, używa go do zmiany katalogu za pomocą funkcji `cd_handler`. W przypadku błędu zwraca kod `1`, a przy sukcesie `0`.
*/
int	cd_bltin(char **cmd, t_data *data)
{
	t_envp	*node;

	if (cmd[1] && cmd[2])
		return (ft_error_message("Too many arguments", 1));
	else if (!cmd[1])
	{
		node = fetch_envp_node(data->envp, "HOME");
		return (ft_cd_home(data, node));
	}
	else if (cd_handler(cmd[1], data) == -1)
		return (1);
	return (0);
}