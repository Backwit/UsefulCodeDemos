#include <iostream>  
#include <string> 
#include <iostream>
#include <functional>

using namespace std;
class Func
{
public:
	int sum;
	Func()
	{
		sum = 2;
	}
	void func2(int numa, int numb, int numc,std::string name)
	{
		std::cout << numa << " " << numb << " " << numc<<" " << name<< endl ;
	}
	void func4()
	{
		std::cout << "func4" << endl;
	}
	void operator() (int a,int b)
	{
		std::cout << "Operator:" << sum<<"  "<<a<<"  "<<b<<endl;
	}
	static void  func6(int numa, int numb, int numc)
	{
		std::cout << numa << " " << numb << " " << numc << endl;
	}
	static void  func5()
	{
		std::cout << "static func" << endl;
	}
};

void callFunc(std::function<void(int a,int b)> call)
{
 call(1,2);
}
void func3()
{
 std::cout <<"func3"<< endl;
}
void func1(int numa, int numb, int numc)
{
 std::cout << numa << " " << numb << " " << numc << endl;
}

int main()
{
	Func func;
	int sum = 10;
	int resultInt = 0;
	//全局或者静态函数
	std::cout << "全局或者静态函数" << endl;
	std::function<void()> testFunc = func3;
	testFunc();
	testFunc = Func::func5;
	testFunc();
	//类成员函数
	std::cout << "类成员函数" << endl;
	testFunc = std::bind(&Func::func2, func, 1, 2, 3, "name");
	testFunc();
	//Lambda表达式
	std::cout << "Lambda表达式" << endl;
	testFunc = [=, &resultInt](){std::cout << sum << endl; resultInt += 100; };
	testFunc();
	cout << "the reslutInt is " << resultInt << endl;
	//仿函数
	std::cout << "仿函数" << endl;
	std::function<void(int a, int b)> abFunc = func;
	abFunc(10, 20);
	std::cout << resultInt << std::endl;
    return 0;
}