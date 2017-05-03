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
	// printf("ax = %f\n", ax);
	ay = sin(a.dir) * a.mag;
	// printf("ay = %f\n", ay);
	bx = cos(dir) * mag;
	// printf("bx = %f\n", bx);
	by = sin(dir) * mag;
	// printf("by = %f\n", by);
	c.dir = atan2(ay + by, ax + bx);
	c.mag = hypot(ax + bx, ay + by);
	return (c);
}
