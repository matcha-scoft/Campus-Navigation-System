#ifndef main_hpp
#define main_hpp

#include <sys/select.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <cstring>
#include <iomanip>
#include <unistd.h>
#include <queue>
#include <fstream>
const int NODEONE = 93;             //校区一建筑物，服务设施，路口总数
const int NODETWO = 38;             //校区二建筑物，服务设施，路口总数
const int EDGEONE = 286;            //校区一道路总数
const int EDGETWO = 118;            //校区二道路总数
const int INF = 0x3f3f3f3f;
const bool pulse_ = 1;               //是否中断标记

using namespace std;

//时间结构
class Time {
public:
    int h, m;                       //维护到小时分钟
};
//时钟结构
class Clock
{
public:
    Clock(){};                                      //构造函数
    void SetTime(int newH = 0, int newM = 0);       //时间初始化
    void ShowTime();                                //显示时间
    void Run();                                     //Run()控制计时，真实的一秒表示两分钟
    void Run(int );                                 //公交车，班车计时，真实的一秒表示十分钟
    int getH();                                     //返回私有成员hour
    int getM();                                     //返回私有成员minute
private:
    int hour, minute;                               //小时，分钟
};
//边结构
class Edge {
public:
    int num;                                        //编号
    double dis;                                     //距离
    int direct;                                     //方向，0，1，2，3表示四个方向
    bool pass;                                      //可否通行自行车，0为不可通行，1为可通行
    double k;                                       //拥挤程度，小于等于1的小数，实际速度等于速度乘以拥挤程度
    int u, v;                                       //连接u,v节点，由u指向v的有向边
};
//节点结构
class Node {
public:
    int num;                                        //节点编号
    string name;                                    //名称
};
//保存用户所在位置信息的结构
class Pos {
public:
    bool state;                                     //用户位置的状态，在节点上（在某一建筑物或服务设施上）则为0，在边上则为1
    string pos;                                     //state为0时保存用户所在节点的name
    int pos_num;                                    //state为1时保存用户所在边的下标
    int campus_num;                                 //保存用户所在校区
    double dis;                                     //state为1时保存用户距离前方节点的距离
    //flag初始化时为0，当系统获得用户输入得到用户最初位置后设置为1，设置为1后系统自行维护用户位置，不需用户再次输入所在位置
    bool flag;                                      
    Pos() {
        flag = false;                               //构造函数初始化flag
    }
    //更新用户当前状态信息，表示用户在一个节点上，state置0，pos为用户所在节点name，campus为用户所在校区数，传入时钟维护写入文件的时间
    void up(string pos , int campus, Clock my_clock) {
        flag = true;                                //flag始终置1
        campus_num = campus;                        //更新校区数
        this -> pos = pos;                          //更新所在节点name
        state = 0;                                  //更新state
        //用户信息写入log文件
        ofstream ofs;
        ofs.open("log.txt", ios::app);
        ofs << "当前时间" << my_clock.getH() << "时" << my_clock.getM() << "分，";
        ofs << "用户位于校区" << campus << "的" << pos << endl;
        ofs.close();
    }
    //重构，更新用户当前状态信息，表示用户在一条边上，state置1，pos_num为用户所在边的下标，campus为用户所在校区数，dis为用户距离此条边终点的距离
    void up(int pos_num, int campus, double dis, Clock my_clock) {
        flag = true;
        this -> pos_num = pos_num;                  //更新用户所在边下标
        campus_num = campus;                      
        this -> dis = dis;                          //更新距离
        state = 1;                                  //更新state
        //写入log文件
        ofstream ofs;
        ofs.open("log.txt", ios::app);
        ofs << "当前时间" << my_clock.getH() << "时" << my_clock.getM() << "分，";
        ofs << "用户位于校区" << campus << "的" << pos_num / 2 + 1 << "号道路上，距离前方目标" << dis << "米" << endl;
        ofs.close();
    }
    //重构，表示用户在班车或公交车上，bus为0表示在公交车上，bus为1表示在定点班车上
    void up(int bus, Clock my_clock) {
        flag = true;
        //写入文件
        ofstream ofs;
        ofs.open("log.txt", ios::app);
        ofs << "当前时间" << my_clock.getH() << "时" << my_clock.getM() << "分，";
        if (bus == 0) {
            ofs << "用户正在乘坐公交车" << endl;
        }
        else {
            ofs << "用户正在乘坐定点班车" << endl;
        }
        ofs.close();
    }
};

//进入系统，参数为校区一，二的节点数组和边数组，用户位置信息，同步时钟，定点班车时间表
void StartSystem(vector<Node> & , vector<Edge> & , vector<Node> & , vector<Edge> & , Pos & , Clock & , vector<Time> );            
//初始化校区一，参数为校区一的节点数组和边数组（传引用）                      
void InitOne(vector<Node> & , vector<Edge> &); 
//初始化校区二，参数为校区二的节点数组和边数组（传引用）                                                                                 
void InitTwo(vector<Node> & , vector<Edge> &);                                                                                  
//校区一初始化辅助函数，已知每条边的起点，计算每条边的终点
void ChangeUVOne(int[] , int* );
//校区二初始化辅助函数
void ChangeUVTwo(int[] , int* );
//初始化定点班车发车时刻表
void InitTimeTable(vector<Time> & );
//查询系统，参数为用户位置信息，用户所在校区的节点数组，边数组，时钟信息用来写入文件
void Inquire(Pos , vector<Node> , vector <Edge> , Clock );       
//单校区导航系统，参数为所在校区的节点和边，用户位置信息，起点名称，所有终点的名称，时钟                                                                    
bool NavigationInOneCampus(vector<Node> & , vector<Edge> & , Pos & , string , vector<string> , Clock & );           
//跨校区导航系统，参数为两校区的节点和边，用户位置信息，起点名称，所有终点名称（跨校区不支持多终点），时钟，定点班车表                                               
void NavigationInTwoCampus(vector<Node> & , vector<Edge> & , vector<Node> & , vector<Edge> & , Pos & , string , vector<string> , Clock & , vector<Time> );  
//计算最短距离，时间，自行车策略最短路径，参数为节点数，边数，起点下标，从起点到每个节点的最短距离数组，路径维护数组，用户所在校区的边数组                     
void ShortestPath(int , int , int , double * , int * , vector<Edge> );                                                                                                            
//多目的地最短路径，不维护任意两目的地之间的具体路径，只维护整体多目的地的路径，参数为起点下标，终点下标集合，全图任意两节点之间的最短路径，整体路径
void ShortestMultiplePath(int , vector<int> , int [][300], vector<int> & );        
//中断
bool pulse(Pos , vector<Node> , vector <Edge> , Clock );

#endif /* main_hpp */
