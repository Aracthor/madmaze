#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "creation_tools.h"
#include "create_laby_map.h"
#include "display.h"
#include "map.h"
#include "mooves.h"

static int	draw_hallway(struct s_map *map, coord *pos,
			     int empty_cases_max, bool display)
{
  coord		mooves[4];
  coord		moove;
  coord		new_pos;
  coord		old_pos;
  int		moove_max;
  int		i;
  int		new_empty_cases;

  empl_mooves_tab(mooves);
  moove = mooves[random() % 4];
  old_pos = *pos;
  new_empty_cases = 0;

  moove_max = -2;
  for (new_pos = *pos;
       is_in_map(map, new_pos);
       new_pos = coord_sum(new_pos, moove))
    ++moove_max;
  if (moove_max > 0)
    moove_max = random() % moove_max + 1;

  for (i = 0; i < moove_max && i <= empty_cases_max; ++i)
    {
      *pos = coord_sum(*pos, moove);
      if (map->cases[pos->y][pos->x] == wall)
	{
	  map->cases[pos->y][pos->x] = empty;
	  ++new_empty_cases;
	}
    }

  if (display)
    display_map(map, &old_pos, pos);

  return (new_empty_cases);
}

int			create_laby_map(struct s_map *map, void *params_void)
{
  struct s_params	*params;
  coord			pos;
  int			empty_cases;
  int			empty_number;
  int			i;
  int			return_value = 0;

  params = (struct s_params *)params_void;
  full_walls(map);
  empty_number = params->creator_params.empty_number;

  pos.x = random() % (map->width - 2) + 1;
  pos.y = random() % (map->height - 2) + 1;

  MAP_CASE(map, pos) = begin;
  empty_cases = 1;

  while (empty_cases < empty_number - 1)
    {
      empty_cases += draw_hallway(map, &pos,
				  empty_number - empty_cases, params->see);
    }

  if (empty_number < params->begins + params->ends + 1)
    {
      write(2, NEED_MORE_SPACE_MSG, strlen(NEED_MORE_SPACE_MSG));
      return_value = 0;
    }
  else if (MAP_CASE(map, pos) == begin)
    return_value = create_laby_map(map, params);
  else
    MAP_CASE(map, pos) = end;

  if (return_value == 0)
    {
      for (i = 1; i < params->begins; ++i)
	{
	  pos = coordonne(random() % map->width, random() % map->height);
	  if (MAP_CASE(map, pos) == empty)
	    MAP_CASE(map, pos) = begin;
	  else
	    --i;
	}
      for (i = 1; i < params->ends; ++i)
	{
	  pos = coordonne(random() % map->width, random() % map->height);
	  if (MAP_CASE(map, pos) == empty)
	    MAP_CASE(map, pos) = end;
	  else
	    --i;
	}
    }

  return (return_value);
}

