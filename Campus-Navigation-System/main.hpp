//
//  main.hpp
//  Campus Navigation System
//
//  Created by 冯勇鑫 on 2021/4/22.
//

#ifndef main_hpp
#define main_hpp

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <iomanip>
#include <unistd.h>
const int NODEONE = 93;             //校区一建筑物，服务设施，路口总数
const int NODETWO = 38;             //校区二建筑物，服务设施，路口总数
const int EDGEONE = 286;            //校区一道路总数
const int EDGETWO = 118;            //校区二道路总数
const int INF = 0x3f3f3f3f;

using namespace std;
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
class Clock
{
public:
    Clock(){};
    void SetTime(int newH = 0, int newM = 0, int newS = 0);
    void ShowTime();
    void Run();          //Run()控制计时
private:
    int hour, minute, second;
};
void StartSystem(vector<Node> & , vector<Edge> & , vector<Node> & , vector<Edge> & , Node & );                                  //进入系统
void InitOne(vector<Node> & , vector<Edge> &);                                                                                  //初始化校区一
void InitTwo(vector<Node> & , vector<Edge> &);                                                                                  //初始化校区二
void InitUser(vector<Node> &, vector<Edge> &, Node & );                                                                         //用户初始化
void ChangeUVOne(int[] , int* );
void ChangeUVTwo(int[] , int* );
void Navigation(vector<Node> & , vector<Edge> & , vector<Node> & , vector<Edge> & , Node & );                                   //导航系统
void Inquire(Node , vector<Node> , vector <Edge> );                                                                             //查询系统
void NavigationInOneCampus(vector<Node> & , vector<Edge> & , Node & );                                                          //单独校区内物理位置导航
void NavigationInTwoCampus(vector<Node> & , vector<Edge> & , vector<Node> & , vector<Edge> & , Node & );                        //跨校区物理位置导航
void ShortestPath(int , int , int , double * , int * , vector<Edge> );                                                          //计算最短距离
void ShortestTime(int , int , int , double * , int * , vector<Edge> );                                                          //计算最短时间
void ShortestBicycle(int , int , int , double * , int * , vector<Edge> );                                                       //交通工具最短路径
void ShortestMultiplePath(int , vector<int> , int [][300], vector<int> & );                                                     //多终点导航策略
bool StrCompare(string , string );

#endif /* main_hpp */
