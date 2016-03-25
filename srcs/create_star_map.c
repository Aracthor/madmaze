#include <stdlib.h>

#include "create_star_map.h"
#include "creation_tools.h"
#include "display.h"
#include "map.h"

int			create_star_map(struct s_map *map, void *params_void)
{
  struct s_params	*params;
  coord			pos;
  int			i;

  params = (struct s_params *)params_void;
  create_bordures(map);

  for (pos.y = 1; pos.y < map->height - 1; ++pos.y)
    for (pos.x = 1; pos.x < map->width - 1; ++pos.x)
      {
	map->cases[pos.y][pos.x] =
	(random() % 100 + 1 > params->creator_params.stars_percentage ?
	 empty : wall);
	if (params->see)
	  display_map(map, &pos, NULL);
      }

  for (i = 0; i < params->begins; ++i)
    {
      pos = coordonne(random() % (map->width - 2) + 1, random() % (map->height - 2) + 1);
      if (MAP_CASE(map, pos) == empty || MAP_CASE(map, pos) == wall)
	MAP_CASE(map, pos) = begin;
      else
	--i;
    }
  for (i = 0; i < params->ends; ++i)
    {
      pos = coordonne(random() % (map->width - 2) + 1, random() % (map->height - 2) + 1);
      if (MAP_CASE(map, pos) == empty || MAP_CASE(map, pos) == wall)
	MAP_CASE(map, pos) = end;
      else
	--i;
    }

  return (0);
}

