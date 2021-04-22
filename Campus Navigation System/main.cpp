//
//  main.cpp
//  Campus Navigation System
//
//  Created by 冯勇鑫 on 2021/3/21.
//
#include "main.hpp"
using namespace std;

int main(void) {
    Clock my_clock;                                                  //时钟
    vector <Node> node_one;                                          //校区一的节点建筑
    vector <Node> node_two;                                          //校区二的节点建筑
    vector <Edge> edge_one;                                          //校区一的道路
    vector <Edge> edge_two;                                          //校区二的道路
    Node user;                                                       //保存用户信息
    InitUser(node_two, edge_two, user);                              //用户初始化
    InitOne(node_one, edge_one);                                     //校区一初始化
    InitTwo(node_two, edge_two);                                     //校区二初始化
    StartSystem(node_one, edge_one, node_two, edge_two, user);       //系统启动
    return 0;
}
