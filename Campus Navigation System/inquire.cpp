//
//  inquire.cpp
//  Campus Navigation System
//
//  Created by 冯勇鑫 on 2021/4/22.
//

#include "main.hpp"
using namespace std;

void Inquire(Node user, vector<Node> node, vector<Edge> edge) {
    int num_node, num_edge;
    num_node = int(node.size());
    num_edge = int(edge.size());
    double min_dis[num_node + 10];
    int pre_node[num_node + 10];
    ShortestPath(num_node, num_edge, min_dis, pre_node, edge);
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
