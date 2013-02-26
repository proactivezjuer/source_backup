#coding=utf8
def checkio(input_data):
    'Return password of given cipher map'
	#列表中的元素可以直接赋值给变量
    a, b=input_data
    indexs = []
    for i in range(4):
        for j in range(4):
            if a[i][j] == 'X':
				#选取为X的坐标
                indexs.append((i, j))
    #print indexs
    result = ''
    
    for i in range(4):
		#要排序坐标列表
        indexs.sort()
        for j in range(4):
            index = indexs[j]
            result = result+b[index[0]][index[1]]
			#选择90度的坐标变换
            indexs[j] = (index[1], 3-index[0])
    return result
            
        
    

if __name__ == '__main__':
    assert checkio([[
    'X...',
    '..X.',
    'X..X',
    '....'],[
    'itdf',
    'gdce',
    'aton',
    'qrdi']]) == 'icantforgetiddqd', 'First'

    assert checkio( [[
    '....',
    'X..X',
    '.X..',
    '...X'],[
    'xhwc',
    'rsqx',
    'xqzz',
    'fyzr']]) == 'rxqrwsfzxqxzhczy', 'Second'
    print('All ok')
