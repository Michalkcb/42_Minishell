/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:38:07 by ltomasze          #+#    #+#             */
/*   Updated: 2025/01/16 18:52:36 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Funkcja `free_envp` zwalnia pamięć wszystkich węzłów listy połączonej `t_envp`.
 */
void	free_envp(t_envp *head)
{
	t_envp	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}
/*
 * Funkcja `fetch_envp_node` przeszukuje listę `t_envp` w poszukiwaniu węzła, którego klucz odpowiada podanemu `key`.
 * Klucz to tekst występujący przed znakiem '=' w wartości węzła.
 * Zwraca wskaźnik na węzeł, jeśli znajdzie, lub NULL, jeśli nie znajdzie.
 */
t_envp	*fetch_envp_node(t_envp *head, char *key)
{
	t_envp*node;
	size_t	key_len;

	key_len = ft_strlen(key);
	node = head;
	while (node != NULL)
	{
		if (ft_strncmp(key, node->value, key_len) == 0 && node->value[key_len] == '=')
			return (node);
		node = node->next;
	}
	return (NULL);
}
/*
 * Funkcja `increment_shlvl` zwiększa wartość zmiennej środowiskowej `SHLVL`.
 * `SHLVL` odpowiada liczbie razy, kiedy uruchomiono powłokę w tej samej sesji.
 */
void increment_shlvl(t_envp *head)
{
	t_envp *node;
	char	*shlvl;
	int	shlvl_nb;

	node = fetch_envp_node(head, "SHLVL");
	shlvl = ft_strchr(node->value, '=') + 1;
	shlvl_nb = ft_atoi(shlvl);
	shlvl_nb++;
	shlvl = ft_itoa(shlvl_nb);
	if (!shlvl)
		perror("ft_itoa");
	free(node->value);
	/*if (!node->value)
		perror("ft_strjoin");*/
	free(shlvl);
}

/*if (!node->value)
		perror("ft_strjoin"); ta część wygląda na niepotrzebną*/
/*
 * Funkcja `fetch_envp` przekształca tablicę `envp` na listę połączoną `t_envp`.
 * Zwraca wskaźnik na początek listy.
 */
t_envp *fetch_envp (char **envp)
{
	t_envp	*envp_node;
	t_envp	*envp_head;
	t_envp	*envp_node_prev;

	envp_node = NULL;
	envp_head = NULL;
	envp_node_prev = NULL;
	while (*envp != NULL)
	{
		envp_node = malloc(sizeof(t_envp));
		envp_node->value = ft_strdup(*envp);
		if(!envp_node || !envp_node->value)
		{
			free_envp(envp_head);
			return (NULL);
		}
		envp_node->next = NULL;
		if (envp_node_prev != NULL)
			envp_node_prev->next = envp_node;
		else
			envp_head = envp_node;
		envp_node_prev = envp_node;
		envp++;
	}
	return (envp_head);
}
/*
Funkcja `append_envp_node` dodaje nowy węzeł do listy jednokierunkowej typu `t_envp` (prawdopodobnie lista przechowująca zmienne środowiskowe). Działa to tak, że zaczyna od głowy listy (`*head`), przeszukuje ją, aby dotrzeć do ostatniego węzła (jeśli lista nie jest pusta). Następnie alokuje pamięć dla nowego węzła, ustawia jego wskaźnik `next` na `NULL` (kończąc listę) i przypisuje wartość `str` do pola `value` nowego węzła. Jeżeli lista była pusta, nowy węzeł staje się głową listy. Funkcja zwraca `0` w przypadku sukcesu, a `-1` w przypadku błędu (np. problem z alokacją pamięci), przy czym przy błędzie wypisuje komunikat o błędzie za pomocą `perror`.
*/
int	append_envp_node(t_envp **head, char *str)
{
	t_envp	*node;
	t_envp	*new_node;

	node = *head;
	while (*head && node->next != NULL)
		node = node->next;
	new_node = malloc(sizeof(t_envp));
	if (!new_node)
	{
		perror("append_envp_node");
		return (-1);
	}
	new_node->next = NULL;
	new_node->value = str;
	if (node)
		node->next = new_node;
	else
		node = new_node;
	return (0);
}
/*
Funkcja `remove_envp_node` usuwa węzeł listy zmiennych środowiskowych `envp`, który znajduje się za podanym węzłem `prev_node`. Aktualizuje wskaźnik `next` w `prev_node`, aby pominąć usuwany węzeł, a następnie zwalnia pamięć zajmowaną przez jego wartość i sam węzeł. Funkcja zapobiega wyciekowi pamięci i zachowuje ciągłość listy.
*/
void	remove_envp_node(t_envp *prev_node)
{
	t_envp	*node;

	node = prev_node->next;
	if (node->next != NULL)
		prev_node->next = node->next;
	else
		prev_node->next = NULL;
	free (node->value);
	free (node);
}
/*
Funkcja `fetch_node_before` wyszukuje węzeł poprzedzający węzeł w liście `envp`, który zawiera zmienną środowiskową o nazwie zgodnej z podanym kluczem `key`. Oblicza długość klucza, a następnie iteruje po liście, porównując `key` z nazwami zmiennych w węzłach. Jeśli zmienna znajduje się w pierwszym węźle, zwraca jego wskaźnik. Jeśli zmienna jest dalej w liście, zwraca wskaźnik na węzeł bezpośrednio poprzedzający. Jeśli zmiennej nie ma, zwraca `NULL`. Funkcja służy do modyfikowania listy przez umożliwienie usuwania lub aktualizacji znalezionego węzła.
*/
t_envp	*fetch_node_before(t_envp **head, char *key)
{
	t_envp	*p_node;
	int		key_len;

	key_len = ft_strlen(key);
	if (!(ft_strncmp(key, (*head)->value, key_len))
		&& (*head)->value[key_len] == '=')
		return (*head);
	p_node = *head;
	while (p_node)
	{
		if (!p_node->next)
			return (NULL);
		else if (!p_node->next->value)
			p_node = p_node->next;
		else if (!(ft_strncmp(key, p_node->next->value, key_len))
			&& p_node->next->value[key_len] == '=')
			return (p_node);
		else
			p_node = p_node->next;
	}
	return (NULL);
}