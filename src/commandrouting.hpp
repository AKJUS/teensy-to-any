#pragma once

#include <inttypes.h>
#include <stdio.h>

// Need to declare command router since it is used by the command_item struct;
class CommandRouter;

typedef struct command_item {
  const char *name;
  const char *description;
  const char *syntax;
  int (*func)(CommandRouter *cmd, int argc, const char **argv);
} command_item_t;

class CommandRouter {
public:
  int init(const command_item_t *commands, int buffer_size, int argv_max);
  int init_no_malloc(const command_item_t *commands, int buffer_size,
                     char *serial_buffer, int argv_max,
                     const char **argv_buffer);
  int help(const char *command_name = nullptr);
  int processSerialStream();
  int processString(const char *buffer);
  void cleanup();
  ~CommandRouter();

  char *buffer = nullptr; // Allow for terminating null byte
  int buffer_size = 0;

private:
  int route(int argc, const char **argv);

  const char **argv;
  int argv_max = 0;

  bool malloc_used = false;
  const command_item_t *command_list;
};

extern CommandRouter cmd;

int command_help_func(CommandRouter *cmd, int argc, const char **argv);
