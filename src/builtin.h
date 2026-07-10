#ifndef BUILTIN_H
#define BUILTIN_H

#include "parser.h"

bool isBuiltin(Command &command);

void executeBuiltin(Command &command);

#endif