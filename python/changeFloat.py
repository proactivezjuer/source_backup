#coding=utf8
import codecs
#正则表达式
import re
import math
'''
python
将x±y替换成x±y/sqrt(n)
正则表达式操作
文件操作
编码处理
字符串操作
'''
#读取ascii码文件
#f = open("data", "r")
#读取utf8文件
f = codecs.open("data", "r", "utf8")
'''
读取所有的行放到列表中，包含换行符
lines = f.readlines()
print lines
'''
#读取第一个数字为n，转化为int型
n = int(f.readline())
while True:
	#readline最后包含换行符
	line = f.readline()
	#读取的为None，if判断为假
	if not line:
		break
	else:
		#index = line.find(u"±")
		'''
		str1 = line[0:index]
		str2 = line[index+1:-1]
		print str1
		print str2
		'''
		#正则表达式匹配
		m = re.match(ur"(.*±)(.*\d)(.*)", line)
		#如果不match直接返回None，可以使用if语句判断
		#没有读取没有匹配返回None，可以直接使用if语句判断
		if m:
			mystr = m.expand(ur"\2")
			myfloat = float(mystr)
			myfloat = myfloat/math.sqrt(n)
			#正则表达式字符串不能和普通字符串连接，使用下面的方法
			#获取匹配串，使用\i来表示
			result = m.expand(ur"\1")
			result = result+("%.2f" % myfloat)
			print result
		
#等键入enter键再退出
raw_input("press enter")
