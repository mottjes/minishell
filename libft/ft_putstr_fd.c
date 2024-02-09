/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:31:57 by mottjes           #+#    #+#             */
/*   Updated: 2023/05/24 13:24:55 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Outputs the string ’s’ to the given file
descriptor
*/

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}

/*
int main(void)
{
	char s[] = "Hello World";
	int fd = 1;
	
	ft_putstr_fd(s, fd);
}
*/

/*
gcc ft_putstr_fd.c -Wall -Wextra -Werror
*/
