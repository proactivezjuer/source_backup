#coding=utf8
from wx import *
import random
'''
用使用中文必须得#coding=utf8
这是一个随机数产生器
python 图形用户界面
'''

#声明一个class
class MyFrame(Frame):
	#构造函数__init__(self)，每个函数都有一个self对象
	def __init__(self):
		#父类的构造函数
		Frame.__init__(self, None, -1, u'珍珍老婆牌随机数产生器', size=(500,500))
		#frame上添加一个panel
		panel = Panel(self, -1)
		#平均值开始
		#声明一个文本标签
		meanText = StaticText(panel, -1, u'平均值：', pos=(10,10))
		#设置文本背景
		meanText.SetForegroundColour('red')
		#设置字体
		font = Font(pointSize=18, family=DEFAULT, style=NORMAL, weight=BOLD)
		meanText.SetFont(font)
		#声明一个文本框
		self.meanInput = TextCtrl(panel,111,'',(100,15),Size(100,25))
		#平均值结束

		#标准差开始
		deviationText = StaticText(panel, -1, u'标准差：', pos=(10,50))
		deviationText.SetForegroundColour('red')
		font = Font(pointSize=18, family=DEFAULT, style=NORMAL, weight=BOLD)
		deviationText.SetFont(font)
		self.deviationInput = TextCtrl(panel,111,'',(100,55),Size(100,25))
		#标准差结束

		#产生按钮
		button = wx.Button(panel, label=u'提交', pos=(225, 55), size=(70, 30))
		#在button上添加事件处理函数，一般事件处理函数作为类的方法，可以使用内部成员
		self.Bind(EVT_BUTTON, self.cal, button)
		#产生按钮结束


		#数量开始
		numberText = StaticText(panel, -1, u'数量：', pos=(10,90))
		numberText.SetForegroundColour('red')
		font = Font(pointSize=18, family=DEFAULT, style=NORMAL, weight=BOLD)
		numberText.SetFont(font)
		self.numberInput = TextCtrl(panel,111,'',(100,95),Size(100,25))
		#数量结束

		#内容文本框
		#滚动文本框
		self.contents = TextCtrl(panel,-1,'', (20,130),Size(450, 300),style=wx.TE_MULTILINE|wx.HSCROLL)
		#快捷键处理
		self.contents.Bind(EVT_CHAR, self.keyPress)
		#内容文本框结束
	
	#事件处理函数一般传递一个event对象
	def cal(self, event):
		try:
			#获取文本框中的值
			mean = float(self.meanInput.GetValue())
			deviation = float(self.deviationInput.GetValue())
			number = int(self.numberInput.GetValue())
			result = ''
			for i in range(number):
				#产生随机数
				rn = random.normalvariate(mean, deviation)
				#字符串格式化
				result += ("%.1f\n" % rn)
			#设置文本框的值
			self.contents.SetValue(result)
		except ValueError, e:
			self.contents.SetValue(u'请输入正确的值')

	#快捷键处理
	def keyPress(self, evt):
		keycode = evt.GetKeyCode()
		#ctrl+a的编码为1
		if keycode==1:
			self.contents.SelectAll()


#如果有__name__=="__main__"，可以避免其作为模块被引入时执行这些代码
if __name__ == "__main__":
	#声明一个app
	app = PySimpleApp()
	#声明定义一个frame
	frame = MyFrame()
	#显示frame，记住都是大写
	frame.Show(True)
	app.MainLoop()
