#include "creation_tools.h"
#include "map.h"

void	create_bordures(struct s_map *map)
{
  coord	pos;

  for (pos.x = 0; pos.x < map->longer; ++pos.x)
    {
      map->cases[0][pos.x] = wall;
      map->cases[map->larger - 1][pos.x] = wall;
    }

  for (pos.y = 0; pos.y < map->larger; ++pos.y)
    {
      map->cases[pos.y][0] = wall;
      map->cases[pos.y][map->longer - 1] = wall;
    }
}

void	full_walls(struct s_map *map)
{
  coord	pos;

  for (pos.x = 0; pos.x < map->longer; ++pos.x)
    for (pos.y = 0; pos.y < map->larger; ++pos.y)
      map->cases[pos.y][pos.x] = wall;
}

void	draw_line(struct s_map *map, coord begin, coord end)
{
  coord	pos;
  float	moove_x;
  float	moove_y;
  float	pos_x;
  float	pos_y;

  pos = begin;
  moove_x = (float)(end.x - begin.x) / (float)(coord_distance(begin, end));
  moove_y = (float)(end.y - begin.y) / (float)(coord_distance(begin, end));
  pos_x = pos.x;
  pos_y = pos.y;
  while (coord_distance(pos, end) > 1)
    {
      pos_x += moove_x;
      pos_y += moove_y;
      if ((int)pos_x != pos.x)
	{
	  pos.x = (int)pos_x;
	  if (MAP_CASE(map, pos) == wall)
	    MAP_CASE(map, pos) = empty;
	}
      if ((int)pos_y != pos.y)
	{
	  pos.y = (int)pos_y;
	  if (MAP_CASE(map, pos) == wall)
	    MAP_CASE(map, pos) = empty;
	}
    }
}

bool	is_in_map(struct s_map *map, coord pos)
{
  return (pos.x >= 0 && pos.y >= 0 &&
	  pos.x < map->longer && pos.y < map->larger);
}

