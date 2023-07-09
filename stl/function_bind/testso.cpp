#include "testso.h"
#include<iostream>

using namespace std;

void mysofun(std::function<void()> call) {
	std::cout<<"it is my so\n";
	call();
}