//
// Created by mux on 2021-04-07.
//

#include "Game.h"
#include <vector>

float AI_put_piece(Board *board) {
    if (board->m_current_player == system) { // 如果本该是AI操作的回合变成玩家操作
        return 0; // 异常
    }

    vector<Point> *possible_points = find_possible_solutions(board);
    vector<Point>::iterator it;//声明一个迭代器，来访问vector容器，作用：遍历或者指向vector容器的元素
    Board stimulate_board; // 复制一个棋盘用来模拟 使用空构造方法
    // 对于每一种可能的下法 （如果第一次进入这个函数，那么这是决策树第一层）
    for (it = possible_points->begin(); it != possible_points->end(); it++) {
        stimulate_board = *board;
        AI_put_piece_stimulatly(board, *it); // 模拟下棋
        //TODO:尝试使用递归的方法解决下棋问题

    }
}


int AI_put_piece_stimulatly(Board *board, Point point) {
    int current_chess = board->m_current_player;
    board->m_map[point.row][point.con].key = board->player_chess[current_chess]; // 在地图上记录下棋
    board->Current_Zobrist ^= board->m_map[point.row][point.con].chess_Zobrist[current_chess]; // 异或Zobrist值
}