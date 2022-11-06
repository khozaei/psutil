/*
 * Copyright (c) 2022, Amin Khozaei <amin.khozaei@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include <stdint.h>

#define DEFAULT_BUFFER_LEN 1024

struct process {
  char *command;
  char *error_message;
  char *output;
  uint32_t error_len;
  uint32_t output_len;
};

typedef struct process Process;

Process *process_new(const char *command, uint32_t error_len,
                     uint32_t output_len);

#define process_new_default(CMD)                                               \
  process_new(CMD, DEFAULT_BUFFER_LEN, DEFAULT_BUFFER_LEN);

void process_destroy(Process *process);
int process_set_path(const unsigned int path_count, ...);

void process_set_command(Process *process, const char *command);
int process_execute(Process *process, const unsigned int arg_count, ...);
