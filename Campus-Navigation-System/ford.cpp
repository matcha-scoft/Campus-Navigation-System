//
//  ford.cpp
//  Campus Navigation System
//
//  Created by 冯勇鑫 on 2021/4/22.
//

#include "main.hpp"
using namespace std;

void ShortestPath(int n, int m, int s, double * d, int * pre, vector<Edge> edge) {
    for (int i = 0; i < n; i ++) {
        d[i] = INF;
        pre[i] = INF;
    }
    d[s] = 0;
    while (true) {
        bool update = false;
        for (int i = 0; i < m; i ++) {
            Edge e = edge[i];
            if (d[e.u] != INF && d[e.v] > d[e.u] + e.dis) {
                d[e.v] = d[e.u] + e.dis;
                pre[e.v] = i;
                update = true;
            }
        }
        if (!update) break;
    }
}

void ShortestTime(int n, int m, int s, double * d, int * pre, vector<Edge> edge) {
    for (int i = 0; i < edge.size(); i ++) {
        edge[i].dis = edge[i].dis / edge[i].k;
    }
    for (int i = 0; i < n; i ++) {
        d[i] = INF;
        pre[i] = INF;
    }
    d[s] = 0;
    while (true) {
        bool update = false;
        for (int i = 0; i < m; i ++) {
            Edge e = edge[i];
            if (d[e.u] != INF && d[e.v] > d[e.u] + e.dis) {
                d[e.v] = d[e.u] + e.dis;
                pre[e.v] = i;
                update = true;
            }
        }
        if (!update) break;
    }
}

void ShortestBicycle(int n, int m, int s, double * d, int * pre, vector<Edge> edge) {
    for (int i = 0; i < n; i ++) {
        d[i] = INF;
        pre[i] = INF;
    }
    d[s] = 0;
    while(true) {
        bool update = false;
        for (int i = 0; i < m; i ++) {
            if (!edge[i].pass) continue;
            Edge e = edge[i];
            if (d[e.u] != INF && d[e.v] > d[e.u] + e.dis) {
                d[e.v] = d[e.u] + e.dis;
                pre[e.v] = i;
                update = true;
            }
        }
        if (!update) break;
    }
}

void ShortestMultiplePath(int u, vector<int> goto_node, int dis[300][300], vector<int> & ans) {
    sort(goto_node.begin(), goto_node.end());
    for (int i = 0; i < goto_node.size(); i ++) {
        ans.push_back(goto_node[i]);
    }
    int min_temp = 0;
    for (int i = 0; i < goto_node.size(); i ++) {
        if (!i) min_temp += dis[u][goto_node[i]];
        else {
            min_temp += dis[goto_node[i - 1]][goto_node[i]];
        }
    }
    while(next_permutation(goto_node.begin(), goto_node.end())) {
        int temp = 0;
        for (int i = 0; i < goto_node.size(); i ++) {
            if (!i) temp += dis[u][goto_node[i]];
            else {
                temp += dis[goto_node[i - 1]][goto_node[i]];
            }
        }
        if (temp < min_temp) {
            min_temp = temp;
            ans.clear();
            for (int i = 0; i < goto_node.size(); i ++) {
                ans.push_back(goto_node[i]);
            }
        }
    }
}