#!/usr/bin/env python
#-*- coding:utf-8 -*-
#**********************************************************************************************
#filename:tool.py
# 用于一些用到的数学简单方法
#更新日期:201505024
#**********************************************************************************************
import math
import matplotlib.pyplot as plt 
import numpy as np 

def calculateLength(Point1,Point2):
	'''
	球面距离计算函数,返回输入点之间的距离(米)
	'''
	x1 = Point1[0]
	y1 = Point1[1]
	x2 = Point2[0]
	y2 = Point2[1]
	if y1==y2:
		return 6371.393*abs(x1-x2)
	else:
		return 6371.393*math.acos(math.sin(x1*1.0)*math.sin(1.0*x2)+math.cos(1.0*x1)*math.cos(1.0*x2)*math.cos(1.0*(y1-y2)))


def normalDistribution(x, Sigma=20.0, Mu=0.0):
	'''
	正态分布计算函数
	范湖输入值的概率
	Sigma 缺省值为20
	Mu 缺省值为0.0
	'''
	const = 1/(math.sqrt(math.pi*2)*Sigma)
	parameter = -1.0*(x**2/(2*(Sigma**2)))
	return const*(2.718281828459045**parameter)


def removeRedundancy(QureyNodeList,CandidateNodeList):
	'''
	去重函数,去除前后重复的候选点
	'''
	temp = CandidateNodeList[0]
	for i in CandidateNodeList[1:]:
		judge = 0
		for j in temp:
			if j in i:
				judge = 1
				break 
		if judge:
			QureyNodeList.pop(CandidateNodeList.index(i))
			CandidateNodeList.remove(i)
			continue
		else:
			temp = i
	return QureyNodeList,CandidateNodeList

def findMaxElement(Argument):
	if not type(max(Argument))==list:
		return max(Argument)
	else:
		return findMaxElement(max(Argument))










