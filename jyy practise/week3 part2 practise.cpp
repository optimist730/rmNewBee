#include<iostream>
#include<stdio.h>
#include<string>
#include<limits>
#include<vector>
#include<map>
#include<set>
using namespace std;
class Task {
public:
    Task() {
        priority = 0;
        ID = -1;
        des = "";
        state = "待执行";
    }
    void Task_action() {
        state = "已执行";
    }
    int ID,priority;
    string des, state;

};
class mycompare {
public:
    bool operator()(const Task& p1, const Task& p2)const {
        return p1.priority > p2.priority;
    }
};
class Robot {
public:
    Robot() {
        name = "";
        for (set<Task,mycompare>::iterator it = Tasklist.begin(); it != Tasklist.end(); it++) {
            Task tem_task = *it;
            Tasklist.erase(it);
            tem_task.ID = -1;
            tem_task.des = "";
            tem_task.state = "待执行";
            Tasklist.insert(tem_task);
        }
    }     
    ~Robot() {
        for (set<Task,mycompare>::iterator it = Tasklist.begin(); it != Tasklist.end(); it++) {
            if (it->ID != -1 && it->state == "待执行") {
                cout <<name<<"未执行任务ID:" << it->ID << " 描述:" << it->des << endl;
            }
        }
    }
    void addTask(int tem_ID, string tem_des,int tem_priority) {
        Task m;
        m.ID = tem_ID;
        m.des = tem_des;
        m.priority = tem_priority;
        Tasklist.insert(m);
    }
    void Robot_action() {
        Task tem_task = *Tasklist.begin();
        Tasklist.erase(Tasklist.begin());
        tem_task.state = "已执行";
        Tasklist.insert(tem_task);
    }
    void showTask() {
        for (set<Task,mycompare>::iterator it = Tasklist.begin(); it != Tasklist.end(); it++) {
            if (it->ID != -1) {
                cout <<"任务ID:" << it->ID << " 描述:" << it->des << " 状态:" << it->state << endl;
            }
        }
    }
    void cancelTask() {
        Tasklist.erase(--Tasklist.end());
    }
    string name;
    set<Task,mycompare>Tasklist;

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
            vector<int>at;
            for (int i = 0; i < input.length(); i++) {
                if (input[i] == ' ') {
                    at.push_back(i);
                }
            }
            int tem1 = 0,tem2=0;
            for (int i = at[1]; i < at[2]; i++) {
                if (input[i] >= '0' && input[i] <= '9') {
                    tem1 = tem1 * 10 + (input[i] - '0');
                }
            }
            for (int i = at[3]; i < input.length(); i++) {
                if (input[i] >= '0' && input[i] <= '9') {
                    tem2 = tem2 * 10 + (input[i] - '0');
                }
            }
            A.Robotlist.find(input.substr(at[0] + 1, at[1] - at[0] - 1))->second.addTask(tem1, input.substr(at[2] + 1, at[3] - at[2] - 1), tem2);
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