/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:36:35 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/20 13:21:17 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_single_quotes(t_data *shell, int i)
{
	if (shell->input[i] == '\'')
	{
		i++;
		while (shell->input[i] && shell->input[i] != '\'')
			i++;
		if (shell->input[i] == '\'')
			i++;
	}
	return (i);
}

char	*remove_env_var(t_data *shell, int i, int len_var)
{
	char	*new_str;
	int		len;

	len = ft_strlen(shell->input) - len_var;
	new_str = safe_malloc(sizeof(char) * (len + 2), shell);
	ft_strlcpy(new_str, shell->input, i);
	ft_strlcpy(new_str + i - 1, "\"\"", 3);
	ft_strlcpy(new_str + i + 1, shell->input + i + len_var, len - i + 1);
	return (new_str);
}

char	*add_env_var(t_data *shell, int j, int i, int len_var)
{
	char	*new_str;
	int		len_envp;
	int		size;

	len_envp = ft_strlen(shell->envp[j] + len_var + 1);
	size = ft_strlen(shell->input);
	size -= len_var - 1;
	size += len_envp;
	new_str = safe_malloc(sizeof(char) * (size + 1), shell);
	ft_strlcpy(new_str, shell->input, i + 1);
	ft_strlcpy(new_str + i, shell->envp[j] + len_var + 1, len_envp + 1);
	ft_strlcpy(new_str + i + len_envp,
		shell->input + i + len_var + 1, size - i - len_envp + 1);
	return (new_str);
}

char	*search_env_var(t_data *shell, int i, int len_var)
{
	char	*new_str;
	int		j;

	j = 0;
	new_str = NULL;
	while (shell->envp[j])
	{
		if (!ft_strncmp(&shell->input[i], shell->envp[j], len_var))
		{
			if (!ft_strncmp(shell->envp[j] + len_var, "=", 1))
				new_str = add_env_var(shell, j, i - 1, len_var);
		}
		j++;
	}
	return (new_str);
}

void	expansion_env_var(t_data *shell, int i)
{
	char	*new_str;
	int		len_var;

	len_var = 0;
	new_str = NULL;
	while (shell->input[i + len_var] && shell->input[i + len_var] != ' '
		&& shell->input[i + len_var] != '\"')
		len_var++;
	new_str = search_env_var(shell, i, len_var);
	if (!new_str)
		new_str = remove_env_var(shell, i, len_var);
	free(shell->input);
	shell->input = new_str;
}
