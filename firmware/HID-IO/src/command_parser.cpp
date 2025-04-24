// Contents of command_parser.cpp

#include "command_parser.h"
#include "rgb_control.h"
#include <Arduino.h>
#include <string.h>

void parse_command(const char* cmd) {
  char buffer[64];
  strncpy(buffer, cmd, sizeof(buffer));
  buffer[sizeof(buffer) - 1] = '\0';

  char* token = strtok(buffer, " \t\r\n");
  if (!token) return;

  if (strcmp(token, "set") == 0) {
    token = strtok(NULL, " \t\r\n");
    if (!token) return;

    const NamedColor* color = find_named_color(token);
    if (color) {
      rgb_set(color->r, color->g, color->b);
      return;
    }

    // Try RGB values instead
    int r = atoi(token);
    int g = atoi(strtok(NULL, " \t\r\n"));
    int b = atoi(strtok(NULL, " \t\r\n"));
    rgb_set(r, g, b);
  }

  else if (strcmp(token, "off") == 0) {
    rgb_off();
  }

  else if (strcmp(token, "blink") == 0) {
    token = strtok(NULL, " \t\r\n");
    if (!token) return;

    const NamedColor* color = find_named_color(token);
    if (color) {
      int interval = atoi(strtok(NULL, " \t\r\n"));
      rgb_blink(color->r, color->g, color->b, interval);
      return;
    }

    // Try RGB values + interval
    int r = atoi(token);
    int g = atoi(strtok(NULL, " \t\r\n"));
    int b = atoi(strtok(NULL, " \t\r\n"));
    int interval = atoi(strtok(NULL, " \t\r\n"));
    rgb_blink(r, g, b, interval);
  }

  else if (strcmp(token, "breathe") == 0) {
    token = strtok(NULL, " \t\r\n");
    if (!token) return;

    const NamedColor* color = find_named_color(token);
    if (color) {
      int cycle = atoi(strtok(NULL, " \t\r\n"));
      rgb_breathe(color->r, color->g, color->b, cycle);
      return;
    }

    // Try RGB values + cycle
    int r = atoi(token);
    int g = atoi(strtok(NULL, " \t\r\n"));
    int b = atoi(strtok(NULL, " \t\r\n"));
    int cycle = atoi(strtok(NULL, " \t\r\n"));
    rgb_breathe(r, g, b, cycle);
  }

  else if (strcmp(token, "brightness") == 0) {
    int level = atoi(strtok(NULL, " \t\r\n"));
    rgb_set_brightness(level);
  }
}
