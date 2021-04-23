//
//  navigation.cpp
//  Campus Navigation System
//
//  Created by 冯勇鑫 on 2021/4/22.
//

#include "main.hpp"
using namespace std;
bool cmp(string , string );

void Navigation(vector<Node> & node_one, vector<Edge> & edge_one, vector<Node> & node_two, vector<Edge> & edge_two, Node & user) {
    string input;
    int quit_flag = 1;
    int campus_num;
    printf("**************导航系统**************\n");
    printf("**      输入1进入单校区导航系统   **\n");
    printf("**      输入2进入多校区导航系统   **\n");
    printf("**          输入0退出系统         **\n");
    printf("************************************\n");
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
	printf("**************导航系统**************\n");
        printf("**      输入1进入单校区导航系统   **\n");
        printf("**      输入2进入多校区导航系统   **\n");
        printf("**          输入0退出系统         **\n");
        printf("************************************\n");
        printf("请输入：");
    }
}

void NavigationInOneCampus(vector<Node> & node, vector<Edge> & edge, Node & user) {
    string tactics;
    int tactics_flag;
    int num_node, num_edge;
    num_node = int(node.size());
    num_edge = int(edge.size());
    double min_dis[num_node + 10];
    int pre[num_edge + 10];
    for (int i = 1; i < node.size(); i ++) {
        cout << i << ':' << node[i].name << '\t' << '\t';
        if (i % 5 == 0) cout << endl;
    }
    if (node.size() - 1 % 5) cout << endl;
    printf("**************导航策略**************\n");
    printf("**        输入1最短路径策略       **\n");
    printf("**        输入2最短时间策略       **\n");
    printf("**        输入3途径最短策略       **\n");
    printf("**        输入4交通工具策略       **\n");
    printf("************************************\n");
    printf("请输入：");
    while(cin >> tactics) {
        if (tactics.length() == 1) {
            if (tactics[0] == '1' || tactics[0] == '2' || tactics[0] == '3' || tactics[0] == '4') {
                tactics_flag = int(tactics[0] - '0');
                break;
            }
        }
        printf("非法输入！\n");
        printf("**************导航策略**************\n");
        printf("**        输入1最短路径策略       **\n");
        printf("**        输入2最短时间策略       **\n");
        printf("**        输入3途径最短策略       **\n");
        printf("**        输入4交通工具策略       **\n");
        printf("************************************\n");
        printf("请输入：");
    }
    if (tactics_flag == 1) {
        string start, end;
        cout << "请输入起点：";
        cin >> start;
        cout << "请输入终点：";
        cin >> end;
        int u = -1, v = -1;
        for (int i = 0; i < num_node; i ++) {
            if (cmp(start, node[i].name)) u = i;
            if (cmp(end, node[i].name)) v = i;
        }
        ShortestPath(num_node, num_edge, u, min_dis, pre, edge);
        if (v > 0 && v < node.size()) {
            stack<int> path;
            while(v && v != u) {
                path.push(v);
                v = pre[v];
            }
            cout << node[u].name;
            while (!path.empty()) {
                int next;
                next = path.top(); path.pop();
                cout << " -> " << node[next].name;
            }
            cout << endl;
        }
        else {
            cout << "不存在的目的地!" << endl;
        }
    }
    else if (tactics_flag == 2) {
        string start, end;
        cout << "请输入起点：";
        cin >> start;
        cout << "请输入终点：";
        cin >> end;
        int u = -1, v = -1;
        for (int i = 0; i < num_node; i ++) {
            if (cmp(start, node[i].name)) u = i;
            if (cmp(end, node[i].name)) v = i;
        }
        ShortestTime(num_node, num_edge, u, min_dis, pre, edge);
        if (v > 0 && v < node.size()) {
            stack<int> path;
            while(v && v != u) {
                path.push(v);
                v = pre[v];
            }
            cout << node[u].name;
            while (!path.empty()) {
                int next;
                next = path.top(); path.pop();
                cout << " -> " << node[next].name;
            }
            cout << endl;
        }
        else {
            cout << "不存在的目的地!" << endl;
        }
    }
    else if (tactics_flag == 3) {
        
    }
    else {
        string start, end;
        cout << "请输入起点：";
        cin >> start;
        cout << "请输入终点：";
        cin >> end;
        int u = -1, v = -1;
        for (int i = 0; i < num_node; i ++) {
            if (cmp(start, node[i].name)) u = i;
            if (cmp(end, node[i].name)) v = i;
        }
        ShortestBicycle(num_node, num_edge, u, min_dis, pre, edge);
        if (v > 0 && v < node.size()) {
            stack<int> path;
            while(v && v != u) {
                path.push(v);
                v = pre[v];
            }
            cout << node[u].name;
            while (!path.empty()) {
                int next;
                next = path.top(); path.pop();
                cout << " -> " << node[next].name;
            }
            cout << endl;
        }
        else {
            cout << "不存在的目的地!" << endl;
        }
    }
    return ;
}

void NavigationInTwoCampus(vector<Node> & node_one, vector<Edge> & edge_one, vector<Node> & node_two, vector<Edge> & edge_two, Node & user) {
    return ;
}

bool cmp(string str1, string str2) {
    if (str1.length() != str2.length()) return 0;
    int length = int(str1.length());
    for (int i = 0; i < length; i ++) {
        if (str1[i] != str2[i]) return 0;
    }
    return 1;
}
