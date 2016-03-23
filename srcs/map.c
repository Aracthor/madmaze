#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "display.h"
#include "map.h"
#include "mooves.h"

static int	create_file(char *name, char *data)
{
  int		fd;

  fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 00644);

  if (write(fd, data, strlen(data)) != (int)strlen(data))
    return (1);
return (0);
}

static char	*empl_data(struct s_map *map)
{
  coord		pos;
  char		*data;
  char		*line;

  data = malloc(sizeof(char) * (map->longer + 1) * (map->larger + 1));
  line = malloc(sizeof(char) * map->longer + 1);

  sprintf(data, "%d:%d\n", map->longer, map->larger);
  for (pos.y = 0; pos.y < map->larger; ++pos.y)
  {
    for (pos.x = 0; pos.x < map->longer; ++pos.x)
       switch(map->cases[pos.y][pos.x])
   {
       case (empty):
       line[pos.x] = ' ';
       break;
       case (wall):
       line[pos.x] = '*';
       break;
       case (begin):
       line[pos.x] = '1';
       break;
       case (end):
       line[pos.x] = '2';
       break;
   }
   line[pos.x] = '\0';
   strcat(data, line);
   strcat(data, "\n");
}
free(line);

return (data);
}

int		create_map(struct s_params *params)
{
  struct s_map	map;
  int		i;
  int		return_value;
  char		*data;

  map.longer = params->longer;
  map.larger = params->larger;
  map.cases = malloc(sizeof(enum e_case *) * map.larger);
  for (i = 0; i < map.larger; ++i)
    map.cases[i] = malloc(sizeof(enum e_case) * map.longer);

return_value = params->creator(&map, params);

if (return_value == 0)
{
    if (params->display)
    {
      display_map(&map, NULL, NULL);
  }
  data = empl_data(&map);
  return_value = create_file(params->name, data);
  free(data);
}

destroy_map(&map);
return (return_value);
}

bool	map_is_empty(struct s_map *map)
{
  coord	pos;
  bool	empty;

  empty = true;

  for (pos.y = 1; empty == true && pos.y < map->larger - 1; ++pos.y)
    for (pos.x = 1; empty == true && pos.x < map->larger - 1; ++pos.x)
      if (MAP_CASE(map, pos) == wall)
         empty = false;

     return (empty);
 }

 bool	is_surrounded(struct s_map *map, coord pos)
 {
    coord	mooves[MOOVES_NBR];
    coord	new_pos;
    int	i;
    bool	surrounded = true;

    empl_mooves_tab(mooves);

    for (i = 0; i < MOOVES_NBR; ++i)
    {
      new_pos = coord_sum(pos, mooves[i]);
      if (IS_IN_MAP(map, new_pos) && MAP_CASE(map, new_pos) == wall)
        surrounded = false;
}

return (surrounded);
}

void	destroy_map(struct s_map *map)
{
    int	i;

    for (i = 0; i < map->larger; ++i)
      free(map->cases[i]);
  free(map->cases);
}

