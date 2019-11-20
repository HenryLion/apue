/* 目的：本程序主要测一下在调用的函数中使用exit调用时主程序会不会推出 */
/* 结果：从测试结果来看，主程序在调用函数时如果函数里面调用了exit系列函数则主程序会推出的 */
/* atexit函数的调用需要在sum函数之前，否则main退出的时候不会调用atexit注册的函数 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sum (int a, int b)
{
	int c = a + b;
	printf ("sum is %d\n", c);
	exit (0);
}

void exit_handler (void)
{
	printf ("this is the eixt handler\n");
}

int main (void)
{
	int a = 3; 
	int b = 4;
	atexit (exit_handler);
	sum (a, b);
	printf ("main will return\n");
	return 0;
}


void hello ()
{
	return;
}
