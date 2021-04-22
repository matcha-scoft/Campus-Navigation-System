//
//  navigation.cpp
//  Campus Navigation System
//
//  Created by 冯勇鑫 on 2021/4/22.
//

#include "main.hpp"
using namespace std;

void Navigation(vector<Node> & node_one, vector<Edge> & edge_one, vector<Node> & node_two, vector<Edge> & edge_two, Node & user) {
    string input;
    int quit_flag = 1;
    int campus_num;
    printf("*************导航系统*************\n");
    printf("**     输入1进入单校区导航系统     **\n");
    printf("**     输入2进入多校区导航系统     **\n");
    printf("**         输入0退出系统         **\n");
    printf("*********************************\n");
    printf("请输入：");
    while(quit_flag && cin >> input) {
        if (input.size() > 1) {
            printf("非法输入!请重新输入\n");
        }
        else {
            switch (input[0]) {
                case '1':
                    cout << "请选择校区:";
                    cin >> campus_num;
                    if (campus_num == 1) {
                        NavigationInOneCampus(node_one, edge_one, user);
                    }
                    else if (campus_num == 2) {
                        NavigationInOneCampus(node_two, edge_two, user);
                    }
                    else cout << "非法输入！" << endl;
                    break;
                case '2':
                    NavigationInTwoCampus(node_one, edge_one, node_two, edge_two, user);
                    break;
                case '0':
                    printf("退出导航系统。\n");
                    quit_flag = 0;
                    continue;
                    break;
                default:
                    printf("非法输入!请重新输入\n");
                    break;
            }
        }
        printf("请输入：");
    }
}

void NavigationInOneCampus(vector<Node> & node, vector<Edge> & edge, Node & user) {
    int num_node, num_edge;
    num_node = int(node.size());
    num_edge = int(edge.size());
    double min_dis[num_node + 10];
    int pre[num_edge + 10];
    ShortestPath(num_node, num_edge, min_dis, pre, edge);
    for (int i = 1; i < node.size(); i ++) {
        cout << i << ':' << node[i].name << '\t' << '\t';
        if (i % 5 == 0) cout << endl;
    }
    int v;
    if (node.size() - 1 % 5) cout << endl;
    cout << "请输入终点编号:";
    cin >> v;
    if (v > 0 && v < node.size()) {
        stack<int> path;
        while(v) {
            path.push(v);
            v = pre[v];
        }
        cout << "0";
        while (!path.empty()) {
            int next;
            next = path.top(); path.pop();
            cout << " -> " << next;
        }
        cout << endl;
    }
    else {
        cout << "不存在的目的地!" << endl;
        cout << "退出导航系统" << endl;
    }
    return ;
}

void NavigationInTwoCampus(vector<Node> & node_one, vector<Edge> & edge_one, vector<Node> & node_two, vector<Edge> & edge_two, Node & user) {
    return ;
}

