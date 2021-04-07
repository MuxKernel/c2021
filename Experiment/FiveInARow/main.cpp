//
// Created by mux on 2021-04-06.
//
#include <stdio.h>
#include "Board/Board.h"
#include "Game/Game.h"

// 主函数
int main(){
    Board board(user),*p_board;
    p_board = &board;
    int row,con;
    do{
        scanf("%d %d",&row,&con);
        // TODO:合法性判断
        p_board->put_piece(p_board,row,con);
        float winning_rate = AI_put_piece(p_board);
        // 输出胜率
    } while (!victory(p_board));
}