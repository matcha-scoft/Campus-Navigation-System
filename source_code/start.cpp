#include "main.hpp"
using namespace std;

//前缀匹配，若str1是str2的前缀则返回true
bool StrCompare(string str1, string str2) {
    if (str1.length() > str2.length()) return false;
    for (int i = 0; i < str1.length(); i ++) {
        if (str1[i] != str2[i]) return false;
    }
    return true;
}

//启动系统，读取用户起点，终点
void StartSystem(vector <Node> & node_one, vector <Edge> & edge_one, vector <Node> & node_two, vector <Edge> & edge_two, Pos & user, Clock & my_clock, vector<Time> time_table) {
    cout << "系统启动" << endl;
    //时间初始化为早上八点
    my_clock.SetTime(8, 0);
    cout << "当前时间为：";
    my_clock.ShowTime();
    //循环处理请求，当用户输入目的地数目为零时结束循环退出系统
    while (true) {
        bool add = false;                                      //记录下是否有新加入的边，导航结束后add为true则删除新加入的边
        int s_campus;                                          //保存用户所在的校区
        string pos;                                            //保存用户所在位置的name，若用户在节点上则为节点的name，否则为“user”
        //user.flag为false，用户未初始化，提醒用户输入起点，起点为一个节点
        if (!user.flag) {
            //读取起点，起点校区
            string temp_pos;                                   //起点名称
            vector<string> s_name;                             //暂存备选节点name
            vector<int> s_cam;                                 //暂存备选节点校区，与s_name一一对应
            cout << "请输入您当前位置:";
            cin >> temp_pos;                                   //用户输入位置信息
            //遍历校园一，校园二，根据用户输入查询符合条件的备选节点
            int num = 1, num_one = 0, num_two = 0;             //计数器
            cout << "校区一:" << endl;
            for (int i = 1; i < node_one.size(); i ++) {
                //前缀匹配，若用户输入为当前节点的name的前缀，则将当前节点加入备选节点，更新计数器
                if (StrCompare(temp_pos, node_one[i].name)) {
                    cout << "地点" << num << ':' << node_one[i].name << endl;
                    num_one ++;
                    num ++;
                    s_name.push_back(node_one[i].name);        //插入节点name
                    s_cam.push_back(1);                        //校区一
                }
            }
            if (num_one == 0) cout << "未找到有效位置！" << endl; //校区一计数器为零，输出提示
            //遍历校园二
            cout << "校区二:" << endl;
            for (int i = 1; i < node_two.size(); i ++) {
                if (StrCompare(temp_pos, node_two[i].name)) {
                    cout << "地点" << num << ':' << node_two[i].name << endl;
                    num_two ++;
                    num ++;
                    s_name.push_back(node_two[i].name);
                    s_cam.push_back(2);
                }
            }
            if (num_two == 0) cout << "未找到有效位置!" << endl;
            //当num等于1表示用户输入的位置不存在
            if (num == 1) {
                cout << "起点不存在!" << endl;
                continue;
            }
            //用户从全部备选节点中选择自己的起始位置，输入选择节点的编号
            int temp;
            cout << "请选择您的起点编号:";
            cin >> temp;
            pos = s_name[temp - 1];                             //更新用户所在位置
            s_campus = s_cam[temp - 1];                         //更新用户所在校区
            //输出提示
            cout << "起点:" << pos << endl;
            cout << "校区:" << s_campus << endl;
            //更新用户信息，并查询用户附近节点
            user.up(pos, s_campus,my_clock);
            if (s_campus == 1) Inquire(user, node_one, edge_one, my_clock);
            else Inquire(user, node_two, edge_two, my_clock);
        }
        //user.flag为true，不需用户再次输入，系统根据用户的状态信息进行初始化
        //用户在节点上
        else if (!user.state) {
            pos = user.pos;                                     //初始化起点为用户所在节点
            s_campus = user.campus_num;                         //初始化起点校区为用户所在校区
        }
        //用户在边上，添加两条边由用户指向用户所在边的起点和终点
        else {
            add = true;                                         //标记add为true
            Edge new_edge[2];
            //若用户在校区一
            if (s_campus == 1) {
                //新建两条边初始化，由用户指向所在边的起点和终点，距离初始化
                new_edge[0] = edge_one[user.pos_num];
                new_edge[0].u = 0;
                new_edge[0].dis = user.dis;
                new_edge[1] = new_edge[0];
                new_edge[1].v = edge_one[user.pos_num].u;
                new_edge[1].dis = edge_one[user.pos_num].dis - new_edge[0].dis;
            }
            //用户在校区二
            else {
                new_edge[0] = edge_two[user.pos_num];
                new_edge[0].u = 0;
                new_edge[0].dis = user.dis;
                new_edge[1] = new_edge[0];
                new_edge[1].v = edge_two[user.pos_num].u;
                new_edge[1].dis = edge_two[user.pos_num].dis - new_edge[0].dis;
            }
            //方向初始化，new_edge[1]与new_edge[0]的方向相反
            switch(new_edge[0].direct) {
                case 0:
                    new_edge[1].direct = 1;
                    break;
                case 1:
                    new_edge[1].direct = 0;
                    break;
                case 2:
                    new_edge[1].direct = 3;
                    break;
                case 3:
                    new_edge[1].direct = 2;
                    break;
            }
            //将新建的边加入边集合中
            if (s_campus == 1) {
                for (int i = 0; i < 2; i ++) {
                    edge_one.push_back(new_edge[i]);
                }
            }
            else {
                for (int i = 0; i < 2; i ++) {
                    edge_two.push_back(new_edge[i]);
                }
            }
            pos = "user";                                       //起点名称为user
            s_campus = user.campus_num;
        }
        //读取目的地，单目的地或多目的地
        vector<string> name;                                    //目的地名称
        int des_num;                                            //目的地数目
        int des_campus = 0;                                     //目的地校区
        vector <string> des_name;                               //暂存备选目的地name
        vector <int> des_cam;                                   //暂存备选目的地校区
        cout << "请输入目的地数:";
        cin >> des_num;                                         //读取目的地数目
        //目的地数为0，退出系统
        if (des_num == 0) break;
        //读取全部目的地name
        for (int i = 0; i < des_num; i ++) {
            //清空备选目的地
            des_name.clear(); des_cam.clear();
            //读取目的地
            cout << "请输入目的地" << i + 1 << ':';
            string des;
            int num = 1, num_one = 0, num_two = 0;               //计数器
            cin >> des;                                          
            //读取校区一物理地址，方法与读取起点相同
            cout << "校区一:" << endl;
            for (int j = 1; j < node_one.size(); j ++) {
                if (StrCompare(des, node_one[j].name)) {
                    cout << "地点" << num << ':' << node_one[j].name << endl;
                    num_one ++;
                    num ++;
                    des_name.push_back(node_one[j].name);
                    des_cam.push_back(1);
                }
            }
            //读取校区一逻辑地址文件，将匹配成功的全部逻辑地址与对应物理地址打印，并加入备选目的地数组
            ifstream ifs;
            string buf;
            ifs.open("campusone.txt", ios::in);
            //读取一行即为一条逻辑地址映射
            while (getline(ifs, buf)) {
                string temp;
                string str1, str2;
                temp.clear();
                //将逻辑地址映射中的逻辑地址与物理地址分开，用空格隔开
                for (int i = 0; i < buf.size(); i ++) {
                    //读取到空格则将temp赋值给str1，后清空temp
                    if (buf[i] == ' ') {
                        str1 = temp;
                        temp.clear();
                    }
                    //不是空格则插入temp
                    else {
                        temp.push_back(buf[i]);
                    }
                }
                //读取完全部字符将temp赋值给str2
                str2 = temp;
                //前缀匹配，匹配成功则将逻辑地址与物理地址全部输出，并将物理地址加入备选目的地数组
                if (StrCompare(des, str1)) {
                    cout << "地点" << num << ':' << "逻辑位置:" << str1 << ",物理地点:" << str2 << endl;
                    num_one ++;
                    num ++;
                    des_name.push_back(str2);
                    des_cam.push_back(1);
                }
            }
            ifs.close();
            //计数器为零输出提示信息
            if (num_one == 0) cout << "未找到有效目的地！" << endl;
            //读取校区二，与读取校区一相同
            cout << "校区二:" << endl;
            for (int j = 1; j < node_two.size(); j ++) {
                if (StrCompare(des, node_two[j].name)) {
                    cout << "地点" << num << ':' << node_two[j].name << endl;
                    num_two ++;
                    num ++;
                    des_name.push_back(node_two[j].name);
                    des_cam.push_back(2);
                }
            }
            ifs.open("campustwo.txt", ios::in);
            while (getline(ifs, buf)) {
                string temp;
                string str1, str2;
                for (int i = 0; i < buf.size(); i ++) {
                    if (buf[i] == ' ') {
                        str1 = temp;
                        temp.clear();
                    }
                    else {
                        temp.push_back(buf[i]);
                    }
                }
                str2 = temp;
                if (StrCompare(des, str1)) {
                    cout << "地点" << num << ':' << "逻辑位置:" << str1 << ",物理地点:" << str2 << endl;
                    num_two ++;
                    num ++;
                    des_name.push_back(str2);
                    des_cam.push_back(2);
                }
            }
            ifs.close();
            if (num_two == 0) cout << "未找到有效目的地!" << endl;
            //计数器判断，没有符合索引条件的目的地，要求用户重新输入
            if (num == 1) {
                cout << "目的地不存在!" << endl;
                i --;
                continue;
            }
            //用户通过编号选择目的地
            int temp;
            cout << "请选择您的目的地编号:";
            cin >> temp;
            //若目的地校区为0即未被初始化，则将当前用户选择的目的地的校区赋值给目的地校区，将当前选择的目的地插入目的地数组
            //若目的地校区不为0即已被初始化，则判断当前用户选择的新目的地与保存的目的地校区是否相同
            //相同则将当前选择的目的地插入目的地数组
            if (des_campus == 0 || des_campus == des_cam[temp - 1]) {
                des_campus = des_cam[temp - 1];
                name.push_back(des_name[temp - 1]);
            }
            //不同则输出提示，不支持多目的地的跨校区导航，要求用户重新输入目的地
            else {
                cout << "不支持跨校区多目的地导航!"  << endl;
                i --;
                continue;
            }
        }
        ofstream ofs;
        ofs.open("log.txt", ios::app);
        //目的地数量为1，则执行单目的地导航，判断目的地校区和用户起点校区是否相同，调用不同的导航函数
        if (des_num == 1) {
            //同校区导航
            if (s_campus == des_campus) {
                //校区一导航
                if (s_campus == 1) {
                    ofs << "当前时间" << my_clock.getH() << "时" << my_clock.getM() << "分 ";
                    ofs << "用户搜索地点:" << endl;
                    ofs << "校区一:" << name[0] << endl;
                    NavigationInOneCampus(node_one, edge_one, user, pos, name, my_clock);
                }
                //校区二导航
                else {
                    ofs << "当前时间" << my_clock.getH() << "时" << my_clock.getM() << "分 ";
                    ofs << "用户搜索地点:" << endl;
                    ofs << "校区二:" << name[0] << endl;
                    NavigationInOneCampus(node_two, edge_two, user, pos, name, my_clock);
                }
            }
            //跨校区导航
            else {
                ofs << "当前时间" << my_clock.getH() << "时" << my_clock.getM() << "分 ";
                ofs << "用户搜索地点:" << endl;
                ofs << "跨校区:" << name[0] << endl;
                NavigationInTwoCampus(node_one, edge_one, node_two, edge_two, user, pos, name, my_clock, time_table);
            }
        }
        //目的地数目不为1，判断目的地校区与起点校区是否在同一校区，不在则输出提示
        else {
            //不在同一校区
            if (s_campus != des_campus) {
                cout << "不支持跨校区多目的地导航!"  << endl;
                continue;
            }
            cout << "默认最后一个目的地为最终目的地" << endl;
            //在同一校区，执行同一校区导航
            if (s_campus == 1) {
                ofs << "当前时间" << my_clock.getH() << "时" << my_clock.getM() << "分 ";
                ofs << "用户搜索地点:" << endl;
                for (int i = 0; i < des_num; i ++) {
                    ofs << name[i] << endl;
                }
                NavigationInOneCampus(node_one, edge_one, user, pos, name, my_clock);
            }
            else {
                ofs << "当前时间" << my_clock.getH() << "时" << my_clock.getM() << "分 ";
                ofs << "用户搜索地点:" << endl;
                for (int i = 0; i < des_num; i ++) {
                    ofs << name[i] << endl;
                }
                NavigationInOneCampus(node_two, edge_two, user, pos, name, my_clock);
            }
        }
        //导航结束后根据add符号标记，删除新加入的边
        if (add) {
            if (s_campus ==1 ) {
                edge_one.erase(edge_one.end() - 1);
                edge_one.erase(edge_one.end() - 1);
            }
            else {
                edge_two.erase(edge_two.end() - 1);
                edge_two.erase(edge_two.end() - 1);
            }
        }
        ofs.close();
    }
}
