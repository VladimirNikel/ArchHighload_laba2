#!/usr/bin/python
import socket
import os
from array import *

import subprocess


list_param = []
list_param.append(input('Введите полный путь исполняемого файла: '))

kol_vo_parametrov = int(input('Введите количество передаваемых параметров вместе с программой: '))
if kol_vo_parametrov > 0:
	for i in range(kol_vo_parametrov):
		list_param.append(input('\tВведите ' + str(i+1) + ' параметр к исполняемому файлу: '))



#вывод для себя
print('list_param = ', list_param, '\n')



subprocess.call(list_param)




print('')
#вывод hostname
print('hostname = ', socket.gethostname())

#Функция os.getcwd возвращает текущий каталог
print('pwd = ', os.getcwd())

print('сеть = ')

#вывод информации о PID'е текущего процесса
print('PID = ', os.getpid())
#написать программу, запускающую другие в контейнере
#(подержать изоляцию Hostname, файловой системы, сети, pid)
#Поддержать лимитирование по памяти.
#Реализовать с нуля без использования инструментов контейнеризации