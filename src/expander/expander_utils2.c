/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:48:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/28 13:52:56 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_single_quotes(t_data *shell, int i)
{
	if (shell->input[i] == '\'')
	{
		i++;
		while (shell->input[i] != '\'')
			i++;
		if (shell->input[i] == '\'')
			i++;
	}
	return (i);
}

char	*search_env_var(t_data *shell, int i, int len)
{
	char	*str_mod;
	int		j;

	j = 0;
	str_mod = NULL;
	while (shell->envp[j])
	{
		if (!ft_strncmp(&shell->input[i], shell->envp[j], len))
		{
			if (!ft_strncmp(shell->envp[j] + len, "=", 1))
			{
				str_mod = copy_env_var(shell->input, i - 1,
						shell->envp[j], len);
				if (!str_mod)
					malloc_fail(shell);
			}
		}
		j++;
	}
	return (str_mod);
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
	ft_strlcpy(new_str + i + len_envp,
		old_str + i + len_var + 1, len - i - len_envp + 1);
	return (new_str);
}

char	*remove_env_var(t_data *shell, int i, int len_var)
{
	char	*new_str;
	int		len;

	len = ft_strlen(shell->input) - len_var;
	new_str = malloc(sizeof(char) * (len));
	if (!new_str)
		malloc_fail(shell);
	ft_strlcpy(new_str, shell->input, i);
	ft_strlcpy(new_str + i - 1, shell->input + i + len_var, len - i + 1);
	return (new_str);
}
