#include<iostream>
#include<stdio.h>
#include<string>
#include<limits>
#include<vector>
using namespace std;
class Task {
public:
    Task() {
        ID = -1;
        des = "";
        state = "待执行";
    }
    void Task_action() {
        state = "已执行";
    }
    int ID;
    string des, state;

};
class Robot {
public:
    Robot() {
        name = "";
        for (vector<Task>::iterator it = list.begin(); it != list.end();it++) {
            it->ID = -1;
            it->des = "";
            it->state = "待执行";
        }
    }
    ~Robot() {
        for (vector<Task>::iterator it = list.begin(); it != list.end();it++) {
            if (it->ID != -1 && it->state == "待执行") {
                cout << "未执行任务ID:" << it->ID << " 描述:" << it->des << endl;
            }
        }
    }
    void add(int tem_ID, string tem_des) {
        Task m;
        m.ID = tem_ID;
        m.des = tem_des;
        list.push_back(m);
    }
    void Robot_action() {
        for (vector<Task>::iterator it = list.begin(); it != list.end(); it++) {
            if (it->ID != -1) {
                it->state = "已执行";
            }
        }
    }
    void show() {
        for (vector<Task>::iterator it = list.begin(); it != list.end(); it++) {
            if (it->ID != -1) {
                cout << "任务ID:" << it->ID << " 描述:" << it->des << " 状态:" << it->state << endl;
            }
        }
    }
    string name;
    vector<Task>list;

};
int main() {
    Robot A;
    int n = -1;
    string input;
    cin >> A.name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "请输入任务" << endl;
    while (getline(cin, input)) {
        if (input == "退出")break;
        else if (input == "执行")A.Robot_action();
        else if (input == "显示")A.show();
        else {
            int tem = 0;
            string a;
            int b;
            b = input.rfind(" ");
            for (int i = 0; i < b; i++) {
                if (input[i] >= '0' && input[i] <= '9') {  
                    tem = tem * 10 + (input[i] - '0');  
                }
            }
            a=input.substr(b+1);
            A.add(tem, a);
        }
    }
    return 0;
}