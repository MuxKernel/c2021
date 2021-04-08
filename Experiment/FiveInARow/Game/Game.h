//
// Created by mux on 2021-04-07.
//
#ifndef FIVEINAROW_GAME_H
#define FIVEINAROW_GAME_H

#include "../Board/Board.h"
#include <vector>


/**
 * 寻找可能的可以落子的点，去除明显不需要思考的点 即在这一层可能的落子位置
 * 其实是决策树的每一层
 * @param board
 * @return
 */
vector<Point> *find_possible_solutions(Board *board);

/**
 * 估计AI胜利概率（全局）
 * @param board
 * @return 0~1的float
 */
float estimate_winning_possibility_to_system(Board *board);

/**
 * 计算一个落子操作的得分（针对一个点）
 * @param board
 * @param point
 * @return
 */
int score_of_a_point(Board *board, int depth);

/**
 * 寻找此时AI赢面最大的地儿
 * @param board 棋面
 * @param depth 搜索深度
 * @param player 这一层是谁下棋
 * @return
 */
Point find_best_point(Board *board, int player, int depth);

/**
 * 检查此时是否有一方已经胜利
 * -1否 0 user 1 sys
 * @param board
 * @return
 */
int victory(Board *board);

/**
 * Ai下棋 返回这步棋的胜率
 * @param board
 * @return
 */
float AI_put_piece(Board *board);

/**
 * 模拟下棋操作 不记录到操作表中，使用复制的棋盘
 * @param board
 * @param row
 * @param con
 * @return
 */
int AI_put_piece_stimulatly(Board board, int row, int con);

/**
 * 模拟下棋操作 不记录到操作表中，使用复制的棋盘
 * @param board
 * @param row
 * @param con
 * @return
 */
int AI_put_piece_stimulatly(Board *board, Point point);


int estimate_score_of_board(Board *board);


int estimate_score_of_a_point(Board *board, Point point, int direction);

#endif //FIVEINAROW_GAME_H
