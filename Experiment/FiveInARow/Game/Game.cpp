//
// Created by mux on 2021-04-07.
//

#include "Game.h"
#include <vector>
#include <cmath>
#include <algorithm>

float AI_put_piece(Board *board) {
    if (board->m_current_player == user) { // 如果本该是AI操作的回合变成玩家操作
        return 0; // 异常
    }
    Point best_solution_point = find_best_point(board);
    if (board->put_piece(best_solution_point)) { // 成功放置
//        return estimate_winning_possibility_to_system(board); TODO:写这个
        return 57.9;
    } else { // 失败
        return 0.0;
    }
}


void AI_put_piece_stimulatly(Board *board, Point point) {
    int current_chess = board->m_current_player;
    board->m_map[point.row][point.con].key = board->player_chess[current_chess]; // 在地图上记录下棋
    board->Current_Zobrist ^= board->m_map[point.row][point.con].chess_Zobrist[current_chess]; // 异或Zobrist值
    board->change_current_player();
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


Point find_best_point(Board *board, int depth) {
    // 留存一份当前玩家是谁 另一份被更改
    int current_player = board->m_current_player;
    vector<Point> possible_points = find_possible_solutions(board);
    vector<Point>::iterator it;//声明一个迭代器，来访问vector容器，作用：遍历或者指向vector容器的元素
    Board stimulate_board; // 复制一个棋盘用来模拟 使用空构造方法
    // 对于每一种可能的下法 （如果第一次进入这个函数，那么这是决策树第一层）
    vector<int> score_point;
    int layer_depth;
    for (it = possible_points.begin(); it != possible_points.end(); it++) { // 触发递归
        layer_depth = depth;
        stimulate_board = *board; // 复制棋盘
        AI_put_piece_stimulatly(&stimulate_board, *it); // 模拟下棋
        layer_depth--;
        int score_of_the_point = score_of_a_point(&stimulate_board, layer_depth);
        score_point.push_back(score_of_the_point);
    }
    // max-min
    if (current_player == sys) {
        auto biggest = std::max_element(std::begin(score_point), std::end(score_point));
        //TODO:返回权重值
//        std::cout << "Max element is " << *biggest<< " at position " << std::distance(std::begin(v), biggest) << std::endl;
        return possible_points[std::distance(std::begin(score_point), biggest)]; // 强制解包 可能会有bug。。
    } else {
        auto smallest = std::min_element(std::begin(score_point), std::end(score_point));
        //TODO:返回权重值
//        std::cout << "Max element is " << *biggest<< " at position " << std::distance(std::begin(v), biggest) << std::endl;
        return possible_points[std::distance(std::begin(score_point), smallest)]; // 强制解包 可能会有bug。。
    }
}

// 分数越大越好
int score_of_a_point(Board *board, int depth) {
    if (depth == 0) { // 如果到了最底层 该计算每一种棋盘的分值了。。。
        return estimate_score_of_board(board);
    } else {
        // 留存一份当前玩家是谁 另一份被更改
        int current_player = board->m_current_player;
        vector<Point> possible_points = find_possible_solutions(board);
        vector<Point>::iterator it;//声明一个迭代器，来访问vector容器，作用：遍历或者指向vector容器的元素
        Board stimulate_board; // 复制一个棋盘用来模拟 使用空构造方法
        // 对于每一种可能的下法
        vector<int> score_point;
        int layer_depth;
        for (it = possible_points.begin(); it != possible_points.end(); it++) { // 触发递归
            layer_depth = depth;
            stimulate_board = *board; // 复制棋盘
            AI_put_piece_stimulatly(&stimulate_board, *it); // 模拟下棋
            layer_depth--;
            int score_of_the_point = score_of_a_point(&stimulate_board, layer_depth);
            score_point.push_back(score_of_the_point);
        }
        // max-min
        if (current_player == sys) {
            auto biggest = std::max_element(std::begin(score_point), std::end(score_point));
            //TODO:返回权重值
//        std::cout << "Max element is " << *biggest<< " at position " << std::distance(std::begin(v), biggest) << std::endl;
            return *biggest;
        } else {
            auto smallest = std::min_element(std::begin(score_point), std::end(score_point));
            //TODO:返回权重值
//        std::cout << "Max element is " << *biggest<< " at position " << std::distance(std::begin(v), biggest) << std::endl;
            return *smallest;
        }
    }
}

vector<Point> find_possible_solutions(Board *board) {
    //TODO:检查所有返回指针的函数 是否返回了局部变量
    vector<Point> possible_points;
    // 目前策略：每一个没有子并且不在边界5格范围内的点都是可用点
    for (int row = 5; row < 16; ++row) { // 从第5行/列开始评估 可以扫到整个棋盘
        for (int con = 5; con < 16; ++con) {
            if (!board->m_map[row][con].key) { // 如果无棋
                possible_points.push_back(board->m_map[row][con]);
            }
        }
    }
    return possible_points;
}

int victory(Board *board) {
    for (int row = 5; row < 16; ++row) { // 从第5行/列开始评估 可以扫到整个棋盘
        for (int con = 5; con < 16; ++con) {
            if (board->m_map[row][con].key) { // 如果有棋
                for (int direction = up; direction <= right_down; ++direction) { // 转半圈
                    Point point = board->m_map[row][con];
                    int now_key = point.key;
                    for (int i = 0; i < 5; ++i) {
                        Point *next_point = board->point_on_a_direction(point, direction);
                        if (next_point == nullptr) { // 越界就不用再检索了
                            break;
                        }
                        if (next_point->key != now_key) { // 如果不能连在一起
                            break;
                        } else { // 如果能连在一起
                            point = *next_point; // 以此为基础继续搜索
                            if (i == 4) {
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

