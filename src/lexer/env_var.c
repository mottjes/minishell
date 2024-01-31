/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:39:29 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/31 17:40:26 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*copy_env_var_in_str(char *old_str, int pos_in_str, char *envp, int len_var)
{
	char 	*new_str;
	int		len;
	int		len_envp;
	
	len_envp = ft_strlen(envp + len_var + 1);
	len = pos_in_str;
	len += len_envp;
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, old_str, pos_in_str + 1);
	ft_strlcpy(new_str + pos_in_str, envp + len_var + 1, len_envp + 1);
	return (new_str);
}

void	get_env_vars(t_data *shell)
{
	t_token *token;
	char	*str_mod;
	int		i;
	int		j;
	int		len_var;
	
	token = shell->token_list;
	
	while (token)
	{
		i = 0;
		j = 0;
		len_var = 0;
		str_mod = NULL;
		while (token->str[i])
		{
			if (token->str[i] == '\'')
			{
				i++;
				while (token->str[i] != '\'' && token->str[i])
					i++;
				if (token->str[i] == '\'')
					i++;
			}
			
			if (token->str[i] == '$')
			{
				i++;
				while (token->str[i + len_var] && token->str[i + len_var] != ' ')
					len_var++;
				while (shell->envp[j])
				{
					if (!ft_strncmp(&token->str[i], shell->envp[j], len_var))
					{
						if (!ft_strncmp(shell->envp[j] + len_var, "=", 1))
						{
							str_mod = copy_env_var_in_str(token->str, i - 1, shell->envp[j], len_var);
							if (!str_mod)
							{
								shell->error = malloc_failed;
								return ;
							}
							free(token->str);
							token->str = str_mod;
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
		token = token->next;
	}
}
