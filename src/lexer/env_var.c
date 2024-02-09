/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:39:29 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/09 12:20:39 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_env(t_data *shell, char **envp)
{
	int	i;
	
	i = 0;
	while (envp[i])
		i++;
	shell->envp = malloc(sizeof(char *) * (i + 1));
	if (!shell->envp)
		malloc_fail(shell);
	i = 0;
	while (envp[i])
	{
		shell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->envp[i] = NULL;
}

char	*copy_env_var(char *old_str, int i, char *envp, int len_var)
{
	char	*new_str;
	int		len_envp;
	int		len;

	len_envp = ft_strlen(envp + len_var + 1);
	len = i;
	len += len_envp;
	len += ft_strlen(old_str + i + len_var);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, old_str, i + 1);
	ft_strlcpy(new_str + i, envp + len_var + 1, len_envp + 1);
	ft_strlcpy(new_str + i + len_envp, old_str + i + len_var + 1, len - i - len_envp + 1);
	return (new_str);
}

char	*remove_env_var(char *old_str, int i, int len_var)
{
	char	*new_str;
	int		len;

	len = ft_strlen(old_str) - len_var;
	new_str = malloc(sizeof(char) * (len));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, old_str, i);
	ft_strlcpy(new_str + i - 1, old_str + i + len_var, len - i + 1);
	return (new_str);	
}

void	get_env_vars(t_data *shell)
{
	char	*str_mod;
	int		len;
	int		i;
	int		j;
	
	i = 0;
	while (shell->input[i])
	{
		str_mod = NULL;
		len = 0;
		j = 0;
		if (shell->input[i] == '\'')
		{
			i++;
			while (shell->input[i] != '\'')
				i++;
			if (shell->input[i] == '\'')
				i++;
		}
		if (shell->input[i] == '$')
		{
			i++;
			while (shell->input[i + len] && shell->input[i + len] != ' ' && shell->input[i + len] != '\"')
				len++;
			while (shell->envp[j])
			{
				if (!ft_strncmp(&shell->input[i], shell->envp[j], len))
				{
					if (!ft_strncmp(shell->envp[j] + len, "=", 1))
					{
						str_mod = copy_env_var(shell->input, i - 1, shell->envp[j], len);
						if (!str_mod)
							malloc_fail(shell);
						free(shell->input);
						shell->input = str_mod;
					}
				}
				j++;
			}
			if (!str_mod)
			{
				str_mod = remove_env_var(shell->input, i, len);
				if (!str_mod)
						malloc_fail(shell);
				free(shell->input);
				shell->input = str_mod;
			}
		}
		else
			i++;
	}
}
