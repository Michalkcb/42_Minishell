/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:34:28 by mbany             #+#    #+#             */
/*   Updated: 2024/12/29 16:08:56 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*process_str(char *str, char *str_final, int str_final_len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (j + 1 >= str_final_len)
			str_final_len = realloc_str_final(&str_final, j, str_final_len);
		if (str_final_len == -1)
			return (NULL);
		if (str[i] == '"' || str[i] == '\'')
			handle_quotes(str, str_final, &i, &j);
		else if (ft_isspace(str[i]) && (i == 0 || ft_isspace(str[i + 1])))
			i++;
		else if ((ft_isalnum(str[i]) && is_operator(str[i + 1])) || (str[i] == '|' && (str[i + 1] == '$' || str[i + 1] == '<' || str[i + 1] == '>' )))
			handle_operators(str, str_final, &i, &j);
		else	str_final[j++] = str[i++];
	}
	str_final[j] = '\0';
	return (str_final);
}

void	sanitize_line(t_data *data)
{
	char *str;
	int str_len;

	str = ft_strtrim(data->line, " \t");
	free(data->line);
	if (!str)
		return ;
	str_len = ft_strlen(str) * 2;
	data->line = malloc(sizeof(char) * (ft_strlen(str) * 2));
	if (!data->line)
	{
		free(str);
		msg_error(SANITIZE_ERROR);
		return ;
	}
	data->line = process_str(str, data->line, str_len);
	//data->line = optimize_str_final(data->line);
	if(!data->line)
	{
		free(str);
		msg_error(SANITIZE_ERROR);
		return ;
	}
	free(str);
}