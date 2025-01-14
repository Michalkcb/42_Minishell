/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:40:51 by mbany             #+#    #+#             */
/*   Updated: 2025/01/14 19:08:32 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Funkcja `exit_bltin` obsługuje polecenie `exit` wbudowane w shellu. Sprawdza, czy podano argument (kod wyjścia). Jeśli tak, weryfikuje, czy jest to liczba (z opcjonalnym znakiem minus na początku), i jeśli nie, wyświetla komunikat o błędzie, zwalnia zasoby i kończy program z kodem wyjścia `2`. Jeśli argument jest poprawny, zamienia go na liczbę za pomocą `ft_atoi`. Gdy brak argumentu, używa domyślnego kodu wyjścia. Następnie zwalnia zasoby i zamyka program z odpowiednim kodem wyjścia.
*/
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