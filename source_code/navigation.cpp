#include "main.hpp"
using namespace std;
bool cmp(string , string );

int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false; if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    } 
    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

//单校区导航
bool NavigationInOneCampus(vector<Node> & node, vector<Edge> & edge, Pos & user, string pos, vector<string> name, Clock & my_clock) {
    string tactics;                                     //策略选择
    int tactics_flag;
    int num_node, num_edge;                             //节点数，边数
    num_node = int(node.size());                          
    num_edge = int(edge.size());
    double min_dis[num_node + 10];                      //最短距离
    int pre[num_edge + 10];                             //最短路径，下标为路径上每条边的终点id，保存最短路径每条边的下标
    //选择策略，共三种，途经最短路径策略由目的地数目决定
    printf("**************导航策略**************\n");
    printf("**        输入1最短路径策略       **\n");
    printf("**        输入2最短时间策略       **\n");
    printf("**        输入3交通工具策略       **\n");
    printf("************************************\n");
    printf("请输入：");
    //非法输入检测
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
        printf("**        输入3交通工具策略       **\n");
        printf("************************************\n");
        printf("请输入：");
    }
    //根据不同策略设置行进速度，最短路径策略和最短时间策略使用全程平均拥挤程度乘以步行速度，步行速度设置为160m每2分钟
    double v;
    //v_state为false表示需要乘以拥挤程度（即步行），为true表示不需乘以拥挤程度（即乘坐自行车）
    bool v_state = false;  
    //根据不同的导航策略重构图，策略一直接赋值，策略二将原图的距离除以拥挤程度赋值给新图的边的dis变量，策略三将不可通行自行车的边删除                                         
    vector<Edge> new_edge;
    if (tactics_flag == 1) {
        cout << "最短路径策略:" << endl;
        v = 160;
        new_edge = edge;
    }
    else if (tactics_flag == 2) {
        cout << "最短时间策略:" << endl;
        v = 160;
        for (int i = 0; i < edge.size(); i ++) {
            Edge temp = edge[i];
            temp.dis = temp.dis / temp.k;
            new_edge.push_back(temp);
        }
    }
    else if (tactics_flag == 3) {
        cout << "自行车策略:" << endl;
        v = 600;
        v_state = true;
        for (int i = 0; i < edge.size(); i ++) {
            if (edge[i].pass) new_edge.push_back(edge[i]);
        }
    }

    num_edge = int(new_edge.size());
    //保存路径的结构
    stack <int> path_;
    stack <int> direct_;
    stack <double> dis_;
    stack <int> id_;
    vector <int> pathq;
    vector <int> directq;
    vector <double> disq;
    vector <int> idq;
    //计算拥挤度，边数，便于计算平均拥挤度
    double k_ = 0;
    int len = 0;
    //单目的地
    if (name.size() == 1) {
        //保存路径
        stack<int> path;
        //保存方向
        stack<int> direct;
        //保存距离
        stack<double> dis;
        //保存起点终点
        string start, end;
        start = pos;                                    //初始化起点
        end = name[0];                                  //初始化终点
        //遍历节点数组，搜索起点终点，下标保存到u，v
        int u = -1, v = -1;
        for (int i = 0; i < num_node; i ++) {
            if (cmp(start, node[i].name)) u = i;
            if (cmp(end, node[i].name)) v = i;
        }
        //计算从u（起点）到图中所有点的最短距离和最短路径
        ShortestPath(num_node, num_edge, u, min_dis, pre, new_edge);
        //合法性判断
        if (v > 0 && v < node.size()) {
            //当v不等于u时，将v放入path栈中，同时维护其他栈，两组栈分别用来输出完整路线和导航的过程中输出路线
            while(v && v != u) {
                path.push(v);
                direct.push(edge[pre[v]].direct);
                dis.push(edge[pre[v]].dis);
                path_.push(v);
                direct_.push(edge[pre[v]].direct);
                dis_.push(edge[pre[v]].dis);
                id_.push(pre[v]);
                //k_和len累加
                k_ += edge[pre[v]].k;
                len ++;
                //将v更新成v在最短路径上的前驱节点
                v = edge[pre[v]].u;
            }
            //当v等于u后表示路径已经完整保存在两个栈中
            cout << "用户从" << node[u].name << "出发";
            //将完整路径输出
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
    //多目的地
    else {
        //首先计算任意两节点之间的最短距离，使用Warshall算法，时间复杂度O(N^3)
        //将原图处理成一个邻接矩阵
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
        //计算任意两点之间最短距离
        for (int k = 1; k < node.size(); k ++) {
            for (int i = 1; i < node.size(); i ++) {
                for (int j = 1; j < node.size(); j ++) {
                    min_dis_all[i][j] = min(min_dis_all[i][j], min_dis_all[i][k] + min_dis_all[k][j]);
                }
            }
        }
        //初始化起点，终点
        string start;
        start = pos;
        int u;
        //遍历节点数组，找到起点的下标u
        for (int i = 0; i < num_node; i ++) {
            if (cmp(start, node[i].name)) {
                u = i;
                break;
            }
        }
        //初始化目的地节点集合
        int goto_num;                           //目的地节点数目
        vector <int> goto_node;                 //目的地节点
        goto_num = name.size();
        //对每个目的地，遍历整个节点集合，找到全部目的地的下标，存入目的地节点数组汇总
        for (int i = 0; i < goto_num; i ++) {
            string end;
            end = name[i];
            for (int j = 0; j < num_node; j ++) if (cmp(end, node[j].name)) { 
                goto_node.push_back(j); 
                break; 
            }
        }
        //保存计算出的相对最有路径
        vector<int> path;
        int dis = 0;
        //计算以u为起点，目的地节点集合为goto_node的相对最优路径，保存在path中
        ShortestMultiplePath(u, goto_node, min_dis_all, path);
        //输出最优路径
        cout << "最优路径为：";
        cout << node[u].name << "->";
        //计算总路径长度
        for (int i = 0; i < goto_num; i ++) {
            if (!i) dis += min_dis_all[u][path[i]];
            else dis += min_dis_all[path[i - 1]][path[i]];
        }
        //输出整条路径
        for (int i = 0; i < goto_num; i ++) {
            if (i != goto_num - 1) {
                cout << node[path[i]].name << "->";
            }
            else cout << node[path[i]].name;
        }
        cout << endl;
        cout << "最短距离是：" << dis << "米" << endl;
        //对求出的最优路径中，全部相邻的两节点，计算单源单目的地最短路径，输出并保存，为后续导航过程作准备
        for (int i = 0; i < goto_num; i ++) {
            //维护当前链路的起始节点和目的地
            int tempu, tempv;
            if (!i) {
                tempu = u;
                tempv = path[i];
            }
            else {
                tempu = path[i - 1];
                tempv = path[i];
            }
            //计算从当前起始节点到目的地的最短路径输出，输出是一并保存在数组中为后续导航作准备
            ShortestPath(num_node, num_edge, tempu, min_dis, pre, edge);
            //处理与输出过程与单源单目的地相同，每次输出将输出信息保存在数组中
            int path_len = 0;
            stack<int> s_path;
            stack<int> s_direct;
            stack<double> s_dis;
            stack<int> s_id;
            while(tempv && tempv != tempu) {
                s_path.push(tempv);
                s_direct.push(edge[pre[tempv]].direct);
                s_dis.push(edge[pre[tempv]].dis);
                s_id.push(pre[tempv]);
                k_ += edge[pre[tempv]].k;
                len ++;
                path_len ++;
                tempv = edge[pre[tempv]].u;
            }
            cout << "用户从" << node[tempu].name << "出发";
            while (!s_path.empty()) {
                int next, next_direct, next_id;
                double next_dis;
                next_direct = s_direct.top(); s_direct.pop(); directq.push_back(next_direct);
                next = s_path.top(); s_path.pop(); pathq.push_back(next);
                next_dis = s_dis.top(); s_dis.pop(); disq.push_back(next_dis);
                next_id = s_id.top(); s_id.pop(); idq.push_back(next_id);
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
    //询问用户是否开始导航，用户输入1则运行模拟导航，用户输入0则退出
    cout << "是否选择此导航方案,输入1选择并执行,输入0退出" << endl;
    cout << "请选择:";
    int ok;
    cin >> ok;
    if (!ok) return false;

    //模拟导航运行
    //根据拥挤程度计算平均速度
    k_ /= len;                          
    if (!v_state) {
        v = v * k_;
    }
    //维护一个已经走过的路径长度
    double dis_left;
    double dis_temp = 0;
    //单目的地
    if (name.size() == 1) {
        //路径非空，输出与上文输出相同，但同时需要计算在两分钟内走过的距离，路过的节点，最终停留的位置，在两分钟结束时以此更新用户的位置信息
        while (!path_.empty()) {
            int next, next_direct, next_id;
            double next_dis;
            next_direct = direct_.top(); 
            next = path_.top(); 
            next_dis = dis_.top(); 
            next_id = id_.top();
            //两分钟内用户可以走过此边，输出用户走过的距离，输出用户经过了该边的终点，更新用户已走过的距离dis_temp，将此条边弹出栈
            if (int(next_dis + dis_temp) < int(v)) {
                cout << "用户";
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
                cout << node[next].name << ' ' << endl;
                user.up(node[next].name, user.campus_num, my_clock);
                dis_temp += next_dis;
                direct_.pop();
                path_.pop();
                dis_.pop();
                id_.pop();
            }
            //两分钟内用户可以走过此条边并恰好停留在此条边的终点位置，输出用户走过的距离，输出用户经过了该边的终点，将此条边弹出栈
            //因用户恰好停留在终点，所以运行时钟，将dis_temp置零，同时更新用户位置信息
            else if (int(next_dis + dis_temp) == (int)(v)){
                cout << "用户";
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
                cout << node[next].name << ' ' << endl;
                dis_temp = 0;
                user.up(node[next].name, user.campus_num, my_clock);
                direct_.pop();
                path_.pop();
                dis_.pop();
                id_.pop();
                my_clock.Run();
                if (_kbhit()) {
                    char ch = getchar();
                    if (pulse(user, node, edge, my_clock)) {
                        cout << "用户选择中断导航" << endl;
                        cout << "导航结束" << endl;
                        return false;
                    }
                }
            }
            //两分钟内此用户无法走过此条边，输出用户走过的距离，更新dis_temp置零
            //此时用户会在两分钟结束时停在此边上，以此更新用户的位置信息
            //同时因为用户已经在此边上走过了一段距离，此时用户与此条边的终点的距离减少，更新用户与终点之间的距离放回栈顶
            else {
                cout << "用户";
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
                cout << int(v) - dis_temp << "米 " << endl;;
                int left;
                left = int(next_dis + dis_temp) - int(v);
                user.up(next_id, user.campus_num, left, my_clock);
                dis_.pop();
                dis_.push(left);
                dis_temp = 0;
                my_clock.Run();
                if (_kbhit()) {
                    char ch = getchar();
                    if (pulse(user, node, edge, my_clock)) {
                        cout << "用户选择中断导航" << endl;
                        cout << "导航结束" << endl;
                        return false;
                    }
                }
            }
        }
        return true;
    }
    //多目的地
    while (!pathq.empty()) {
        //处理方式与单目的地相同
        //由于多目的地的完整路径保存在vector中并非栈中，所以在vector的begin（）位置进行处理
        int next, next_direct, next_id;
        double next_dis;
        next_direct = directq[0]; 
        next = pathq[0]; 
        next_dis = disq[0]; 
        next_id = idq[0];
        if (int(next_dis + dis_temp) < int(v)) {
            cout << "用户";
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
            cout << node[next].name << ' ' << endl;
            user.up(node[next].name, user.campus_num, my_clock);
            dis_temp += next_dis;
            directq.erase(directq.begin());
            pathq.erase(pathq.begin());
            disq.erase(disq.begin());
            idq.erase(idq.begin());
        }
        else if (int(next_dis + dis_temp) == (int)(v)){
            cout << "用户";
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
            cout << node[next].name << ' ' << endl;
            dis_temp = 0;
            user.up(node[next].name, user.campus_num, my_clock);
            directq.erase(directq.begin());
            pathq.erase(pathq.begin());
            disq.erase(disq.begin());
            idq.erase(idq.begin());
            my_clock.Run();
            if (_kbhit()) {
                char ch = getchar();
                if (pulse(user, node, edge, my_clock)) {
                    cout << "用户选择中断导航" << endl;
                    cout << "导航结束" << endl;
                    return false;
                }
            }
        }
        else {
            cout << "用户";
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
            cout << int(v) - dis_temp << "米 " << endl;;
            int left;
            left = int(next_dis + dis_temp) - int(v);
            user.up(next_id, user.campus_num, left, my_clock);
            disq.erase(disq.begin());
            disq.insert(disq.begin(), left);
            dis_temp = 0;
            my_clock.Run();
            if (_kbhit()) {
                char ch = getchar();
                if (pulse(user, node, edge, my_clock)) {
                    cout << "用户选择中断导航" << endl;
                    cout << "导航结束" << endl;
                    return false;
                }
            }
        }
    }
    return true;
}

//跨校区导航
void NavigationInTwoCampus(vector<Node> & node_one, vector<Edge> & edge_one, vector<Node> & node_two, vector<Edge> & edge_two, Pos & user, string pos, vector<string> name, Clock & my_clock, vector<Time> time_table) {
    Time now;                                               //保存当前时间
    int state;                                              //保存最近的班车号
    bool ok = true;                                         //判断是否可以乘坐班车
    //初始化时钟
    now.h = my_clock.getH();
    now.m = my_clock.getM();
    //判断当前时间是否在班车与公交车的运营时间内，运营时间区间[8, 22)
    if (now.h >= 22) {
        cout << "当前时间已错过最后一班定点班车和公交车,请选择其他交通工具" << endl;
        return ;
    }
    if (now.h <= 7) {
        cout << "当前时间还未到首班定点班车和公交车发车时间，请选择其他交通工具" << endl;
        return ;
    }
    //当前时间在运营时间内
    else {
        bool flag = false;                                  //记录是否有可乘坐的班车
        //遍历班车时刻表，班车时刻表按时间顺序排序
        for (int i = 0; i < time_table.size(); i ++) {
            //若当前查询的班车时间早于用户时钟，则continue查询下一辆班车
            if (now.h > time_table[i].h || (now.h == time_table[i].h && now.m > time_table[i].m)) {
                continue;
            }
            //找到距离用户时钟最近的一班班车，判断将flag置为true表示至少存在一班班车的时间大于用户当前时钟
            int temp = 0;
            flag = true;
            //计算此辆班车与用户时钟之间的时间差
            temp += (time_table[i].h - now.h) * 60;
            temp += (time_table[i].m - now.m);
            //若时间差大于四十分钟，因乘坐公交车的平均等待时间为十分钟，则认定乘坐公交车的方案更合理，ok置false
            if (temp > 40) {
                cout << "离最近的一班定点班车发车时间还有超过四十分钟，请选择其他交通工具" << endl;
                ok = false;
            }
            //若时间差小于十五分钟，因用户赶到停车场需要一定时间，则认定用户有可能错过此次班车，认定乘坐公交车的方案更合理，ok置false
            else if (temp < 15) {
                cout << "离最近的一班定点班车发车时间还有不到十五分钟，请选择其他交通工具" << endl;
                ok = false;
            }
            //若时间在15分钟到40分钟以内，则认定乘坐班车的方案更合理，保存此次班车的下标
            else {
                state = i;
            }
            break;
        }
        //flag为false表示错过最后一班班车与公交车，提示用户选择其他交通工具
        if (!flag) {
            cout << "当前时间已错过最后一班定点班车和公交车,请选择其他交通工具" << endl;
            return ;
        }
    }
    //ok为false，乘坐公交车
    if (!ok) {
        cout << "选择公交车" << endl;
        //两个校区的公交车的站点均在校南门，首先运行单校区导航，用户根据导航前往公交车站点
        string str;
        str = "校南门";                                             //设置终点
        vector <string> temp;
        temp.push_back(str);
        //执行校区一内的单校区导航
        if (user.campus_num == 1) {
            if (!NavigationInOneCampus(node_one, edge_one, user, pos, temp, my_clock)) return ;
            cout << "等待公交车时间10分钟" << endl;
            //等待公交车的时间是五分钟，一秒模拟两分钟，执行五次
            for (int i = 0; i < 5; i ++) {
                cout << "等待公交车" << endl;
                my_clock.Run();
                if (_kbhit()) {
                    char ch = getchar();
                    if (pulse(user, node_one, edge_one, my_clock)) {
                        cout << "用户选择中断导航" << endl;
                        cout << "导航结束" << endl;
                        return ;
                    }
                }
                
            }
            //更新用户信息，表示用户正在乘坐公交车
            user.up(0, my_clock);
            cout << "乘坐公交车时间60分钟" << endl;
            //公交车运行时间60分钟，一秒模拟十分钟，执行六次
            for (int i = 0; i < 6; i ++) {
                cout << "乘坐公交车" << endl;
                my_clock.Run(0);
            }
        }
        //执行校区二内的单校区导航，与校区一相同
        else {
            if (!NavigationInOneCampus(node_two, edge_two, user, pos, temp, my_clock)) return ;
            cout << "等待公交车时间10分钟" << endl;
            for (int i = 0; i < 5; i ++) {
                cout << "等待公交车" << endl;
                my_clock.Run();
                if (_kbhit()) {
                    char ch = getchar();
                    if (pulse(user, node_two, edge_two, my_clock)) {
                        cout << "用户选择中断导航" << endl;
                        cout << "导航结束" << endl;
                        return ;
                    }   
                }
            }
            user.up(0, my_clock);
            cout << "乘坐公交车时间60分钟" << endl;
            for (int i = 0; i < 6; i ++) {
                cout << "乘坐公交车" << endl;
                my_clock.Run(0);
            }
        }
    }
    //ok为true，优先选择乘坐定点班车
    else {
        cout << "选择定点班车" << endl;
        //定点班车的站点在停车场一
        string str;
        str = "停车场一";
        vector <string> temp;
        temp.push_back(str);
        //单校区内的导航，导航到停车场一
        if (user.campus_num == 1) {
            if (!NavigationInOneCampus(node_one, edge_one, user, pos, temp, my_clock)) return ;
        }
        else {
            if (!NavigationInOneCampus(node_two, edge_two, user, pos, temp, my_clock)) return ;
        }
        //再次判断是否有可以乘坐的定点班车，若用户没有赶上前面所查询到的一班班车，因任意两班班车之间时间差较大，则认定此时没有适合的定点班车，退出
        int state = -1;
        now.h = my_clock.getH();
        now.m = my_clock.getM();
        int wait;                                                   //保存要等待的时间
        if (now.h >= 22) {
            cout << "当前时间已错过最后一班定点班车和公交车,请选择其他交通工具" << endl;
            return ;
        }
        else {
            bool flag = false;
            for (int i = 0; i < time_table.size(); i ++) {
                if (now.h > time_table[i].h || (now.h == time_table[i].h && now.m > time_table[i].m)) {
                    continue;
                }
                int temp = 0;
                flag = true;
                temp += (time_table[i].h - now.h) * 60;
                temp += (time_table[i].m - now.m);
                if (temp > 40) {
                    cout << "离最近的一班定点班车发车时间还有超过四十分钟，请选择其他交通工具" << endl;
                    return ;
                }
                else {
                    wait = temp;
                    state = i;
                    break;
                }
            }
            if (!flag) {
                cout << "当前时间已错过最后一班定点班车和公交车,请选择其他交通工具" << endl;
                return ;
            }
        }
        //输出最近一班车的信息
        cout << "等待班车,最近一班的时间为:" << time_table[state].h << "时" << time_table[state].m << "分" << endl;
        cout << "等待" << wait << "分钟" << endl;
        //等待至少wait分钟
        for (int i = 0; i < wait; i += 2) {
            my_clock.Run();
            if (user.campus_num == 1) {
                if (_kbhit()) {
                    char ch = getchar();
                    if (pulse(user, node_one, edge_one, my_clock)) {
                        cout << "用户选择中断导航" << endl;
                        cout << "导航结束" << endl;
                        return ;
                    }
                }
            }
            else {
                if (_kbhit()) {
                    char ch = getchar();
                    if (pulse(user, node_two, edge_two, my_clock)) {
                        cout << "用户选择中断导航" << endl;
                        cout << "导航结束" << endl;
                        return ;
                    }
                }
            }
        }
        //更新用户信息为正在乘坐定点班车
        user.up(1, my_clock);
        cout << "乘坐班车时间40分钟" << endl;
        //定点班车时间40分钟，一秒模拟十分钟
        for (int i = 0; i < 4; i ++) {
            cout << "乘坐班车" << endl;
            my_clock.Run(0);
        }
    }
    //定点班车或公交车运行结束，显示到达另一校区
    my_clock.ShowTime();
    cout << "到达目的地" << endl;
    //更新用户信息，此时用户所在地为另一校区的停车场
    if (!ok) {
        //更新用户所在的校区，公交车站点在另一校区的校南门，所以更新用户的位置为校南门，同时执行另一个校区内的导航，到达最终的目的地
        if (user.campus_num == 1) {
            user.up("校南门", 2, my_clock);
            if (!NavigationInOneCampus(node_two, edge_two, user, "校南门", name, my_clock)) return ;
        }
        else {
            user.up("校南门", 1, my_clock);
            if (!NavigationInOneCampus(node_one, edge_one, user, "校南门", name, my_clock)) return ;
        }
    }
    else {
        //更新用户所在的校区，定点班车站点在另一校区的停车场一，所以更新用户的位置为停车场一，同时执行另一个校区内的导航，到达最终的目的地
        if (user.campus_num == 1) {
            user.up("停车场一", 2, my_clock);
            if (!NavigationInOneCampus(node_two, edge_two, user, "停车场一", name, my_clock)) return ;
        }
        else {
            user.up("停车场一", 1, my_clock);
            if (!NavigationInOneCampus(node_one, edge_one, user, "停车场一", name, my_clock)) return ;
        }
    }
    return ;
}

//比较两字符串相等
bool cmp(string str1, string str2) {
    if (str1.length() != str2.length()) return 0;
    int length = int(str1.length());
    for (int i = 0; i < length; i ++) {
        if (str1[i] != str2[i]) return 0;
    }
    return 1;
}