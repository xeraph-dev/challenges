#include "robot_simulator.h"

robot_status_t robot_create(robot_direction_t direction, int x, int y) {
  return (robot_status_t){direction, {x, y}};
}

void robot_move(robot_status_t *robot, const char *commands) {
  for (; *commands != '\0'; commands++)
    switch (*commands) {
    case 'R':
      robot->direction++;
      if (robot->direction == DIRECTION_MAX)
        robot->direction = DIRECTION_DEFAULT;
      break;
    case 'L':
      if (robot->direction == DIRECTION_DEFAULT)
        robot->direction = DIRECTION_MAX - 1;
      else
        robot->direction--;
      break;
    case 'A':
      switch (robot->direction) {
      case DIRECTION_NORTH:
        robot->position.y++;
        break;
      case DIRECTION_EAST:
        robot->position.x++;
        break;
      case DIRECTION_SOUTH:
        robot->position.y--;
        break;
      case DIRECTION_WEST:
        robot->position.x--;
        break;
      case DIRECTION_MAX:
        break;
      }
      break;
    }
}
