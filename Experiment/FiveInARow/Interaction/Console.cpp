//
// Created by mux on 2021-04-07.
//

#include "Console.h"
#include <stdio.h>

void Print_Board_to_Console(Board *board){
    for (int row = 1; row < 16; ++row) { // 行输出
        for (int con = 1; con < 16; ++con) { // 每一行中的列输出
            printf("%d",board->m_map[row][con].key);
        }
        printf("\n");
    }
}

int Input_parser(Board *board,int row,int con){
    return board->put_piece(row,con); // 其实就是封装了一层。。不过在使用其他输出方式的时候挺有用，毕竟是通用接口qw
}