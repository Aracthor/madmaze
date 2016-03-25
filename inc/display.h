#ifndef DISPLAY_H_
# define DISPLAY_H_

# include "grimly_gen.h"

# define DISPLAY_USLEEP		(100000)

# define NEED_MORE_SPACE_MSG	("Need more space.\n")
# define EMPTY_MAP_MSG		("Too many holes : map is empty.\n")
# define NEED_MORE_ISLANDS_MSG	("You need more islands.\n")

void	display_map(struct s_map *map, coord *marked_pos, coord *second_pos);

#endif /* !DISPLAY_H_ */

