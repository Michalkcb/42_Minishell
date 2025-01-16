/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:34:11 by mbany             #+#    #+#             */
/*   Updated: 2025/01/16 19:52:58 by mbany            ###   ########.fr       */
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
/*
Funkcja `ft_cd_home` zmienia aktualny katalog roboczy na katalog domowy użytkownika zapisany w zmiennej środowiskowej `HOME`. Jeśli `HOME` nie jest ustawiona, funkcja zwraca błąd. Po zmianie katalogu aktualizuje zmienne środowiskowe `OLDPWD` i `PWD`, które śledzą poprzedni oraz obecny katalog roboczy. Jest kluczowa w projekcie *Minishell*, ponieważ implementuje obsługę komendy `cd` bez argumentów, umożliwiając użytkownikowi szybki powrót do katalogu domowego zgodnie z zachowaniem standardowych powłok systemowych.
*/
static int	ft_cd_home(t_data *data, t_envp *home)
{
	t_envp	*node_pwd;
	char	curr[4096];

	if (!home)
		return (ft_error_message("HOME not set", 1));
	if (chdir(&home->value[5]))
	{
		ft_perror_message();
		return (1);
	}
	getcwd(curr, 4096);
	node_pwd = fetch_envp_node(data->envp, "PWD");
	if (!home)
	{
		if (ft_change_value("OLDPWD", NULL, data) == -1)
			return (1);
	}
	else
	{
		if (ft_change_value("OLDPWD", &node_pwd->value[4], data) == -1)
			return (1);
	}
	if (ft_change_value("PWD", curr, data) == -1)
		return (1);
	return (0);
}