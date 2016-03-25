#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "create_islands_map.h"
#include "creation_tools.h"
#include "display.h"
#include "island.h"
#include "map.h"
#include "mooves.h"

static void		add_an_island(struct s_map *map, coord pos, int size,
				      bool display, enum e_case case_type)
{
  struct s_island	island;
  coord			mooves[MOOVES_NBR];
  coord			beach_pos;
  int			i;

  empl_mooves_tab(mooves);

  create_island(map, &island, pos, case_type);
  if (display)
    display_map(map, &pos, NULL);
  for (i = 1; island.beach != NULL && i < size; ++i)
    {
      do
      {
	beach_pos = get_random_beach(island.beach);
      } while (is_surrounded(map, beach_pos));

      do
      {
	pos = coord_sum(beach_pos, mooves[random() % 4]);
      } while (!IS_IN_MAP(map, pos) || MAP_CASE(map, pos) != wall);
      if (display)
	display_map(map, &beach_pos, &pos);
      island.beach = add_case_to_beach(map, island.beach, pos);

    }
  destroy_island(&island);
}

int			create_islands_map(struct s_map *map,
					   void *params_void)
{
  struct s_params	*params;
  struct s_coord_list	*islands;
  coord			pos;
  enum e_case		case_type;
  int			islands_nbr;
  int			return_value = 0;

  params = (struct s_params *)params_void;
  full_walls(map);
  islands = NULL;
  if (params->creator_params.islands.number < params->begins + params->ends)
    {
      write(2, NEED_MORE_ISLANDS_MSG, strlen(NEED_MORE_ISLANDS_MSG));
      return_value = 1;
    }
  for (islands_nbr = 0;
       return_value == 0 && islands_nbr < params->creator_params.islands.number;
       ++islands_nbr)
    {
      do
      {
	pos = coordonne(random() % (map->width - 2) + 1,
			random() % (map->height - 2) + 1);
      } while (MAP_CASE(map, pos) != wall || is_surrounded(map, pos));
      islands = add_coord_to_list(islands, pos);
      if (islands_nbr != 0)
        draw_line(map, pos, islands->next->pos);

      if (islands_nbr == 0)
	case_type = begin;
      else if (islands_nbr == params->creator_params.islands.number - 1)
	case_type = end;
      else
	{
	  case_type = empty;
	  if (params->begins > 1 &&
	      random() % (params->creator_params.islands.number - islands_nbr)
	      < params->begins)
	    {
	      --params->begins;
	      case_type = begin;
	    }
	  else if (params->ends > 1 &&
	      random() % (params->creator_params.islands.number - islands_nbr)
	      < params->ends)
	    {
	      --params->ends;
	      case_type = end;
	    }
	}
      add_an_island(map, pos, params->creator_params.islands.size,
		    params->see, case_type);

      if (map_is_empty(map) && case_type != end)
	{
	  islands_nbr = params->creator_params.islands.number;
	  write(2, EMPTY_MAP_MSG, strlen(EMPTY_MAP_MSG));
	  return_value = 1;
	}
    }

  destroy_coord_list(islands);
  return (return_value);
}

