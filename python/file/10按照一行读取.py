with open('古诗.txt','r',encoding='utf-8') as file:       #打开模式必须是r或者r+
    s=file.readline()
    print(s)
file.close()