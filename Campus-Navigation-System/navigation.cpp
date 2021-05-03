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
        if (i == 26) cout << '\t';
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
            stack<int> direct;
            stack<double> dis;
            while(v && v != u) {
                path.push(v);
                direct.push(edge[pre[v]].direct);
                dis.push(edge[pre[v]].dis);
                v = edge[pre[v]].u;
            }
            cout << "用户从" << node[u].name << "出发";
            while (!path.empty()) {
                int next, next_direct;
                double next_dis;
                next_direct = direct.top(); direct.pop();
                next = path.top(); path.pop();
                next_dis = dis.top(); dis.pop();
                switch (next_direct) {
                    case 0:
                        cout << "向东走";
                        break;
                    case 1:
                        cout << "向西走";
                        break;
                    case 2:
                        cout << "向南走";
                        break;
                    case 3:
                        cout << "向北走";
                        break;
                    default:
                        break;
                }
                cout << next_dis << "米到";
                cout << node[next].name << ' ';
                if(!path.empty()) {
                    cout << "从" << node[next].name;
                }
                else cout << "到达目的地附近";
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
            stack<int> direct;
            stack<double> dis;
            while(v && v != u) {
                path.push(v);
                direct.push(edge[pre[v]].direct);
                dis.push(edge[pre[v]].dis);
                v = edge[pre[v]].u;
            }
            cout << "用户从" << node[u].name << "出发";
            while (!path.empty()) {
                int next, next_direct;
                double next_dis;
                next_direct = direct.top(); direct.pop();
                next = path.top(); path.pop();
                next_dis = dis.top(); dis.pop();
                switch (next_direct) {
                    case 0:
                        cout << "向东走";
                        break;
                    case 1:
                        cout << "向西走";
                        break;
                    case 2:
                        cout << "向南走";
                        break;
                    case 3:
                        cout << "向北走";
                        break;
                    default:
                        break;
                }
                cout << next_dis << "米到";
                cout << node[next].name << ' ';
                if(!path.empty()) {
                    cout << "从" << node[next].name;
                }
                else cout << "到达目的地附近";
            }
            cout << endl;
        }
        else {
            cout << "不存在的目的地!" << endl;
        }
    }
    else if (tactics_flag == 3) {
        int min_dis_all[300][300];
        for (int i = 0; i < node.size(); i ++) {
            for (int j = 0; j < node.size(); j ++) {
                min_dis_all[i][j] = INF;
                if (i == j) min_dis_all[i][j] = 0;
            }
        }
        for (int i = 0; i < edge.size(); i ++) {
            min_dis_all[edge[i].u][edge[i].v] = int(edge[i].dis);
        }
        for (int k = 1; k < node.size(); k ++) {
            for (int i = 1; i < node.size(); i ++) {
                for (int j = 1; j < node.size(); j ++) {
                    min_dis_all[i][j] = min(min_dis_all[i][j], min_dis_all[i][k] + min_dis_all[k][j]);
                }
            }
        }
        string start;
        int start_flag = 0;
        int u;
        int goto_num;
        vector <int> goto_node;
        printf("请输入起点：");
        while(true) {
            cin >> start;
            for (int i = 0; i < num_node; i ++) {
                if (cmp(start, node[i].name)) {
                    u = i;
                    start_flag = 1;
                    break;
                }
            }
            if (start_flag) break;
            printf("起点不存在，请重新输入：");
        }
        printf("请输入目的地数：");
        cin >> goto_num;
        for (int i = 0; i < goto_num; i ++) {
            printf("请输入目的地%d：", i + 1);
            string end;
            int goto_flag = 0;
            cin >> end;
            for (int j = 0; j < num_node; j ++) if (cmp(end, node[j].name)) { goto_node.push_back(j); goto_flag = 1; break; }
            if (!goto_flag) {
                printf("目的地不存在，请重新输入！\n");
                i --;
            }
        }
        vector<int> path;
        int dis = 0;
        ShortestMultiplePath(u, goto_node, min_dis_all, path);
        cout << "最优路径为：";
        cout << node[u].name << "->";
        for (int i = 0; i < goto_num; i ++) {
            if (!i) dis += min_dis_all[u][path[i]];
            else dis += min_dis_all[path[i - 1]][path[i]];
        }
        for (int i = 0; i < goto_num; i ++) {
            if (i != goto_num - 1) {
                cout << node[path[i]].name << "->";
            }
            else cout << node[path[i]].name;
        }
        cout << endl;
        cout << "最短距离是：" << dis << "米" << endl;
        for (int i = 0; i < goto_num; i ++) {
            int tempu, tempv;
            if (!i) {
                tempu = u;
                tempv = path[i];
            }
            else {
                tempu = path[i - 1];
                tempv = path[i];
            }
            ShortestPath(num_node, num_edge, tempu, min_dis, pre, edge);
            int path_len = 0;
            stack<int> s_path;
            stack<int> s_direct;
            stack<double> s_dis;
            while(tempv && tempv != tempu) {
                s_path.push(tempv);
                s_direct.push(edge[pre[tempv]].direct);
                s_dis.push(edge[pre[tempv]].dis);
                path_len ++;
                tempv = edge[pre[tempv]].u;
            }
            cout << "用户从" << node[tempu].name << "出发";
            while (!s_path.empty()) {
                int next, next_direct;
                double next_dis;
                next_direct = s_direct.top(); s_direct.pop();
                next = s_path.top(); s_path.pop();
                next_dis = s_dis.top(); s_dis.pop();
                path_len --;
                switch (next_direct) {
                    case 0:
                        cout << "向东走";
                        break;
                    case 1:
                        cout << "向西走";
                        break;
                    case 2:
                        cout << "向南走";
                        break;
                    case 3:
                        cout << "向北走";
                        break;
                    default:
                        break;
                }
                cout << next_dis << "米到";
                cout << node[next].name << ' ';
                if(path_len > 1) {
                    cout << "从" << node[next].name;
                }
            }
            cout << endl;
        }
        cout << "到达全部目的地" << endl;
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
            stack<int> direct;
            stack<double> dis;
            while(v && v != u) {
                path.push(v);
                direct.push(edge[pre[v]].direct);
                dis.push(edge[pre[v]].dis);
                v = edge[pre[v]].u;
            }
            cout << "用户从" << node[u].name << "出发";
            while (!path.empty()) {
                int next, next_direct;
                double next_dis;
                next_direct = direct.top(); direct.pop();
                next = path.top(); path.pop();
                next_dis = dis.top(); dis.pop();
                switch (next_direct) {
                    case 0:
                        cout << "向东骑行";
                        break;
                    case 1:
                        cout << "向西骑行";
                        break;
                    case 2:
                        cout << "向南骑行";
                        break;
                    case 3:
                        cout << "向北骑行";
                        break;
                    default:
                        break;
                }
                cout << next_dis << "米到";
                cout << node[next].name << ' ';
                if(!path.empty()) {
                    cout << "从" << node[next].name;
                }
                else cout << "到达目的地附近";
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
