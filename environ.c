#include "minishell.h"

// вернуть значение переменной окружения
char		*give_val_env(char **env, char *var)
{
	int		i;
	char	*val;
	int		n;

	n = ft_strlen(var);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], var, n) == 0)
		{
			val = ft_strdup(&(env[i][n + 1]));
			return (val);
		}
		i++;
	}
	ft_putstr("no environment variable named ");
	ft_putstr(var);
	write (1, "\n", 1);
	return (NULL);
}

// Заменить '$' и '~' на соответствующие значения
void		init_call(char **call, char **env)
{
	char	*temp;
	char	*temp1;
	int		i;

	i = 0;
	while (call[i] != NULL)
	{
		if (call[i][0] == '$')
		{
			temp = give_val_env(env, &(call[i][1]));
			free(call[i]);
			call[i] = temp;
		}
		else if (call[i][0] == '~' && (call[i][1] == 0 \
			|| call[i][1] == '/'))
		{
			temp = ft_strdup(&(call[i][1]));
			temp1 = give_val_env(env, "HOME");
			free(call[i]);
			call[i] = ft_strjoin(temp1, temp);
		}
		i++;
	}
}
