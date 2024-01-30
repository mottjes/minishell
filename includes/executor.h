/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:52:05 by frbeyer           #+#    #+#             */
/*   Updated: 2024/01/29 15:38:58 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_data t_data;
typedef	struct s_cmd t_cmd;

typedef struct s_exec
{
    char    *output;
}   t_exec;

void	executor(t_data *shell);

#endif
