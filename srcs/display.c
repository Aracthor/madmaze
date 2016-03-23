#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "color.h"
#include "display.h"
#include "map.h"

static void	empl_chars_tab(char *chars)
{
  chars[empty] = ' ';
  chars[wall] = '*';
  chars[begin] = '1';
  chars[end] = '2';
}

static char	*mark_case(char *display, int *pc, enum e_color color)
{
  display[(*pc)++] = 0x1B;
  display[(*pc)++] = '[';
  display[(*pc)++] = '4';
  display[(*pc)++] = '0' + color;
  display[(*pc)++] = 'm';

  return (display);
}

static char	*unmark_case(char *display, int *pc)
{
  display[(*pc)++] = 0x1B;
  display[(*pc)++] = '[';
  display[(*pc)++] = '0';
  display[(*pc)++] = 'm';

  return (display);
}

void	display_map(struct s_map *map, coord *marked_pos, coord *second_pos)
{
  coord	pos;
  int	pc;
  char	*display;
  char	chars[CASE_TYPES_NBR];

  empl_chars_tab(chars);

  pc = 0;
  display = malloc(sizeof(char) * ((map->longer + 1) * map->larger + 1 + 20));
  if (marked_pos != NULL)
    system("clear");

  for (pos.y = 0; pos.y < map->larger; ++pos.y)
    {
      for (pos.x = 0; pos.x < map->longer; ++pos.x)
	{
	  if (marked_pos != NULL && coord_distance(pos, *marked_pos) == 0)
	    display = mark_case(display, &pc, red);
	  else if (second_pos != NULL && coord_distance(pos, *second_pos) == 0)
	    display = mark_case(display, &pc, green);

	  display[pc++] = chars[MAP_CASE(map, pos)];
	  if ((marked_pos != NULL && coord_distance(pos, *marked_pos) == 0) ||
	      (second_pos != NULL && coord_distance(pos, *second_pos) == 0))
	    display = unmark_case(display, &pc);
	}
      display[pc++] = '\n';
    }

  display[pc] = '\0';
  printf("%d:%d\n%s", map->longer, map->larger, display);
  usleep(DISPLAY_USLEEP);
  free(display);
}

