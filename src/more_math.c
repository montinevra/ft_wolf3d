#include "more_math.h"
#include <stdio.h>																//debug

t_vec	add_vector(t_vec a, double dir, double mag)
{
	t_vec	c;
	double	ax;
	double	bx;
	double	ay;
	double	by;

	ax = cos(a.dir) * a.mag;
	ay = sin(a.dir) * a.mag;
	bx = cos(dir) * mag;
	by = sin(dir) * mag;
	c.dir = atan2(ay + by, ax + bx);
	c.mag = hypot(ax + bx, ay + by);
	return (c);
}
