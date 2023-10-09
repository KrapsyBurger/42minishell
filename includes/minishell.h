/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:55:33 by rdel-agu          #+#    #+#             */
/*   Updated: 2022/08/25 18:56:01 by rdel-agu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>    
# include <fcntl.h> 
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <termios.h>

extern int		g_global;

typedef struct s_dataa
{
	char			*token;
	char			*token_type;
	struct s_dataa	*next;
}					t_tokens;

typedef struct s_env
{
	char			*var_name;
	char			*var_content;
	struct s_env	*next;
}					t_env;

typedef struct s_minishell
{
	char			*input;
	char			**og_env;
	char			**new_env;
	t_env			*lst_env;
	int				arg_size;
	char			*heredoc_s;
	char			*heredoc_s2;
	int				return_value;
	int				heredoc_bool;
	struct termios	termios;
}				t_minishell;

typedef struct s_structure
{
	char				**infile;
	char				**outfile;
	char				**cmd;
	char				*first;
	int					fd_heredoc;
	int					heredoc_nb;
	int					fd_rd;
	int					fd_wr;
	int					to_append;
	int					to_heredoc;
	char				*heredoc_string;
	char				*heredoc_filename;
	struct s_structure	*next;
}				t_exec;

enum e_state
{
	STATE_GENERAL,
	STATE_IN_FILENAME,
	STATE_IN_PIPE,
	STATE_IN_AMPERSAND,
	STATE_IN_STDIN_REDIRECT,
	STATE_IN_HEREDOC_TOKEN,
	STATE_IN_STDOUT_REDIRECT,
	STATE_IN_APPEND,
	STATE_IN_DOUBLE_QUOTE_OPEN,
	STATE_IN_DOUBLE_QUOTE_CLOSE,
	STATE_IN_SIMPLE_QUOTE_OPEN,
	STATE_IN_SIMPLE_QUOTE_CLOSE,
	STATE_IN_ECHO,
	STATE_IN_ECHO_WHITESPACE,
	STATE_IN_ECHO_DOUBLE_QUOTE_OPEN,
	STATE_IN_ECHO_DOUBLE_QUOTE_CLOSE,
	STATE_IN_ECHO_SIMPLE_QUOTE_OPEN,
	STATE_IN_ECHO_SIMPLE_QUOTE_CLOSE,
};

enum e_character_category
{
	CHAR_GENERAL,
	CHAR_WHITESPACE = ' ',
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_STDIN_REDIRECT = '<',
	CHAR_STDOUT_REDIRECT = '>',
	CHAR_DOUBLE_QUOTE = '"',
	CHAR_SIMPLE_QUOTE = '\'',
	CHAR_EOF = -1,
};

//////////MAIN//////////

void	init(t_minishell *m_s);
void	init_exec(t_exec **ex, t_tokens *temp);
void	token_init(t_tokens **token);

//////////DEMALLOCAGE//////////

void	free_array(char **twoD);
void	demallocage(t_minishell *m_s);
int		free_exec(t_exec **ex);
void	free_exec2(t_exec **ex, int *nb, t_exec **temp, char **filename);
int		ctrl_d_exit(t_minishell *m_s, t_tokens *token);
int		exit_return(t_tokens **token, t_minishell *m_s);

//////////LIBFT//////////

int		is_alpha(char c);
int		ft_strlen(char *s);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		new_strcmp(char *s1, char *s2);

char	*ft_itoa(int n);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
char	**ft_mod_split(char const *s, char c);
char	*ft_substr(char *s, int start, int len);
char	*ft_strnstr(char *hay, char *needle, int len);

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	free_array(char **twoD);
void	ft_putstr_fd(char *s, int fd);
void	ft_puterror(char *s1, char *s2, char *s3);

void	*ft_memset(void *b, int c, size_t len);
int		is_num(char *s);

//////////GNL//////////

void	*gnl_free(char *line);
char	*ft_a(char *a, char *s, unsigned long l, unsigned int b);
char	*gnl_substr(char *s, unsigned int start, int len);
char	*gnl_strjoin(char *s1, char *s2, int b);
int		ft_is_newline(const char *s, int c);
char	*ft_final_substr(char *s, int start, int len);
char	*new_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

//////////HEREDOC//////////

int		heredoc_helper2(t_minishell *ms, t_exec **ex);
int		heredoc_helper3(t_minishell *ms, t_exec **ex);
void	heredoc(t_exec **ex, t_minishell *ms);
int		heredoc_free_token(t_tokens **list);
void	expander_heredoc(char **s, t_minishell *ms);

//////////ENV//////////

int		ft_envsize(t_env *lst);

void	ft_envclear(t_env **lst);
void	env_to_link(t_minishell *m_s);
void	ft_envadd_back(t_env **alst, t_env *new);

char	**link_to_env(t_minishell *m_s);

t_env	*ft_envlast(t_env *lst);
t_env	*ft_envnew(char *content);
void	yes_env(t_minishell *m_s, char **env);
void	no_env(t_minishell *m_s);
void	lvl_plus_one(t_minishell *m_s);

//////////EXIT//////////

int		exit_checker(t_tokens **token);
int		is_there_exit(t_tokens **token, int *pipenb);
int		is_there_pipe(t_tokens **token);

//////////ECHO//////////

void	echo(char *str);

//////////EXPORT//////////

void	tri_char(char **tab);
void	only_export(t_minishell *m_s);
void	replace_value(t_minishell *m_s, char *str);
void	export_blender(t_minishell *m_s, char **cmd);

int		plus_equal(char *str);
int		export(t_minishell *m_s, char *str);
int		export_check(t_minishell *m_s, char *verif);

char	**link_to_only_export(t_minishell *m_s);

//////////PWD//////////

int		pwd(void);

//////////CD//////////

void	cd(t_minishell *m_s, char **cmd);

//////////UNSET//////////

int		unset(t_minishell *m_s, char *str);

void	unset_blender(t_minishell *m_s, char **str);

/////////LEXER//////////

int		strcharjoin(char **token, char c, int state);
int		token_in_list(t_tokens **list, char **token, char *token_type, int ret);
char	translate(char c);
int		free_last_node(t_tokens **tk);
int		ft_free_token(t_tokens **list);
int		exit_free_token(t_tokens **list);
int		lexer(char *input, t_tokens **list);
int		state_general(int category, char c, char **token, t_tokens **list);
int		state_in_filename(int category, char c, char **token, t_tokens **list);
int		state_in_pipe(int category, char c, char **token, t_tokens **list);
int		state_in_ampersand(int category, char c, char **token, t_tokens **list);
int		state_in_stdin_redirect(int category, char c,
			char **token, t_tokens **list);
int		state_in_heredoc_token(int category, char c,
			char **token, t_tokens **list);
int		state_in_stdout_redirect(int category, char c, char **token,
			t_tokens **list);
int		state_in_append(int category, char c, char **token, t_tokens **list);
int		state_in_double_quote_open(int category, char c, char **token,
			t_tokens **list);
int		state_in_double_quote_close(int category, char c, char **token,
			t_tokens **list);
int		state_in_simple_quote_open(int category, char c, char **token,
			t_tokens **list);
int		state_in_simple_quote_close(int category, char c, char **token,
			t_tokens **list);
int		state_in_echo_whitespace(int category, char c, char **token,
			t_tokens **list);
int		state_in_echo(int category, char c, char **token, t_tokens **list);
int		state_in_echo_double_quote_open(int category, char c, char **token,
			t_tokens **list);
int		state_in_echo_double_quote_close(int category, char c, char **token,
			t_tokens **list);
int		state_in_echo_simple_quote_open(int category, char c, char **token,
			t_tokens **list);
int		state_in_echo_simple_quote_close(int category, char c, char **token,
			t_tokens **list);
int		print_list(t_tokens **tokens);

//////////EXPANDER//////////

char	*dollar_replace(t_minishell *m_s, char *str, int indice, int *size);
void	expander(t_tokens **token, t_minishell *m_s);
void	var_increase(int *size, int *i);
int		is_there_quote(char *s);
char	*global_replace(char *s, int i, int *b, char *a);
char	*search_env(t_minishell *m_s, char *analyse);
void	expander_helper2(t_minishell *m_s, t_tokens **a, int *i, int *size);
void	expander_helper3(t_tokens **a, int size);
char	*trim_quote(char *s, int size);
void	simple_quote(char **s, int *index_s, int *index_ret, char **ret);
void	double_quote(char **s, int *index_s, int *index_ret, char **ret);

//////////PARSER//////////

int		new_strcmp(char *s1, char *s2);
int		infile_nbr(t_tokens *temp);
int		infile_fill(t_exec **ex, t_tokens **temp);
int		outfile_nbr(t_tokens *temp);
int		tab_end(char **tab);
int		is_append(t_exec **ex, t_tokens *temp);
int		outfile_fill(t_exec **ex, t_tokens **temp);
int		cmd_nbr(t_tokens *temp);
int		cmd_fill(t_exec **ex, t_tokens **temp, int i);
int		list_fill(t_exec **ex, t_tokens **temp, t_minishell *ms);
int		cmd_helper(t_tokens **temp);
int		heredoc_fill(t_exec **ex, t_tokens **temp, t_minishell *ms);
int		cmp_helper(char *s);
void	init_ex(t_exec **ex);
int		list_fill_helper(t_exec **ex, t_tokens **temp, t_minishell *ms);
int		to_heredoc(t_exec **ex, t_tokens *temp);
char	*parser_strjoin(char *s1, char *s2);
void	init_pipex_parser(t_exec *ex);
int		pipex_parser(t_minishell *m_s, t_tokens **tk);

//////////PIPEXEC//////////

void	empty(t_exec *tmp);
void	pipe_link(t_exec *ex);
void	minisplit(t_exec *ex);
void	close_fd(t_exec *ex, int wr, int rd);
void	pipexec(t_minishell *m_s, t_exec *ex, t_tokens *tk);

int		infile_checker(char	**infile);
int		verif_command(t_exec *ex, char **paths);
int		verif_access(char **paths, t_exec *tmp);
int		outfile_checker(t_exec *ex, char **outfile);
int		command_checker(t_minishell *m_s, t_exec *ex, char *str);

char	**path_splitter(t_env *lst_env);

//////////BLTN//////////

int		is_bltn(char *str);

void	ft_print_env(char **str);
void	bltn_select(char **cmd, t_minishell *m_s);
void	bltn_exec(char **cmd, t_minishell *m_s, t_exec *ex);

//////////CHILD//////////

void	close_all_fd(void);
void	infile(t_exec *tmp);
void	outfile(t_exec *tmp, t_minishell *m_s, t_tokens *tk);
void	dup_checker(t_exec *tmp);
void	child(t_exec *tmp, t_minishell *m_s, t_tokens *tk);
void	infile_heredoc(t_exec *tmp, t_minishell *m_s, t_tokens *tk);

/////////SIGNAL/////////

void	sighandler(int sig);

#endif
