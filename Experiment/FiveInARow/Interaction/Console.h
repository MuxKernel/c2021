//
// Created by mux on 2021-04-07.
//

#ifndef FIVEINAROW_CONSOLE_H
#define FIVEINAROW_CONSOLE_H

#include "../Board/Board.h"

void Print_Board_to_Console(Board *board);

int Input_parser(Board *board ,int row,int con);

void Print_sys_operations(Board *board);

void Print_user_operations(Board *board);
#endif //FIVEINAROW_CONSOLE_H
