#include "main.hpp"
using namespace std;

//查询
void Inquire(Pos user, vector<Node> node, vector<Edge> edge, Clock my_clock) {
    //判断用户状态
    if (user.state == 0) {  
        //用户在节点上，新建一条长度为0的有向边，从用户节点指向用户所在位置的节点                        
        Edge temp;
        for (int i = 0; i < node.size(); i ++) {
            //查找到用户所在节点
            if (user.pos == node[i].name) {
                temp.u = 0;                 //0号节点为用户节点
                temp.v = i;
                temp.dis = 0;
                edge.push_back(temp);
            }
        }
    }
    else {
        //用户在边上，新建两条边，分别指向用户所在边的起点和终点
        Edge temp[2];
        //第一条边从用户指向用户所在边的终点，长度为dis
        temp[0].v = edge[user.pos_num].v;
        temp[0].u = 0;
        temp[0].dis = user.dis;
        //第二条边从用户指向用户所在边的起点，长度为边长减dis
        temp[1].v = edge[user.pos_num].u;
        temp[1].u = 0;
        temp[1].dis = edge[user.pos_num].dis - user.dis;
        //两条边插入边集合
        edge.push_back(temp[0]);
        edge.push_back(temp[1]);
    }
    //计算单源最短路径
    int num_node, num_edge;
    num_node = int(node.size());
    num_edge = int(edge.size());
    double min_dis[num_node + 10];
    int pre_node[num_node + 10];
    ShortestPath(num_node, num_edge, 0, min_dis, pre_node, edge);
    int dis = 500;
    //将与起点距离小于等于dis的节点输出
    cout << "附近的建筑和服务设施有:" << endl;
    for (int i = 1; i < node.size(); i ++) {
        if (min_dis[i] <= dis) {
            cout << node[i].name << ",最短距离是:" << min_dis[i] << endl;
        }
    }
    //删除添加的边
    if (user.state == 0) {
        edge.erase(edge.end() - 1);
    }
    else {
        edge.erase(edge.end() - 1);
        edge.erase(edge.end() - 1);
    }
    //查询信息写入文件
    ofstream ofs;
    ofs.open("log.txt", ios::app);
    ofs << "当前时间" << my_clock.getH() << "时" << my_clock.getM() << "分，";
    ofs << "用户查询。" << endl;
    ofs << "附近的建筑和服务设施有:" << endl;
    for (int i = 1; i < node.size(); i ++) {
        if (min_dis[i] <= dis) {
            ofs << node[i].name << ",最短距离是:" << min_dis[i] << endl;
        }
    }
    ofs.close();
}
