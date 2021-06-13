#include "main.hpp"
using namespace std;

//返回当前时间的hour
int Clock::getH() {
    return hour;
}
//返回当前时间的minute
int Clock::getM() {
    return minute;
}
//时间初始化
void Clock::SetTime(int newH, int newM)
{
    hour = newH;
    minute = newM;
}
//显示时间，在显示时间前进行判断，如果时间设置不合适，则提示错误
void Clock::ShowTime()        
{
    if (hour > 24 || hour<0 || minute>60 || minute<0 )
    {
        cout << "输入有误！" << endl;
        exit(0);
    }
    else
    {
        cout << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << endl;
    }
}
//实现计时功能
void Clock::Run()  
{
    //真实一秒模拟两分钟
    usleep(1000000);                            
    minute += 2;
    if (minute >= 60)
    {
        minute -= 60;
        hour += 1;
    }
    if (hour >= 24)
    {
        hour -= 24;
    }
    ShowTime();
}
//校区间行进
void Clock::Run(int t) {
    //真实的一秒模拟十分钟
    usleep(1000000);
    minute += 10;
    if (minute >= 60)
    {
        minute -= 60;
        hour += 1;
    }
    if (hour >= 24)
    {
        hour -= 24;
    }
    ShowTime();
}


//中断
bool pulse(Pos user, vector<Node> node, vector <Edge> edge, Clock my_clock) {
    if (pulse_) {
        char ch = getchar();
        while (true) {
            cout << "继续导航请输入1" << endl;
            cout << "中断当前导航请输入2" << endl;
            cout << "查询请输入3" << endl;
            cout << "查询日志文件请输入4" << endl;
            cout << "请输入:";
            int input; cin >> input;
            if (input == 1) {
                return false;
            }
            if (input == 2) {
                ofstream ofs;
                ofs.open("log.txt", ios::app);
                ofs << "当前时间" << my_clock.getH() << "时" << my_clock.getM() << "分," << "用户中断导航" << endl;
                ofs.close();
                getchar();
                return true;
            }
            if (input == 3) {
                Inquire(user, node, edge, my_clock);
                continue;
            }
            if (input == 4) {
                string buf;
                ifstream ifs;
                ifs.open("log.txt", ios::in);
                while (getline(ifs, buf)) {
                    cout << buf << endl;
                }
                ifs.clear(ios::goodbit);
                ifs.seekg(ios::beg);
                ifs.close();
                continue;
            }
            cout << "非法输入" << endl;
        }
    }
    else return false;
}