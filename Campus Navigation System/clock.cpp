//
//  clock.cpp
//  Campus Navigation System
//
//  Created by 冯勇鑫 on 2021/4/22.
//

#include "main.hpp"
using namespace std;
void Clock::SetTime(int newH, int newM, int newS) //设置时间
{
    hour = newH;
    minute = newM;
    second = newS;
}

void Clock::ShowTime()        //显示时间，在显示时间前进行判断，如果时间设置不合适，则提示错误
{
    if (hour > 24 || hour<0 || minute>60 || minute<0 || second>60 || second < 0)
    {
        cout << "输入有误！" << endl;
        exit(0);
    }
    else
    {
        cout << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << ":" << setw(2) << setfill('0') << second << endl;
    }
}

void Clock::Run()  //实现计时功能
{

    while (1)
    {
        second += 1;
        if (second >= 60)
        {
            second -= 60;
            minute += 1;

        }
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
        usleep(1000000);
    }
}
