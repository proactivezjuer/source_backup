#include <string>
#include <stdio.h>
using namespace std;

int main ( int argc, char *argv[] )
{
 freopen("data", "r", stdin);
 const int MAX = 1005;
 char str[MAX];
 while(gets(str))
 {
 string str1(str);
 int c1=0;
 int c2=0;
 int st = 0;
 int pos;
 while((pos=str1.find('z',st))!=string::npos)    //find函数的参数颠倒了，这是常见的错误之一
 {
 c1++;
 st = pos+1;
 if(c1>1)
 break;
 }
 st = 0;
 while((pos=str1.find('j',st))!=string::npos)
 {
 c2++;
 st = pos+1;
 if(c2>1)
 break;
 }
 if(c1>1||c2>1||c1==0||c2==0)//这里不是确保了z和j都只有一个吗？
 {
 puts("Wrong Answer");
 continue;
 }
 int i1 = str1.find('z');
 int i2 = str1.find('j');
 if(i1>i2||i1-i2==1)    //为什么这里会出现i1==i2的情况呢？就因为这里导致了wa多次，如果确保了z和j都出现一次，为什么find可以找到i1==i2的情况呢
 {
 puts("Wrong Answer");
 continue;
 }
 int n1 = i1;
 int n2 = i2-i1-1;
 int n3 = str1.length()-i2-1;
 if(n1*n2==n3&&n2>0)
 {
 puts("Accepted");
 }
 else
 {
 puts("Wrong Answer");
 }


 }
 return 0;

}

//用一个表达式可以搞定的却用了许多的表达式导致了错误，但是为什么会错还是不大清除，主要是string的find函数不大清除但是却乱用了，其实手动寻找可能会更好，太依赖库函数，但是又用得不大熟练
