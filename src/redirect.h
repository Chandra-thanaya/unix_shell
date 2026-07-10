#ifndef REDIRECT_H
#define REDIRECT_H

#include "parser.h"

bool setupRedirection(Command &command);

void restoreRedirection();

#endif