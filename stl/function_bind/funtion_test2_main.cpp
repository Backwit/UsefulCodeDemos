#include <string> 
#include <iostream>
#include <functional>
#include <dlfcn.h>

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
};

 void callFunc(std::function<void(int a,int b)> call)
 {
	 call(1,2);
 }

void callmyfunc(std::function<void()> call) {
	std::cout<<"my func\n";
	call();
}

int main()
{
	Func func;
	int sum = 10;
	int resultInt = 0;
	//类成员函数
	std::function<void()> testFunc = std::bind(&Func::func2, func, 1, 2, 3, "name");
	testFunc();
	callmyfunc(testFunc);

	char path[100] = "/lxh/stl_learn/callback/libmyso.so";
	void* handle = dlopen(path, RTLD_LAZY);
	if (!handle) {
		std::cout<<"error\n";
		return 0;
	}
    dlerror();
	void (*mysofunc) (std::function<void()> call);
	mysofunc =(void (*)(std::function<void()>)) dlsym(handle, "mysofun");
	const char *errmsg = dlerror(); 
	if (errmsg != NULL) {
		std::cout<<"dlerror:"<<errmsg<<std::endl;
		return -1;
	}	

    mysofunc(testFunc);

	dlclose(handle);

	using std::placeholders::_1;
	using std::placeholders::_2;
	std::function<void(int, int)> testFunc2 = std::bind(&Func::func2, &func, _1, _2, 3, "name");
	testFunc2(5, 6);

	return 0;
}