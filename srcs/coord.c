#include <stdlib.h>

#include "coord.h"

coord	coordonne(int x, int y)
{
  coord	coords;

  coords.x = x;
  coords.y = y;
  return (coords);
}

coord	coord_sum(coord a, coord b)
{
  coord	sum;

  sum.x = a.x + b.x;
  sum.y = a.y + b.y;

  return (sum);
}

coord	coord_sub(coord a, coord b)
{
  coord	sum;

  sum.x = a.x - b.x;
  sum.y = a.y - b.y;

  return (sum);
}

int	coord_distance(coord a, coord b)
{
  return (abs(a.x - b.x) + abs(a.y - b.y));
}

