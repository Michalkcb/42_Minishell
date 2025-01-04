/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 18:19:19 by mbany             #+#    #+#             */
/*   Updated: 2025/01/04 13:40:09 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_envp
{
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_cmd
{
	char			**cmd;
	char			*infile;
	char			*outfile;
	bool			append;
	bool			here_doc;
	bool			redir_error;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	t_cmd		*cmd;
	t_envp		*envp;
	char		**envp_arr;
	char		*line;
	int			cmd_exit_status;
}	t_data;

typedef struct s_token
{
	int type;
	char*text;
	struct s_token *next;
	
} t_token;


/* errors */
# define MANY_ARGS_ERR "Error: minishell doesn't accept arguments"
# define NO_ENVP_ERR "Error: no environment found"
# define MISS_QUOTE_ERR "Error: missing quote"
# define MISS_CMD_ERR "Error: missing command"
# define SANITIZE_ERROR "Error: line sanitize error"

/* Standard file descriptors.  */
#define	STDIN_FILENO	0	/* Standard input.  */
#define	STDOUT_FILENO	1	/* Standard output.  */
#define	STDERR_FILENO	2	/* Standard error output.  */


/* Print a message describing the meaning of the value of errno.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
extern void perror (const char *__s);

//libft
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int	ft_atoi(const char *nptr);
char	*ft_itoa(int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putstr_fd(char *s, int fd);
int	ft_isspace(char c);
int	ft_isalnum(int c);



//envp
void	free_envp(t_envp *head);
t_envp	*fetch_envp_node(t_envp *head, char *key);
void increment_shlvl(t_envp *head);
t_envp *fetch_envp (char **envp);
//signals
void handle_sigint(int sig);
void	handle_signals(void);
//free
void	free_ft_split(char **split);
void	ft_free_commands(t_cmd **commands);

//check_syntax
int check_syntax(char *line);
int check_if_line_is_empty(char *line);
int check_for_unclosed_quotes(char *line);

//error
int	ft_error_message(char *str, int num);
void	msg_error(char *err);


//utils
void	go_to_next_quote(char *line, int *i, bool go_back);

//sanitize
void	sanitize_line(t_data *data);

//commands
int	ft_commands_creation(t_data *data);

//tokens
t_token *ft_tokenizer(t_data *data, char *text);




#endif