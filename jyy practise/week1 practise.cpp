#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
int main()
{
	int x = 0,y=0,a=0,c=0,x1,y1;
	string chturn,turnput="上";
	char turn = 'w';
	bool is = true;
	while (is)
	{
		cin >> chturn;
		if (chturn == "exit")break;
		a = 0;
		if (chturn == "w" || chturn == "s")cin >> a;
		if (chturn == "d")
		{
			switch (turn)
			{
			case'w':turn = 'd'; break;
			case'd':turn = 's'; break;
			case's':turn = 'a'; break;
			case'a':turn = 'w'; break;
			}
		}
		if (chturn == "a")
		{
			switch (turn)
			{
			case'w':turn = 'a'; break;
			case'd':turn = 'w'; break;
			case's':turn = 'd'; break;
			case'a':turn = 's'; break;
			}
		}
		if (chturn == "w")
		{
			switch (turn)
			{
			case'w':y+=a; break;
			case'd':x+=a; break;
			case's':y-=a; break;
			case'a':x-=a; break;
			}
		}
		if (chturn == "s")
		{
			switch (turn)
			{
			case'w':y -= a; break;
			case'd':x -= a; break;
			case's':y += a; break;
			case'a':x += a; break;
			}
		}
		if (turn == 'w')turnput = "上";
		if (turn == 'd')turnput = "右";
		if (turn == 's')turnput = "下";
		if (turn == 'a')turnput = "左";

		cin >> chturn>>x1>>y1;
		
		cout << "位置：（" << x << "," << y << ")方向：" << turnput << endl;
		char tem1 = turn,tem2,tem3;
		if (x == x1 &&y>y1)
		{
			switch (turn)
			{
			case'w':tem1 = 'd'; cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "," << tem1 << "]" << endl; break;
			case'd':tem1 = 'd'; cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "]" << endl; break;
			case's': cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[]" << endl; break;
			case'a':tem1 = 'a'; cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "]" << endl; break;

			}
		}
		if (x == x1 && y < y1)
		{
			switch (turn)
			{
			case's':tem1 = 'd'; cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "," << tem1 << "]" << endl; break;
			case'a':tem1 = 'd'; cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "]" << endl; break;
			case'w': cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[]" << endl; break;
			case'd':tem1 = 'a'; cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "]" << endl; break;

			}
		}
		if (y == y1 && x > x1)
		{
			switch (turn)
			{
			case'd':tem1 = 'd'; cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "," << tem1 << "]" << endl; break;
			case's':tem1 = 'd'; cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "]" << endl; break;
			case'a': cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[]" << endl; break;
			case'w':tem1 = 'a'; cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "]" << endl; break;

			}
		}
		if (y == y1 && x < x1)
		{
			switch (turn)
			{
			case'a':tem1 = 'd'; cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "," << tem1 << "]" << endl; break;
			case'w':tem1 = 'd'; cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "]" << endl; break;
			case'd': cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[]" << endl; break;
			case's':tem1 = 'a'; cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "]" << endl; break;

			}
		}
		if (x < x1 && y != y1)
		{
			a = x1 - x;
			if (turn == 'd')
			{
				tem1 = 'w';
				if ( y > y1)
				{
					tem2 = 'd';
					cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 <<" "<<a<<", "<< tem2 << "]" << endl; continue;
				}
				else
				{
					tem2 = 'a';
					cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << " " << a << ", " << tem2 << "]" << endl; continue;
				}
				
			}
			else if (turn == 'w')
			{
				tem1 = 'd';
				tem2 = 'w';
				if (y > y1)
				{
					tem3 = 'd';
					cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "," << tem2 << " " << a << ", " << tem3 << "]" << endl; continue;
				}

				else
				{
					tem3 = 'a';
					cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "," << tem2 << " " << a << ", " << tem3 << "]" << endl; continue;
				}
			}
			else if (turn == 'a')
			{
				tem1 = 's';
				if (y > y1)
				{
					tem2 = 'a';
					cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << " " << a << ", " << tem2 << "]" << endl; continue;
				}
				else
				{
					tem2 = 'd';
					cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << " " << a << ", " << tem2 << "]" << endl; continue;
				}
			}
			else if (turn == 's')
			{
				tem1 = 'a';
				tem2 = 'w';
				if (y > y1)
				{
					tem3 = 'd';
					cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "," << tem2 << " " << a << ", " << tem3 << "]" << endl; continue;
				}

				else
				{
					tem3 = 'a';
					cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "," << tem2 << " " << a << ", " << tem3 << "]" << endl; continue;
				}
			}
		}
		if (x > x1 && y != y1)
		{
			a = x - x1;
			if (turn == 'd')
			{
				tem1 = 's';
				if (y > y1)
				{
					tem2 = 'a';
					cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << " " << a << ", " << tem2 << "]" << endl; continue;
				}
				else
				{
					tem2 = 'd';
					cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << " " << a << ", " << tem2 << "]" << endl; continue;
				}

			}
			else if (turn == 'w')
			{
				tem1 = 'a';
				tem2 = 'w';
				if (y > y1)
				{
					tem3 = 'd';
					cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "," << tem2 << " " << a << ", " << tem3 << "]" << endl; continue;
				}

				else
				{
					tem3 = 'a';
					cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "," << tem2 << " " << a << ", " << tem3 << "]" << endl; continue;
				}
			}
			else if (turn == 'a')
			{
				tem1 = 'w';
				if (y > y1)
				{
					tem2 = 'd';
					cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << " " << a << ", " << tem2 << "]" << endl; continue;
				}
				else
				{
					tem2 = 'a';
					cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << " " << a << ", " << tem2 << "]" << endl; continue;
				}
			}
			else if (turn == 's')
			{
				tem1 = 'd';
				tem2 = 'w';
				if (y > y1)
				{
					tem3 = 'd';
					cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "," << tem2 << " " << a << ", " << tem3 << "]" << endl; continue;
				}

				else
				{
					tem3 = 'a';
					cout << "最近敌人位置：(" << x1 << "," << y1 << "),所需的操作：[" << tem1 << "," << tem2 << " " << a << ", " << tem3 << "]" << endl; continue;
				}
			}
		}
	}
	return 0;
}