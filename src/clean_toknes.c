/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_toknes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:46:10 by mbany             #+#    #+#             */
/*   Updated: 2025/01/05 15:41:41 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
static int	ft_rm_empty_tokens(t_token **tokens);

int	ft_check_tokens(t_token **tokens)
{
	if (ft_rm_empty_tokens(tokens) == -1)
	{
		ft_free_tokens(tokens);
		return (-1);
	}
	return (0);
}
/*
Funkcja `ft_remove_empty_tokens` usuwa puste tokeny z listy `tokens`. Iteruje przez listę tokenów, a jeśli token ma pusty tekst (`text[0] == '\0'`), sprawdza, czy jego typ jest zgodny z poprawną sekwencją tokenów; w przypadku błędnej sekwencji zwraca błąd z komunikatem. Jeśli token można usunąć, wywołuje `ft_remove_token`, aby go usunąć i zaktualizować wskaźniki, po czym kontynuuje iterację. Funkcja gwarantuje poprawność składni listy tokenów i usuwa zbędne elementy. Na końcu zwraca `0` przy poprawnym zakończeniu.
*/
int	ft_remove_empty_tokens(t_token **tokens)
{
	t_token	*curr;
	t_token	*prev;

	prev = NULL;
	curr = *tokens;
	while (curr)
	{
		if (curr->text && !curr->text[0])
		{
			if (prev && (prev->type != T_WORD && prev->type != T_PIPE
					&& prev->type != T_HEREDOC))
				return (ft_error_message(NULL_REDIR, -1));
			if ((prev && prev->type == T_WORD) || !prev)
			{
				ft_remove_token(tokens, &curr, &prev);
				continue ;
			}
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}