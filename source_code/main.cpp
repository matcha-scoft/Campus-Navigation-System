#include "main.hpp"
using namespace std;

int main(void) {
    Clock my_clock;                                                  //时钟
    vector <Node> node_one;                                          //校区一的节点建筑
    vector <Node> node_two;                                          //校区二的节点建筑
    vector <Edge> edge_one;                                          //校区一的道路
    vector <Edge> edge_two;                                          //校区二的道路
    vector <Time> time_table;                                        //定点班车表
    Pos user;                                                        //保存用户信息
    //校区一初始化
    InitOne(node_one, edge_one);                 
    //校区二初始化                    
    InitTwo(node_two, edge_two);                                     
    //定点班车表初始化
    InitTimeTable(time_table);                                       
    //系统启动
    StartSystem(node_one, edge_one, node_two, edge_two, user, my_clock, time_table);
    return 0;
}
