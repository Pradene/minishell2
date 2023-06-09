/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 06:31:12 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/30 22:11:26 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/types.h>

# include <sys/wait.h>

# include <signal.h>

# include <stdbool.h>

# include <termios.h>

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUFFER_SIZE 4096

extern int	g_exit;

typedef struct s_list
{
	char			*s;
	struct s_list	*next;
}	t_list;

typedef enum e_type
{
	ERR = 0,
	CMD,
	R_OUT,
	R_OUT2,
	R_IN,
	HEREDOC,
	PIPE,
	DBL_PIPE,
	AMP,
	DBL_AMP,
	SEMICOL,
	OPEN_BRACKET,
	CLOSE_BRACKET,
}	t_type;

typedef struct s_node
{
	t_type			type;
	char			**cmd;
	char			*file;
	int				fd_in;
	int				fd_out;
	int				heredoc;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_tmp
{
	t_node			*node;
	struct s_tmp	*next;
}	t_tmp;

typedef struct s_data
{
	char	**env;
	t_node	*root;
	t_tmp	*tmp;
	int		fd0;
	int		fd1;
	int		parse;
	int		exec;
	int		c_heredoc;
	t_list	*tokens;
}	t_data;

// UTILS
char		*ft_addchar(char *s, char c);
long long	ft_atoll(const char *str);
void		ft_bzero(char *s, int n);
int			ft_strncmp(const char *s1, const char *s2, int n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);
int			ft_strlen(const char *s);
void		ft_strcpy(char *s1, char *s2, int n);
char		*ft_strdup(const char *s);
char		*ft_strndup(const char *str, int n);
void		*ft_memcpy(void *dest, const void *src, int n);
char		*ft_strcat(char *s1, char *s2);
char		*ft_strncat(char *s1, char *s2, int n);
char		*ft_stradd(char *s1, char *s2);
char		**ft_split(const char *s, char c);
char		*ft_strrchr(const char *str, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
void		*ft_calloc(size_t nmemb, size_t size);
t_list		*lstlast(t_list *lst);
int			lstsize(t_list *lst);
void		lstadd(t_list **lst, t_list *new);
void		lstclear(t_list **lst);
void		lstprint(t_list *lst);
t_list		*lstnew(char *s);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_itoa(int n);
int			max(int n1, int n2);
int			size_tree(t_node *node);
void		quote_status(char c, int *quote);
void		change_fd(int *old, int new);

// MINISHELL
void		error(char *msg);
void		prerror(char *msg);
int			cmp_env(char *env, char *key);
int			cmp_envs(char **src, char *key);
char		*get_env(char **env, char *s);
char		**envcp(char **envp);
int			last_index(char *s, int c);
char		*get_prompt(void);
void		sig_child(int sig);
void		set_attribute(void);
void		dfree(char **ss);
int			dsize(char **ss);
void		free_data(t_data *data);
void		sig_handler(int sig);
void		sigquit_handler(int sig);

// EXPANSION
char		**expand(t_data *data, char **cmds);
char		*expansion(t_data *data, char *cmd);

// PARSER
void		lclear(t_tmp **lst);
t_node		*new_node(t_data *data, t_type type);
int			heredoc(t_data *data, t_node *node, char *limiter);
int			create_redir(t_data *data, t_node *node, t_type type, char *file);
t_node		*parser_tree(t_data *data, t_list *lst, int first, int last);
void		parse(t_data *data, t_node **root, char **s);

// PARSER SEARCH
t_list		*search_token(t_list *lst, char *token, int *pos, int size);
t_list		*search_orand(t_list *lst, int *pos, int size);
t_list		*search_sep(t_list *lst, int *pos, int size);
int			search_openbrackets(t_list *lst, int first, int last);
int			search_closebrackets(t_list *lst, int first, int last);

// PARSER CMD UTILS
int			check_redir_error(t_data *data, t_node *new, t_list *c);
int			handle_redir(t_data *data, t_node *node, char *type, char *file);
char		**add_to_cmd(char **cmds, char *cmd);

// PARSER UTILS
t_list		*go(t_list *lst, int index);
int			isredir(char *s);
int			issep(char *s);
void		print_error(t_data *data, char *token);
t_type		get_type(char *s);

// TREE
t_node		*create_node(t_data *data, t_list *lst, int first, int last);
t_node		*create_tree(t_data *data, t_list *lst, int first, int last);
void		print_node(t_node *node);
void		print_tree(t_node *node);
void		free_node(t_node **node);

// TMP
void		free_tmp(t_node *node);
void		tmp_clear(t_tmp **lst);
t_tmp		*tmp_last(t_tmp *lst);
void		tmp_add(t_tmp **lst, t_node *node);
void		tmp_print(t_tmp *lst);

// TOKENS
t_list		*tokens(char **s);

// LEXER
char		*lexer(char *command, char **env, int i, int j);
char		**lex(char **cmds, char **env);

// CLEAN CMD
char		*clean_cmd(char *cmd);
char		**clean_cmds(char **tab);

// EXEC UTILS
void		connect_cmd(t_node *left, t_node *right, int fd[2]);
void		sig_child(int sig);
void		sigquit_child(int sig);
int			open_files(t_data *data, t_node *node);

// EXEC
void		exec_builtin(t_data *data, t_node *node);
char		*get_path(char **env, char *cmd);
void		exec_node(t_data *data, t_node *node);
void		exec(t_data *data, t_node *node);
void		get_cmd(t_data *data);

// EXEC ERROR
void		command_nfound(t_data *data, char *cmd);
void		access_error(t_data *data, char *path, char *cmd, int ex);
void		path_isdir(t_data *data, char *path, DIR *dir);

// BUILT-IN
int			is_builtin(char *s);
void		builtin(t_data *data, t_node *node);
void		cd(t_data *data, t_node *node);
void		echo(t_node *node);
void		env(t_data *data, t_node *node);
void		ex(t_data *data, t_node *node);
void		print_export(char **env);
int			export_arg(char *arg);
char		**export(t_data *data, t_node *node);
void		pwd(t_data *data, t_node *node);
char		**unset(t_data *data, t_node *node);

// WILD CARD
char		**wild_card(char **cmds, int i);
char		**add_dir(char *s, char **tab, int d_number);
int			corresponding_dir(char *dir, char **motif, int stars);
int			handle_star(char *cmd);
int			wc_in_quotes(char *s);
char		**create_motif(char *cmd, char **motif);
int			is_quote(char c);

// SINGLETON
t_data		*singleton(t_data *data);

#endif
