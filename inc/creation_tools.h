#ifndef CREATION_TOOLS_H_
# define CREATION_TOOLS_H_

# include "boolean.h"
# include "grimly_gen.h"

void	create_bordures(struct s_map *map);
void	full_walls(struct s_map *map);
void	draw_line(struct s_map *map, coord begin, coord end);
bool	is_in_map(struct s_map *map, coord pos);

#endif /* !CREATION_TOOLS_H_ */

