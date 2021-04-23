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
                pre[e.v] = e.u;
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
                pre[e.v] = e.u;
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
                pre[e.v] = e.u;
                update = true;
            }
        }
        if (!update) break;
    }
}
