//
// Created by mux on 2021-04-06.
//
#include <stdio.h>
#include "Board/Board.h"
#include "Game/Game.h"
#include "Interaction/Console.h"


// 主函数
//int main(){
//    Board board(user),*p_board;
//    p_board = &board;
//    int row,con;
//    do{
//        scanf("%d %d",&row,&con);
//        // TODO:合法性判断
//        Input_parser(p_board,row,con);
//        Print_Board_to_Console(p_board);
//        float winning_rate = AI_put_piece(p_board);
//        Print_Board_to_Console(p_board);
//        // 输出胜率
//        printf("此时AI胜率为：%f\n",winning_rate);
//    } while (!victory(p_board));
//}


int main() {
    Board board(user), *p_board;
    p_board = &board;
    int row, con;
    int score;
    do {
        scanf("%d %d", &row, &con);
        // TODO:合法性判断
        Input_parser(p_board, row, con);
        Print_Board_to_Console(p_board);
        score = estimate_score_of_board(p_board);
        // 输出胜率
        printf("score:%d\n", score);
        p_board->change_current_player();
    } while (1);
}
