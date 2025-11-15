#include<iostream>
#include<stdio.h>
#include<string>
#include<limits>
#include<vector>
#include<map>
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
        for (vector<Task>::iterator it = Tasklist.begin(); it != Tasklist.end(); it++) {
            it->ID = -1;
            it->des = "";
            it->state = "待执行";
        }
    }
    ~Robot() {
        for (vector<Task>::iterator it = Tasklist.begin(); it != Tasklist.end(); it++) {
            if (it->ID != -1 && it->state == "待执行") {
                cout <<name<<"未执行任务ID:" << it->ID << " 描述:" << it->des << endl;
            }
        }
    }
    void addTask(int tem_ID, string tem_des) {
        Task m;
        m.ID = tem_ID;
        m.des = tem_des;
        Tasklist.push_back(m);
    }
    void Robot_action() {
        for (vector<Task>::iterator it = Tasklist.begin(); it != Tasklist.end(); it++) {
            if (it->ID != -1) {
                it->state = "已执行";
            }
        }
    }
    void showTask() {
        for (vector<Task>::iterator it = Tasklist.begin(); it != Tasklist.end(); it++) {
            if (it->ID != -1) {
                cout <<"任务ID:" << it->ID << " 描述:" << it->des << " 状态:" << it->state << endl;
            }
        }
    }
    void cancelTask() {
        Tasklist.pop_back();
    }
    string name;
    vector<Task>Tasklist;

};
class TaskSeduler {
public:
    void addRobot(string tem_a,Robot tem_b) {
        Robotlist[tem_a] = tem_b;
        Robotname.push_back(tem_a);
    }
    void cancelRobot(string tem_a) {
        Robotlist.erase(tem_a);
        for (vector<string>::iterator it = Robotname.begin(); it != Robotname.end(); it++) {
            if (*it == tem_a) {
                Robotname.erase(it);
                break;
            }
        }
    }
    void search(string tem_a) {
        cout << tem_a << "的任务为:" << endl;
       // Robot tem_robot = Robotlist.find(tem_a)->second;
        Robotlist.find(tem_a)->second.showTask();
    }
    void showRobot() {
        for (vector<string>::iterator it = Robotname.begin(); it != Robotname.end(); it++) {
            cout << *it << endl;
        }
    }
    map<string, Robot>Robotlist;
    vector<string>Robotname;
};
int main() {
    TaskSeduler A;

    cout << "请输入指令" << endl;
    string input;
    while (getline(cin, input)) {
        int a = input.find(" ");
        if (input == "退出")break;
        if (input == "获取机器人名称列表")A.showRobot();
        else if (input.substr(0, a) == "添加机器人") {
            Robot new_robot;
            new_robot.name = input.substr(a + 1);
            A.addRobot(input.substr(a + 1), new_robot);
        }
        else if (input.substr(0, a ) == "添加任务") {
            int b = input.rfind(" "),tem=0;
            string n = input.substr(0, b);
            int c = n.rfind(" ");
            for (int i = c; i < b; i++) {
                if (input[i] >= '0' && input[i] <= '9') {
                    tem = tem * 10 + (input[i] - '0');
                }
            }
           // Robot tem_robot = A.Robotlist.find(input.substr(a + 1, c-a-1))->second;
            A.Robotlist.find(input.substr(a + 1, c - a - 1))->second.addTask(tem, input.substr(b + 1));
        }
        else if (input.substr(0, a ) == "撤销任务") {
          //  Robot tem_robot = A.Robotlist.find(input.substr(a + 1))->second;
            A.Robotlist.find(input.substr(a + 1))->second.cancelTask();
        }
        else if (input.substr(0, a ) == "执行任务") {
          //  Robot tem_robot = A.Robotlist.find(input.substr(a + 1))->second;
            A.Robotlist.find(input.substr(a + 1))->second.Robot_action();
        }
        else if (input.substr(0, a ) == "删除机器人") {
            A.cancelRobot(input.substr(a + 1));
        }
        else if (input.substr(0, a ) == "查询任务") {
            string tem_name = input.substr(a + 1);
            A.search(tem_name);
        }
    }
    return 0;
}