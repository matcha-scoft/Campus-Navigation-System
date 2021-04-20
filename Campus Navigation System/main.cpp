//
//  main.cpp
//  Campus Navigation System
//
//  Created by 冯勇鑫 on 2021/3/21.
//
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int NODEONE = 93;             //校区一建筑物，服务设施，路口总数
const int NODETWO = 38;             //校区二建筑物，服务设施，路口总数
const int EDGEONE = 286;            //校区一道路总数
const int EDGETWO = 118;            //校区二道路总数
const int INF = 0x3f3f3f3f;

class Edge {
public:
    int num;                        //编号
    double dis;                     //距离
    int direct;                     //方向
    bool pass;                      //可否通行自行车
    double k;                       //拥挤程度
    int u, v;                       //连接u,v节点，由u指向v的有向边
};
class Node {
public:
    int num;                        //节点编号
    int campus_num;                 //校区数
    string name;                    //名称
};

void StartSystem(vector<Node> , vector<Edge> , vector<Node> , vector<Edge> , Node & );                                          //进入系统
void InitOne(vector<Node> & , vector<Edge> &);                                                                                  //初始化校区一
void InitTwo(vector<Node> & , vector<Edge> &);                                                                                  //初始化校区二
void InitUser(vector<Node> &, vector<Edge> &, Node & );                                                                         //用户初始化
void ChangeUVOne(int[] , int* );
void ChangeUVTwo(int[] , int* );
void Navigation();                                                                                                              //导航系统
void Inquire(Node , vector<Node> , vector <Edge> );                                                                             //查询系统
void NavigationInOneCampus(vector<Node> , vector<Edge> );                                                                       //单独校区内物理位置导航
void NavigationInTwoCampus(vector<Node> , vector<Edge> , vector<Node> , vector<Edge> );                                         //跨校区物理位置导航
void ShortestPath(int , int ,double * , vector<Edge> );                                                                         //计算最短距离


int main(void) {
    vector <Node> node_one;                                          //校区一的节点建筑
    vector <Node> node_two;                                          //校区二的节点建筑
    vector <Edge> edge_one;                                          //校区一的道路
    vector <Edge> edge_two;                                          //校区二的道路
    Node user;                                                       //保存用户信息
    InitUser(node_two, edge_two, user);                              //用户初始化
    InitOne(node_one, edge_one);
    InitTwo(node_two, edge_two);
    StartSystem(node_one, edge_one, node_two, edge_two, user);
    return 0;
}

