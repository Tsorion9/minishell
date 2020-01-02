/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:54:48 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/02 10:10:53 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdlib.h>
# include "libft/includes/libft.h"
# include <dirent.h>

# define BUFSIZE 4096

void		call_check(char *buf, char ***env);
void		replace_tabs(char *buf);
void		execute_pwd(char **call);
void		execute_exit(char **call, char **env);
int			get_call_length(char **call);
void		init_call(char **call, char **env);
void		init_call_sup1(char **call, char **env, int i);
void		init_call_sup(char **call, char **env, int i);
char		*remove_equal_sig(char *call);
char		*remove_equal_sig_sup(char *new_call, char *call);
void		execute_echo(char **env, char **call);
void		print_echo_str(char *str);
void		execute_cd(char **call, char **env);
void		check_dir(char *path, char *prev_dir);
void		check_dir_sup(char *path);
void		check_dir_sup1(char *path);
void		execute_setenv(char **call, char ***env);
void		add_rep_env_var(char **call, char ***env);
void		add_env_var(char **call, char ***env);
int			replace_env_var(char **call, char **env);
void		execute_unsetenv(char **call, char ***env);
int			find_var_env(char **call, char **env);
void		delete_var_env(char **call, char ***env);
void		execute_env(char **call, char ***env);
int			env_flags(char ***new_env, char **call);
int			add_env(char ***new_env, char **call);
char		**create_call_unsetenv(char *val_env);
char		**create_call_setenv(char *val_env);
int			env_flags_sup3(char ***new_env, char **call, int i);
void		env_flags_sup2(char ***new_env, char **call, int i);
int			env_flags_sup1(char ***new_env, char **call, int i);
int			env_flags_sup(char ***new_env, char **call, int i);
void		execute_bin(char **call, char **env, char **new_env);
int			check_binfile(char *filename);
int			check_bunfile_sup(char *filename);
int			execute_sysbin(char **call, char **env, char **new_env);
int			execute_sysbin_sup1(int error, char **call);
int			execute_sysbin_sup(char **c, char **n, char **p, int *e);
int			check_sysbin(char *filename, char *path);
char		*give_val_env(char **env, char *var);
void		print_env(char **env);
char		**copy_env(char **environ);
char		**get_new_env(void);
#endif
