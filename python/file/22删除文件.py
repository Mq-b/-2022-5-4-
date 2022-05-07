"""
import os
os.remove('古诗.txt')
"""

#最好像下面这样
import os.path

path='古诗.txt'
if os.path.exists(path):
    os.remove(path)
else:
    print('文件不存在')