/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 03:40:48 by albernar          #+#    #+#             */
/*   Updated: 2024/12/01 19:23:48 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*build_prompt_with_home(const char *cwd, const char *home)
{
	size_t	size;
	size_t	color_size;
	size_t	path_size;
	char	*result;

	path_size = ft_strlen(cwd) - ft_strlen(home);
	color_size = ft_strlen(LIGHT_BLUE) + ft_strlen(RESET_COLOR);
	size = ft_strlen(cwd) - ft_strlen(home) + color_size + 4;
	result = lp_alloc(sizeof(char), size);
	ft_strcpy(result, LIGHT_BLUE);
	result[ft_strlen(LIGHT_BLUE)] = '~';
	ft_strcpy(result + ft_strlen(LIGHT_BLUE) + 1, cwd + ft_strlen(home));
	ft_strcpy(result + ft_strlen(LIGHT_BLUE) + 1 + path_size, RESET_COLOR);
	ft_strcpy(result + 1 + path_size + color_size, " ");
	return (result);
}

char	*build_prompt_without_home(const char *cwd)
{
	size_t	size;
	size_t	color_size;
	size_t	path_size;
	char	*result;

	path_size = ft_strlen(cwd);
	color_size = ft_strlen(LIGHT_BLUE) + ft_strlen(RESET_COLOR);
	size = ft_strlen(cwd) + color_size + 3;
	result = lp_alloc(sizeof(char), size);
	ft_strcpy(result, LIGHT_BLUE);
	ft_strcpy(result + ft_strlen(LIGHT_BLUE), cwd);
	ft_strcpy(result + ft_strlen(LIGHT_BLUE) + path_size, RESET_COLOR);
	ft_strcpy(result + color_size + path_size, " ");
	return (result);
}
