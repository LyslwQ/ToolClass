/*************************************************************************
    > File Name: main.cpp
    > Author: Ys
    > Created Time: 2019年01月30日 星期三 14时22分48秒
 ************************************************************************/
#include <unistd.h>
#include "Sentinel.h"

int main(void)
{
	Sentinel  sentinel("placeHolder");
	while(1){
		sentinel.handleFiles();
		sleep(3);
	}
	return 0;
}
