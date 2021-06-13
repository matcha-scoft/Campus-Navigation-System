#include "main.hpp"
using namespace std;

//单源最短路径的ford算法，返回d数组保存u到d[i]的最短距离，pre数组中的pre[i]保存最短路径上以i号节点为终点的边的下标
void ShortestPath(int n, int m, int s, double * d, int * pre, vector<Edge> edge) {
    //预处理
    for (int i = 0; i < n; i ++) {
        d[i] = INF;
        pre[i] = INF;
    }
    //将起点路径长设为零
    d[s] = 0;
    while (true) {
        //判断d数组是否有更新，有更新则继续搜索，无更新即已经找到所有最短路径，则退出循环
        bool update = false;
        //遍历每一条边
        for (int i = 0; i < m; i ++) {
            Edge e = edge[i];
            //若存在某一条有向边e，选择此条边可以更新他的终点节点的最短距离
            if (d[e.u] != INF && d[e.v] > d[e.u] + e.dis) {
                //更新他的终点节点的最短距离
                d[e.v] = d[e.u] + e.dis;
                //保存此条边，将此边作为其终点的前驱边
                pre[e.v] = i;
                update = true;
            }
        }
        if (!update) break;
    }
}

//贪心求解途径最短路径，返回路径保存在ans中
void ShortestMultiplePath(int u, vector <int> goto_node, int dis[300][300], vector <int> & ans) {
    bool ok[goto_node.size() + 10];
    for (int i = 0; i < goto_node.size() + 10; i ++) ok[i] = false;
    while (ans.size() != goto_node.size() - 1) {
        int minn = INF, minp;
        for (int i = 0; i < goto_node.size() - 1; i ++) {
            if (ok[i]) continue;
            if (dis[u][goto_node[i]] < minn) {
                minn = dis[u][goto_node[i]];
                minp = i;
            }
        }
        ans.push_back(goto_node[minp]);
        u = goto_node[minp];
        ok[minp] = true;
    }
    ans.push_back(goto_node[goto_node.size() - 1]);
}




// //贪心求解限界函数上界
// int greed(bool * ok, int ** gra, int x, int size) {
//     ok[x] = false;
//     bool updata = false;
//     int min_pos, min = INF;
//     for (int i = 0; i < size; i ++) {
//         if (ok[i]) {
//             updata = true;
//             if (gra[x][i] < min) {
//                 min = gra[x][i];
//                 min_pos = i;
//             }
//         }
//     }
//     if (!updata) return 0;
//     return min + greed(ok, gra, min_pos, size);
// }
// //多目的地路径问题，返回数组ans，保存整体路径（非具体的路径）
// void ShortestMultiplePath(int u, vector<int> goto_node, int dis[300][300], vector<int> & ans) {
//     int lower = 0, upper = 0;
//     int ** gra;
    
//     gra = new int * [goto_node.size() + 2];
//     for (int i = 0; i < (goto_node.size() + 2); i ++) {
//         gra[i] = new int[goto_node.size() + 2];
//     } 
//     for (int i = 0; i <= goto_node.size(); i ++) {
//         for (int j = 0; j <= goto_node.size(); j ++) {
//             if (i == j) gra[i][j] = INF;
//             else if (j == goto_node.size()) {
//                 gra[i][j] = dis[goto_node[i]][u];
//             }
//             else if (i == goto_node.size()) {
//                 gra[i][j] = dis[u][j];
//             }
//             else {
//                 gra[i][j] = dis[goto_node[i]][goto_node[j]];
//             }
//         }
//     }
//     bool * ok; 
//     ok = new bool[goto_node.size() + 2];
//     for (int i = 0; i < (goto_node.size() + 2); i ++) {
//         ok[i] = true;
//     }
//     //贪心求解上界
//     upper = greed(ok, gra, goto_node.size(), goto_node.size() + 1);
//     //求解下界
//     int minl[goto_node.size()];
//     int minn;
//     for (int i = 0; i < goto_node.size(); i ++) {
//         for (int j = 0; j < goto_node.size(); j ++) {
//             if (j == 0) minl[i] = gra[i][j];
//             else minl[i] = min(minl[i], gra[i][j]);
//         }
//     }
//     for (int i = 0; i < goto_node.size(); i ++) {
//         if (i == 0) minn = gra[goto_node.size()][i];
//         else minn = min(minn, gra[goto_node.size()][i]);
//     }




//     for (int i = 0; i < (goto_node.size() + 2); i ++) {
//         delete[] gra[i];
//     }
//     delete[] gra;
//     delete[] ok;


//     sort(goto_node.begin(), goto_node.end());
//     for (int i = 0; i < goto_node.size(); i ++) {
//         ans.push_back(goto_node[i]);
//     }
//     int min_temp = 0;
//     for (int i = 0; i < goto_node.size(); i ++) {
//         if (!i) min_temp += dis[u][goto_node[i]];
//         else {
//             min_temp += dis[goto_node[i - 1]][goto_node[i]];
//         }
//     }
//     while(next_permutation(goto_node.begin(), goto_node.end())) {
//         int temp = 0;
//         for (int i = 0; i < goto_node.size(); i ++) {
//             if (!i) temp += dis[u][goto_node[i]];
//             else {
//                 temp += dis[goto_node[i - 1]][goto_node[i]];
//             }
//         }
//         if (temp < min_temp) {
//             min_temp = temp;
//             ans.clear();
//             for (int i = 0; i < goto_node.size(); i ++) {
//                 ans.push_back(goto_node[i]);
//             }
//         }
//     }
// }
