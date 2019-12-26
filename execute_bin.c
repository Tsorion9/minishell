#include "minishell.h"

int         check_binfile(char *filename, char *path)
{
    char        *filepath;
    struct stat fstat;
    char        *temp;

    temp = ft_strjoin(path, "/");
    filepath = ft_strjoin(temp, filename);
    stat(filepath, &fstat);
    if (access(filepath, F_OK))
	{
		ft_putstr("minishell: no such file or directory: ");
		ft_putstr("./");
        ft_putstr(filename);
		write(1, "\n", 1);
        return (0);
	}
    else if (S_ISDIR(fstat.st_mode))
	{
		ft_putstr("minishell: is a directory: ");
		ft_putstr("./");
        ft_putstr(filename);
		write(1, "\n", 1);
        return (0);
	}
    else if (access(filepath, X_OK))
	{
		ft_putstr("minishell: permission denied: ");
		ft_putstr("./");
        ft_putstr(filename);
		write(1, "\n", 1);
        return (0);
	}
    free(filepath);
    free(temp);
    return (1);
}

void        run_file(char **call, char **env, int i)
{
    if (fork() == 0)
        execve(&(call[0][i]), call + 1, env);
    else
        wait(NULL);
    return ;
}

int         execute_sysbin(char **call, char **env)
{
    char    *val_path;
    char    **path;
    char    *filepath;

    if ((val_path = give_val_env(env, "PATH")) == NULL)
        return (0);
    path = ft_strsplit(val_path, ':');
    free(val_path);
    while (*path != NULL)
    {
        filepath = ft_strjoin(*path, "/");
        filepath = ft_strjoin(filepath, *call);
        if (access(filepath, F_OK) == 0)
        {
            if (check_binfile(*call, *path) == 1)
            {
                if (fork() == 0)
                    execve(filepath, call, env);
                else
                    wait(NULL);
                free(filepath);
                return (1);
            }
            return (1);
        }
        path++;
    }
    return (0);
}

void        execute_bin(char **call, char **env)
{
    if (ft_strncmp(call[0], "./", 2) == 0)
    {
        if (check_binfile(&(call[0][2]), "./") == 0)
            return ;
        run_file(call, env, 2);
        return ;
    }
    if (execute_sysbin(call, env) == 0)
    {
	    ft_putstr("minishell: command not found: ");
	    ft_putstr(call[0]);
	    write(1, "\n", 1);
        return ;
    }
}
