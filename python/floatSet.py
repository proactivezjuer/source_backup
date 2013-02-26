#coding=utf8
'''
浮点数集合，和一个浮点数n，从浮点数集合中找几个数使得和为n
'''
#是否找到这样的集合，找到直接退出
flag = False
#记录结果中的浮点数
result = []
#输入的浮点数n
n = 0
'''
递归函数查找和为n的浮点数集合
numbers是浮点数集合
i是当前判断的下标（numbers的下标）
cur记录当前的集合
'''
def fun(numbers, i, cur):
	#全局变量的声明，如果没有global就把它当成局部变量了
	global flag
	global result
	global n
	#求列表的和
	total = sum(cur)
	#print total
	#找到直接返回
	if flag :
		return
	else:
		#先判断是否满足条件，这个是要到i==len(numbers)结束，而不是最后一个元素结束
		if total== n:
			flag = True
			for x in cur:
				result.append(x)
		#如果大于，因为都是正数，所以可以直接剪枝了
		elif total>n:
			return
		#还有元素需要处理，进行递归处理
		elif i<len(numbers):
			#添加当前元素
			cur.append(numbers[i])
			#递归函数
			fun(numbers, i+1, cur)
			#删除列表的最后一个元素
			cur.pop()
			#在不添加当前元素的情况下递归
			fun(numbers, i+1, cur)
	
f = open('data', 'r')
numbers = []
cnt = 0
for line in f:
	cnt=cnt+1
	#字符串替换，将xxx,xxx变成xxxxxx的样式
	line = line.replace(',', '')
	if cnt==1:
		#字符串转化成浮点数
		n = float(line)
	else:
		numbers.append(float(line))
#print numbers
'''
删除最后一个元素的另一种方式
numbers.pop()
print numbers
'''
#print n
#print numbers
fun(numbers, 0, [])
#结果记录在全局变量中
#flag表示是否找到，而结果放置在result列表中
if flag:
	#将列表中的每个元素转化为浮点数
	result = [str(x) for x in result]
	#连接列表中的元素
	print '+'.join(result) +'=%.2f'%n
f.close()