void StartSystem(vector <Node> node_one, vector <Edge> edge_one, vector <Node> node_two, vector <Edge> edge_two, Node & user) {
    string input;
    int quit_flag = 1;
    printf("********校园导览系统********\n");
    printf("**    输入1进入导航系统    **\n");
    printf("**    输入2进入查询系统    **\n");
    printf("**     输入0退出系统      **\n");
    printf("**模拟用户起始位置为校区二南门*\n");
    printf("**************************\n");
    printf("请输入：");
    while(quit_flag && cin >> input) {
        if (input.size() > 1) {
            printf("非法输入!请重新输入\n");
        }
        else {
            switch (input[0]) {
                case '1':
                    
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
        printf("请输入：");
    }
}

void InitOne(vector<Node> & node_one, vector<Edge> & edge_one) {
    string node_names_one[100] = {"路口", "校西门", "路口", "加油站一", "路口", "路口", "路口", "路口", "路口", "路口",
        "停车场一", "校医院一", "路口", "图书馆二", "路口", "教学楼一", "路口", "教学楼二", "路口", "教学楼三",
        "一食堂", "路口", "学生宿舍九", "学生宿舍十一", "学生宿舍十", "学生宿舍十二", "路口", "篮球场一", "足球场一", "二食堂",
        "学生宿舍七", "学生宿舍八", "路口", "三食堂", "校北门", "路口", "路口", "路口", "路口", "路口",
        "路口", "路口", "路口", "路口", "学生活动中心一", "路口", "路口", "路口", "校南门", "路口",
        "教学楼四", "学生活动中心二", "雁栖湖", "路口", "路口", "路口", "路口", "路口", "学生宿舍一", "学生宿舍四",
        "路口", "学生宿舍十三", "学生宿舍十四", "路口", "教学楼五", "四食堂", "路口", "路口", "足球场二", "路口",
        "路口", "图书馆一", "路口", "路口", "学生宿舍二", "学生宿舍五", "路口", "路口", "路口", "篮球场二",
        "校医院", "路口", "路口", "学生宿舍三", "学生宿舍六", "路口", "路口", "停车场二", "加油站二", "路口",
        "校东门", "路口", "路口"
    };                                   //所有节点名称
    double edge_dis_one[300] = {
        
    };                                       //所有道路距离
    bool edge_pass_one[300];                 //所有道路可否通行自行车
    int edge_direct_one[300];                //所有道路方向; 0,1,2,3分别表示东西南北
    double edge_k_one[300] = {};             //所有道路拥挤程度
    int edge_u_one[300] = {
        1, 2, 2, 3, 11, 12, 12, 13, 13, 14,
        14, 15, 5, 6, 15, 16, 6, 7, 16, 17,
        7, 8, 18, 19, 19, 20, 8, 9, 20, 21,
        21, 22, 9, 10, 23, 24, 27, 28, 28, 29,
        29, 30, 30, 31, 31, 32, 32, 33, 33, 34,
        25, 26, 35, 36, 36, 37, 37, 38, 38, 39,
        39, 40, 40, 41, 41, 42, 42, 43, 43, 44,
        44, 46, 46, 47, 47, 48, 48, 49, 50, 51,
        51, 52, 52, 53, 53, 54, 54, 93, 58, 59,
        59, 60, 60, 61, 55, 56, 56, 57, 64, 66,
        66, 68, 73, 75, 75, 76, 76, 77, 62, 63,
        63, 65, 65, 67, 67, 69, 69, 70, 71, 72,
        72, 74, 82, 84, 84, 85, 85, 86, 78, 79,
        79, 80, 81, 83, 87, 88, 88, 89, 90, 91,
        91, 92, 1, 35, 35, 90, 4, 11, 11, 27,
        27, 36, 36, 55, 55, 62, 62, 78, 37, 50,
        50, 56, 56, 63, 63, 79, 12, 28, 28, 38,
        13, 29, 29, 39, 39, 51, 51, 57, 57, 64,
        64, 65, 40, 52, 52, 66, 66, 67, 69, 80,
        2, 5, 5, 15, 15, 30, 30, 41, 41, 53,
        53, 68, 68, 70, 70, 71, 6, 16, 54, 72,
        72, 81, 17, 31, 31, 42, 7, 18, 19, 32,
        32, 43, 43, 93, 93, 58, 58, 73, 73, 74,
        74, 82, 82, 83, 83, 87, 87, 91, 8, 20,
        20, 33, 44, 59, 59, 75, 75, 84, 84, 88,
        21, 34, 34, 45, 45, 46, 9, 22, 22, 23,
        23, 25, 25, 47, 47, 60, 60, 76, 76, 85,
        10, 24, 24, 26, 26, 48, 48, 61, 61, 77,
        77, 86, 3, 49, 49, 92,
    };
    
    int edge_v_one[300];
    for (int i = 0; i < NODEONE; i ++) {
        Node temp;
        temp.num = i + 1;
        temp.name = node_names_one[i];
        node_one.push_back(temp);
    }
    for (int i = 0; i < 142; i += 2) {
        edge_direct_one[i] = 2;
        edge_direct_one[i + 1] = 3;
    }
    for (int i = 142; i < 286; i += 2) {
        edge_direct_one[i] = 0;
        edge_direct_one[i + 1] = 1;
    }
    ChangeUVOne(edge_u_one, edge_v_one);
    for (int i = 0; i < EDGEONE; i ++) {
        Edge temp;
        temp.num = i + 1;
        temp.dis = edge_dis_one[i];
        temp.pass = edge_pass_one[i];
        temp.direct = edge_direct_one[i];
        temp.k = edge_k_one[i];
        temp.u = edge_u_one[i];
        temp.v = edge_v_one[i];
        edge_one.push_back(temp);
    }
    cout << "初始化模拟校园校区一成功" << endl;
}

void InitTwo(vector<Node> & node_two, vector<Edge> & edge_two) {
    string node_names_two[100] = {
        "停车场一", "加油站", "足球场一", "教学楼一", "学生宿舍一", "停车场二", "体育馆", "北区图书馆", "学生食堂一", "湖一",
        "学生食堂二", "教师食堂", "校北门", "篮球场一", "路口", "学生活动中心", "篮球场二", "停车场三", "篮球场三", "篮球场四",
        "篮球场五", "篮球场六", "足球场二", "足球场三", "游泳馆", "湖二", "教学楼二", "教学楼三", "教学楼四", "教学楼五",
        "学生宿舍二", "学生宿舍三", "学生宿舍四", "学生宿舍五", "南区图书馆", "校南门", "校医院", "停车场四"
    };                                       //所有节点名称
    double edge_dis_two[300] = {
        200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
        40, 40, 160, 160, 160, 160, 160, 160, 160, 160,
        280, 280, 280, 280, 120, 120, 160, 160, 160, 160,
        160, 160, 200, 200, 200, 200, 200, 200, 300, 300,
        300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
        300, 300, 300, 300, 300, 300, 300, 300, 120, 120,
        120, 120, 120, 120, 120, 120, 240, 240, 240, 240,
        240, 240, 240, 240, 120, 120, 120, 120, 120, 120,
        120, 120, 240, 240, 240, 240, 120, 120, 120, 120,
        240, 240, 240, 240, 240, 240, 240, 240, 240, 240,
        240, 240, 240, 240, 240, 240, 240, 240, 240, 240,
        240, 240, 240, 240, 240, 240, 240, 240
    };                                       //所有道路距离
    bool edge_pass_two[300];                 //所有道路可否通行自行车
    int edge_direct_two[300];                //所有道路方向; 0,1,2,3分别表示东西南北
    double edge_k_two[300] = {};             //所有道路拥挤程度
    int edge_u_two[300] = {
        1, 2, 7, 8, 9, 10, 11, 12, 13, 14,
        14, 15, 16, 17, 18, 19, 17, 21, 19, 22,
        2, 3, 10, 23, 15, 20, 20, 24, 21, 25,
        22, 26, 3, 4, 24, 28, 26, 30, 4, 5,
        27, 31, 28, 32, 29, 33, 30, 34, 5, 6,
        31, 35, 32, 36, 33, 37, 34, 38, 1, 7,
        7, 9, 9, 11, 11, 13, 13, 16, 16, 18,
        14, 17, 17, 19, 2, 8, 8, 10, 10, 12,
        12, 15, 20, 21, 21, 22, 3, 23, 23, 24,
        24, 25, 25, 26, 4, 27, 27, 28, 28, 29,
        29, 30, 5, 31, 31, 32, 32, 33, 33, 34,
        6, 35, 35, 36, 36, 37, 37, 38
    };
    int edge_v_two[300];
    
    for (int i = 0; i < NODETWO; i ++) {
        Node temp;
        temp.num = i + 1;
        temp.name = node_names_two[i];
        node_two.push_back(temp);
    }
    for (int i = 0; i < 58; i += 2) {
        edge_direct_two[i] = 2;
        edge_direct_two[i + 1] = 3;
    }
    for (int i = 58; i < 118; i += 2) {
        edge_direct_two[i] = 0;
        edge_direct_two[i + 1] = 1;
    }
    ChangeUVTwo(edge_u_two, edge_v_two);
    for (int i = 0; i < EDGETWO; i ++) {
        Edge temp;
        temp.num = i + 1;
        temp.dis = edge_dis_two[i];
        temp.pass = edge_pass_two[i];
        temp.direct = edge_direct_two[i];
        temp.k = edge_k_two[i];
        temp.u = edge_u_two[i];
        temp.v = edge_v_two[i];
        edge_two.push_back(temp);
    }
    cout << "初始化模拟校园校区二成功" << endl;
}

void ChangeUVOne(int edge_u_one[EDGEONE], int * edge_v_one) {
    for (int i = 0; i < EDGEONE; i += 2) {
        edge_v_one[i] = edge_u_one[i + 1];
        edge_v_one[i + 1] = edge_u_one[i];
    }
}
void ChangeUVTwo(int edge_u_two[EDGETWO], int * edge_v_two) {
    for (int i = 0; i < EDGETWO; i += 2) {
        edge_v_two[i] = edge_u_two[i + 1];
        edge_v_two[i + 1] = edge_u_two[i];
    }
}

void InitUser(vector<Node> & node_two, vector<Edge> & edge_two, Node & user) {
    user.name = "用户";
    user.num = 0;
    user.campus_num = 2;
    node_two.insert(node_two.begin(), user);
    Edge new_edge;
    new_edge.u = 0;
    new_edge.v = 36;
    new_edge.direct = -1;
    new_edge.dis = 0;
    new_edge.k = 0;
    new_edge.pass = true;
    new_edge.num = EDGETWO + 1;
    edge_two.push_back(new_edge);
}

void Inquire(Node user, vector<Node> node, vector<Edge> edge) {
    int num_node, num_edge;
    num_node = int(node.size());
    num_edge = int(edge.size());
    double min_dis[num_node + 10];
    ShortestPath(num_node, num_edge, min_dis, edge);
    vector<int> inquire_res;
    int dis = 500;
    for (int i = 1; i < node.size(); i ++) {
        if (min_dis[i] <= dis) inquire_res.push_back(i);
    }
    cout << "附近的建筑和服务设施有:" << endl;
    for (int i = 0; i < inquire_res.size(); i ++) {
        cout << node[inquire_res[i]].name << endl;
    }
}

void ShortestPath(int n, int m, double * d, vector<Edge> edge) {
    for (int i = 0; i < n; i ++) d[i] = INF;
    d[0] = 0;
    while (true) {
        bool update = false;
        for (int i = 0; i < m; i ++) {
            Edge e = edge[i];
            if (d[e.u] != INF && d[e.v] > d[e.u] + e.dis) {
                d[e.v] = d[e.u] + e.dis;
                update = true;
            }
        }
        if (!update) break;
    }
}
