//
// Created by mux on 2021-04-07.
//
/**
 * 这个文件中定义与棋局有关的东西。。。
 */
#include<vector>

#ifndef FIVEINAROW_BOARD_H
#define FIVEINAROW_BOARD_H
using namespace std;

enum Player { // 人0 系统1
    user, system
};

enum chess { // 黑1 白2
    black = 1, white
};

enum directions {
    up = 1, up_right = 2, right = 3, right_down = 4, down = -1, down_left = -2, left = -3, left_up = -4
};

typedef struct {// 棋盘上的一个点
    int row;
    int con;
    int key; // 点上的棋子状态 0 无 1黑 2 白
    int chess_Zobrist[3]; // 记录每种棋子在每个位置上对应的Zobrist值
} Point;


class Board {
public: // 公共变量定义
    char *m_name{}; // 玩家姓名 unused
    Point m_map[16][16]{}; // 地图数组指针 二维数组 大小：15*15 会多出来一行一列的数据
    int m_current_player{}; // 记录现在是谁在操作
    int player_chess[2]{}; // 记录每个玩家的棋子是啥
    vector<Point> m_user_operations; // 记录用户操作的向量 <[row,con]>
    vector<Point> m_sys_operations;  // 记录系统操作的向量 <[row,con]>
    int Current_Zobrist{}; // 记录现在的Zobrist值
public: // 公共方法声明
    explicit Board(int current, char *name = nullptr); // 构造方法
    Board(); // 空构造方法
    /**
     * 下棋操作 成功1 失败0
     * @param row
     * @param con
     * @param player
     * @return
     */
    int put_piece(int row, int con);
    //TODO:悔棋
    /**
     * 注意：返回的是地址值，更改其值会对应棋盘的改变！
     * 以一个点为基础，返回一个方向上的点，若越界返回-1
     * @param direction
     * @return
     */
    Point *point_on_a_direction(Point point, int direction);
};


#endif //FIVEINAROW_BOARD_H
