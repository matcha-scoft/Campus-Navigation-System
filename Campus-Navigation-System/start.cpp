//
//  start.cpp
//  Campus Navigation System
//
//  Created by 冯勇鑫 on 2021/4/22.
//

#include "main.hpp"
using namespace std;

void StartSystem(vector <Node> & node_one, vector <Edge> & edge_one, vector <Node> & node_two, vector <Edge> & edge_two, Node & user) {
    string input;
    int quit_flag = 1;
    printf("************校园导览系统************\n");
    printf("**        输入1进入导航系统       **\n");
    printf("**        输入2进入查询系统       **\n");
    printf("**          输入0退出系统         **\n");
    printf("**  模拟用户起始位置为校区二南门  **\n");
    printf("************************************\n");
    printf("请输入：");
    while(quit_flag && cin >> input) {
        if (input.size() > 1) {
            printf("非法输入!请重新输入\n");
        }
        else {
            switch (input[0]) {
                case '1':
                    Navigation(node_one, edge_one, node_two, edge_two, user);
                    break;
                case '2':
                    if (user.campus_num == 1) {
                        Inquire(user, node_one, edge_one);
                    }
                    else {
                        Inquire(user, node_two, edge_two);
                    }
                    break;
                case '0':
                    printf("退出系统。\n");
                    quit_flag = 0;
                    continue;
                    break;
                default:
                    printf("非法输入!请重新输入\n");
                    break;
            }
        }
        printf("************校园导览系统************\n");
        printf("**        输入1进入导航系统       **\n");
        printf("**        输入2进入查询系统       **\n");
        printf("**          输入0退出系统         **\n");
        printf("**  模拟用户起始位置为校区二南门  **\n");
        printf("************************************\n");
        printf("请输入：");
        printf("请输入：");
    }
}
