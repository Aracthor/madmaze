#ifndef MAP_H_
# define MAP_H_

# include "params.h"

# define IS_IN_MAP(map, pos)		(pos.x >= 1 && pos.y >= 1 &&	\
					 pos.x < map->width - 1 &&	\
					 pos.y < map->height - 1)

# define MAP_CASE(map, pos)		(map->cases[pos.y][pos.x])

int	create_map(struct s_params *params);
bool	map_is_empty(struct s_map *map);
bool	is_surrounded(struct s_map *map, coord pos);
void	destroy_map(struct s_map *map);

#endif /* MAP_H_ */

