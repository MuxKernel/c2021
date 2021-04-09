//
// Created by mux on 2021-04-07.
//

#include "Game.h"
#include <vector>
#include <cmath>

#define DEPTH 8
//
//float AI_put_piece(Board *board) {
//    if (board->m_current_player == sys) { // 如果本该是AI操作的回合变成玩家操作
//        return 0; // 异常
//    }
//
//
//}


void AI_put_piece_stimulatly(Board *board, Point point) {
    int current_chess = board->m_current_player;
    board->m_map[point.row][point.con].key = board->player_chess[current_chess]; // 在地图上记录下棋
    board->Current_Zobrist ^= board->m_map[point.row][point.con].chess_Zobrist[current_chess]; // 异或Zobrist值
}

//int score_of_a_point(Board *board, int depth = DEPTH) {
//    vector<Point> *possible_points = find_possible_solutions(board);
//    vector<Point>::iterator it;//声明一个迭代器，来访问vector容器，作用：遍历或者指向vector容器的元素
//    Board stimulate_board; // 复制一个棋盘用来模拟 使用空构造方法
//    // 对于每一种可能的下法 （如果第一次进入这个函数，那么这是决策树第一层）
//    for (it = possible_points->begin(); it != possible_points->end(); it++) {
//        depth--;
//        stimulate_board = *board;
//        AI_put_piece_stimulatly(board, *it); // 模拟下棋
//        //TODO:尝试使用递归的方法解决下棋问题
//        score_of_a_point(board, depth);
//
//    }
//}

int estimate_score_of_board(Board *board) {
    // 遍历地图
    Board stimulate_board = *board; // 复制一个棋盘用来模拟 使用空构造方法
    Board *p_stimulate_board = &stimulate_board; // 使用指针动态更新棋盘
    int total_score = 0;
    int direction_score;
    for (int row = 5; row < 16; ++row) { // 从第5行/列开始评估 可以扫到整个棋盘
        for (int con = 5; con < 16; ++con) {
            if (stimulate_board.m_map[row][con].key) { // 如果有棋
                for (int direction = up; direction <= right_down; ++direction) { // 转半圈
                    direction_score = 0;
                    direction_score += estimate_score_of_a_point(p_stimulate_board, stimulate_board.m_map[row][con],
                                                                 direction);
                    direction_score += estimate_score_of_a_point(p_stimulate_board, stimulate_board.m_map[row][con],
                                                                 -direction); // 反方向再来一次
                    total_score += (int) pow(10, direction_score);

                }
                stimulate_board.m_map[row][con].key = 0; // 当前位置也重置为空
            }
        }
    }
    return total_score / 4; // 四个方向
}

int estimate_score_of_a_point(Board *board, Point point, int direction) {
    int score = 1; // 这个点的得分
    int now_key = point.key;
    for (int i = 0; i < 5; ++i) {
        Point *next_point = board->point_on_a_direction(point, direction);
        if (next_point == nullptr) { // 越界就不用再检索了
            break;
        }
        if (next_point->key != now_key) { // 如果不能连在一起
            if (next_point->key != 0) { // 如果是步死棋
                score--;
            }
            break;
        } else { // 如果能连在一起
            next_point->key = 0; // 不重复计数 重置为空
            score++;
            point = *next_point; // 以此为基础继续搜索
        }

    }
    return score;
}

//
//Point find_best_point(Board *board, int player) {
//    vector<Point> *possible_points = find_possible_solutions(board);
//    vector<Point>::iterator it;//声明一个迭代器，来访问vector容器，作用：遍历或者指向vector容器的元素
//    Board stimulate_board; // 复制一个棋盘用来模拟 使用空构造方法
//    // 对于每一种可能的下法 （如果第一次进入这个函数，那么这是决策树第一层）
//    for (it = possible_points->begin(); it != possible_points->end(); it++) {
//        stimulate_board = *board;
//        AI_put_piece_stimulatly(board, *it); // 模拟下棋
//        //TODO:尝试使用递归的方法解决下棋问题
//
//    }
//}

