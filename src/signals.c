/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:48:07 by ltomasze          #+#    #+#             */
/*   Updated: 2024/12/27 15:50:31 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/* Parametr sig reprezentuje numer sygnału, który został wysłany do programu. 
W tej funkcji nie jest on używany, dlatego jest on "ignorowany" (tzn. nie jest przetwarzany). 
To częsta praktyka w przypadku, gdy sygnał jest obsługiwany w sposób ogólny, 
bez konieczności uwzględniania szczegółów sygnału.
write(STDOUT_FILENO, "\n", 1);  // Wypisanie nowej linii do STDOUT
Ma to na celu poprawienie wyglądu terminala, aby po naciśnięciu Ctrl+C 
(co powoduje wysłanie sygnału SIGINT) kursor przesunął się na nową linię, 
a użytkownik nie widział zanieczyszczonego wiersza.
rl_replace_line("", 0);  // Usunięcie poprzedniej linii w buforze readline
Ta funkcja usuwa aktualną linię z bufora Readline. 
W tym przypadku linia jest zastępowana pustym ciągiem znaków 
(czyli linia jest usuwana).
rl_on_new_line();  // Przełączenie na nową linię w buforze readline
rl_redisplay();  // Ponowne wyświetlenie linii w buforze readline
Dzięki temu użytkownik widzi pustą linię, a nie usuniętą linię, którą właśnie wyczyściliśmy.
W skrócie, funkcja handle_sigint zapewnia, że po naciśnięciu Ctrl+C:
Kursor przechodzi na nową linię,
Poprzednia linia jest usuwana z bufora,
Terminal nie zostaje w stanie "brudnym" (pozostaje czysty, z nową pustą linią).*/

void	handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
/*signal(SIGINT, handle_sigint); po to aby po naciśnięciu ctrl+c
nie wyrzuciło nas do dużego shella
signal(SIGQUIT, SIG_IGN); aby po naciśnie ctrl+\ nie przerwalo programu,
ten sygnał jest ignorowany*/