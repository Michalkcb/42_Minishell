/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:33:45 by mbany             #+#    #+#             */
/*   Updated: 2025/01/19 14:40:06 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
Funkcja `echo_bltin` realizuje działanie wbudowanej komendy `echo`, wypisując argumenty przekazane w `cmd` na standardowe wyjście. Obsługuje flagę `-n`, która pomija dodanie znaku nowej linii na końcu. Analizuje kolejne argumenty, sprawdzając poprawność flagi `-n`. Jeśli flaga występuje poprawnie, ustawia zmienną `flag` na `true` i pomija dodawanie nowej linii po wypisaniu argumentów. Po przetworzeniu funkcja wywołuje `ft_echo_args` do wypisania właściwych argumentów i kończy proces kodem `0`. Funkcja służy do odwzorowania działania polecenia `echo` w *minishell*.
*/
void	echo_bltin(char **cmd)
{
	int		i;
	int		j;
	bool	flag;

	i = 1;
	j = 0;
	flag = false;
	while (cmd[i])
	{
		if (!cmd[i][j] || cmd[i][j] != '-')
			break ;
		j++;
		while (cmd[i][j] && cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] || j == 1)
			break ;
		j = 0;
		flag = true;
		i++;
	}
	ft_echo_args(&cmd[i]);
	if (flag == false)
		printf("\n");
	exit(0);
}