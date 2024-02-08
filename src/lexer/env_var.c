/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:39:29 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/08 14:25:58 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*copy_env_var(char *old_str, int i, char *envp, int len_var)
{
	char	*new_str;
	int		len_envp;
	int		len;

	len_envp = ft_strlen(envp + len_var + 1);
	len = i;
	len += len_envp;
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, old_str, i + 1);
	ft_strlcpy(new_str + i, envp + len_var + 1, len_envp + 1);
	return (new_str);
}


void	get_env_vars(t_data *shell)
{
	char	*str_mod;
	int		len;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	len = 0;
	while (shell->input[i])
	{
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
				shell->error = env_var_not_found;
				return ;
			}
		}
		else
			i++;
	}
}
