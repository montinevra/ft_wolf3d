/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_math.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 16:22:36 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/05/07 16:42:50 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MORE_MATH_H
# define MORE_MATH_H
# include <math.h>
# define M_TAU 6.28318530717958623199592693708837032318115234375

typedef struct	s_vec
{
	float	mag;
	float	dir;
}				t_vec;

t_vec			add_vector(t_vec a, double dir, double mag);

#endif
