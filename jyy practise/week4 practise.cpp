#include<stdio.h>
#include<thread>
#include<mutex>
#include<atomic>
#include<vector>
#include<chrono>
#include<iostream>
#include<condition_variable>
using std::cout;
using std::endl;
using std::thread;
using std::vector;
using std::mutex;
std::condition_variable cv;
mutex mtx;
class Task {
public:
	virtual void run() = 0;
	virtual void callback(int msg) = 0;
	void stop() {
		is = false;
	}
	Task() : running(&Task::run, this),ready(false){}
	virtual ~Task() {
		stop();
		if (running.joinable()) {
			running.join();
		}
	}
	thread running;
	int key=0;
	std::atomic<int>* p1;
	std::atomic<int>* p2;
	std::atomic<bool>is{true};
	std::atomic<bool>ready;
};
class Task1 :public Task {
public:
	virtual void run() override 
	{
		while (is) {
			if (*p1 != 0) {
				std::lock_guard<mutex> lock(mtx);
				*p2 = *p1 + 1;
				*p1 = 0;
				cout <<"Task1: " << key << "  " << *p2 << endl;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	virtual void callback(int msg) override
	{
		*p1 = msg;
	}
	~Task1()override {
		stop();
		if (running.joinable()) {
			running.join();
		}
		if (p1 != nullptr && p2 != nullptr) {
			//delete p1;
			//delete p2;
			p1 = nullptr;
			p2 = nullptr;
		}
	}
};
class Task2 :public Task {
public:
	virtual void run() override
	{
		while (is) {
			if (*p1 != 0) {
				std::lock_guard<mutex> lock(mtx);
				*p2 = (*p1) * k;
				*p1 = 0;
				//std::lock_guard<mutex> outputlock(all);
				cout << "Task2: " << key << "  " << *p2 << endl;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	virtual void callback(int msg) override
	{
		k = msg;
		*p1 = 1;
	}
	~Task2()override {
		stop();
		if (running.joinable()) {
			running.join();
		}
		if (p1 != nullptr && p2 != nullptr) {
			//delete p1;
			//delete p2;
			p1 = nullptr;
			p2 = nullptr;
		}
	}
	int k = 1;
};
class Task3 :public Task {
public:
	virtual void run() override
	{
		while (is) {
			if (*p1 != 0) {
				std::lock_guard<mutex> lock(mtx);
				t = *p1;
				*p1 = 0;
				*p2 = t;
				//std::lock_guard<mutex> outputlock(all);
				cout << "Task3: " << key << "  " << *p2 << endl;
				*p2 = t + 1;
				cout << "Task3: " << key << "  " << *p2 << endl;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		
	}
	virtual void callback(int msg) override
	{
		*p1 = msg;
	}
	~Task3()override {
		stop();
		if (running.joinable()) {
			running.join();
		}
		if (p1 != nullptr && p2 != nullptr) {
			//delete p1;
			//delete p2;
			p1 = nullptr;
			p2 = nullptr;
		}
	}
	int t=0;
};
class TaskManager {
public:
	void add() {
		std::lock_guard<mutex> lock(mtx);
		int tem_key;
		std::string kind;
		std::cin >> tem_key >> kind;
		Task* a = nullptr;
		if (kind == "Task1") a = new Task1();
		else if (kind == "Task2") a = new Task2();
		else  a = new Task3();
		a->key = tem_key;
		if (Tasklist.empty()) {
			Tasklist.push_back(a);
			an.push_back(std::make_unique<std::atomic<int>>(0));
			auto it = an.end() - 1;
			Tasklist[0]->p1 = it->get();
			Tasklist[0]->p2 = &out;
		}
		else {
			Tasklist.push_back(a);
			an.push_back(std::make_unique<std::atomic<int>>(0));
			auto it = an.end() - 1;
			Tasklist.back()->p1 = it->get();
			--it;
			Tasklist.back()->p2 = it->get();
		}
		Tasklist.back()->ready = true;
	}
	void pop() {
		std::lock_guard<mutex> lock(mtx);
		Task* tem_task = Tasklist.back();
		tem_task->stop();
		if (tem_task->running.joinable()) {
			tem_task->running.join();
		}
		delete tem_task;
		Tasklist.pop_back();
		an.pop_back();
		//std::lock_guard<mutex> outputlock(all);
		cout << "已经删除最后一个任务" << endl;
	}
	void callbackuse() {
		int tem_key, msg;
		std::cin >> tem_key >> msg;
		vector<Task*>::iterator it;
		for (it = Tasklist.begin(); it != Tasklist.end(); it++) {
			if ((*it)->key == tem_key)break;
		}
		(*it)->callback(msg);
	}
	std::atomic<int>out{0};
	vector<std::unique_ptr<std::atomic<int>>> an;
	vector<Task*>Tasklist;
	mutex mtx;
};
void action_1(TaskManager &A) {
	while (1) {
		if (A.out != 0) {
			std::lock_guard<mutex> lock(mtx);
			cout << "out为：" << A.out << endl;
			A.out = 0;
			cv.notify_one();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
void action_2(TaskManager &A) {
	mutex all;
	while (1) {
		std::string instruction;
		//std::lock_guard<mutex> outputlock(all);
		cout << "请输入指令" << endl;
		std::cin >> instruction;
		if (instruction == "add") {
			A.add();
		}
		else if (instruction == "pop") {
			A.pop();
		}
		else {
			std::unique_lock<mutex> outputlock(all);
			A.callbackuse();
			cv.wait(outputlock);
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
int main() {
	TaskManager ALL;
	ALL.an.reserve(10000);
	thread at(action_1, std::ref(ALL));
	thread ar(action_2, std::ref(ALL));
	at.join();
	ar.join();
	return 0;
}