/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 16:19:46 by pvan-erp          #+#    #+#             */
/*   Updated: 2016/09/28 16:19:47 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_words(char const *s, char c)
{
	int i;
	int words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] && !(s[i] == c))
				i++;
			words++;
		}
		else
			i++;
	}
	return (words);
}

static void		ssplit(char const *s, char c, size_t wd_ct, char **split)
{
	size_t	i;
	size_t	wd;
	size_t	k;

	i = 0;
	wd = 0;
	while (s[i] && wd < wd_ct)
	{
		if (s[i] != c)
		{
			k = 0;
			while (s[i] != c && s[i])
			{
				i++;
				k++;
			}
			split[wd] = ft_strsub(s, i - k, k);
			wd++;
		}
		else
			i++;
	}
	split[wd] = NULL;
}

char			**ft_strsplit(char const *s, char c)
{
	char	**split;
	size_t	wd_ct;

	if (!s)
		return (NULL);
	wd_ct = get_words(s, c);
	if (!(split = (char **)malloc(sizeof(char *) * (wd_ct + 1))))
		return (NULL);
	ssplit(s, c, wd_ct, split);
	return (split);
}
