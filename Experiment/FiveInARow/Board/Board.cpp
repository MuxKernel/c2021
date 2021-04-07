//
// Created by mux on 2021-04-07.
//

#include "Board.h"
#include "../randomc/randomc.h"
#include <ctime>

#define RANDOM_MAX 1000

Board::Board(int current, char *name) {
    this->m_name = name;
//    this->m_map = map; 暂时不支持下残局
    this->m_current_player = current;
    // 记录每个玩家拿的是什么棋
    if(current == system){// 黑棋先
        this->player_chess[user] = black;
        this->player_chess[system] = white;
    }else{
        this->player_chess[user] = white;
        this->player_chess[system] = black;
    }

    // 初始化棋局
    for (int row = 1; row < 16; ++row) {
        for (int con = 1; con < 16; ++con) {
            this->m_map[row][con].key = 0; //清空棋盘
        }
    }

    // 初始化Zobrist表
    int seed = (int) time(nullptr); // 随机数生成种子
    CRandomMersenne RanGen(seed);
    for (int row = 1; row < 16; ++row) {
        for (int con = 1; con < 16; ++con) {
            this->m_map[row][con].chess_Zobrist[black] = RanGen.IRandom(0, RANDOM_MAX);
            this->m_map[row][con].chess_Zobrist[white] = RanGen.IRandom(0, RANDOM_MAX);
        }
    }
    // 初始化Zobrist值
    this->Current_Zobrist = RanGen.IRandom(0, RANDOM_MAX);
}

int Board::put_piece(int row, int con) {
    // 当前操作者从board中读取
    int current_chess = this->m_current_player;
    if (this->m_current_player == system){ // 如果本该是玩家操作的回合变成AI操作
        return 0; // 异常
    }
    this->m_map[row][con].key = this->player_chess[current_chess]; // 在地图上记录下棋
    this->Current_Zobrist ^= this->m_map[row][con].chess_Zobrist[current_chess]; // 异或Zobrist值
    this->m_user_operations.push_back(m_map[row][con]); // 记录操作
    this->m_current_player = 1 - this->m_current_player; // 切换现在下棋的人
    return 1; // 成功
}



