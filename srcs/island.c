#include <stdlib.h>

#include "island.h"
#include "map.h"

void	create_island(struct s_map *map, struct s_island *island,
		      coord pos, enum e_case case_type)
{
  island->size = 1;
  island->pos = pos;
  island->beach = add_case_to_beach(map, NULL, pos);
  MAP_CASE(map, pos) = case_type;
}

void	destroy_island(struct s_island *island)
{
  destroy_coord_list(island->beach);
}

