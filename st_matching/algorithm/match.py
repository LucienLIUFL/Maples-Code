#!/usr/bin/env python
#-*- coding:utf-8 -*-
#**********************************************************************************************
#filename:match.py
#用于采样点投影
#更新日期:201505024
#**********************************************************************************************
from math import sqrt
from tool import calculateLength
import reader
import stAnalysis
class Mapping(object):
	'''
	Mapping类
	传入采样点和路段信息
	直接调用 mappingPoint 属性即可
	比如:
	P = Mapping(Point,Road).mappingPoint
	返回 False 或 一个候选点
	'''
	def __init__(self,Point,Road):
		'''
		变量初始化和一些简单的计算
		'''
		self.Point = Point
		self.Road = Road
		self.x0 = Point[0]
		self.y0 = Point[1]
		self.x1 = Road[0][0]
		self.y1 = Road[0][1]
		self.x2 = Road[1][0]
		self.y2 = Road[1][1]
		self.DeltaX = self.x1-self.x2
		self.DeltaY = self.y1-self.y2
		self.ConstA = self.x0*self.DeltaX + self.y0*self.DeltaY
		self.ConstB = self.x2*self.DeltaY - self.y2*self.DeltaX
		self.DeltaPattern = self.DeltaY**2 + self.DeltaX**2
	def distancePointToRoad(self):
		'''
		距离判断函数,若再半径之内返回 True
		'''
		numrator = abs(self.DeltaY*self.x0 - self.DeltaX*self.y0 - self.ConstB)
		denominator = sqrt(self.DeltaPattern)
		if denominator==0:
			return False
		distance = numrator/denominator
		if distance<=0.0003:
			return True
		return False
	def judgeOutOfDistance(self):
		'''
		判断距离是否超出预期
		'''
		JuageLength1 = calculateLength(self.Point,self.Road[0])
		JuageLength2 = calculateLength(self.Point,self.Road[1])
		if JuageLength1>5.0 or JuageLength2>5.0:
			return False
		else:
			return True
	def judgePointLocation(self):
		'''
		角度判断函数,判断是否可以将点投影到路上,不能返回端点
		'''
		angle1 = (self.x1-self.x0)*self.DeltaX + (self.y1-self.y0)*self.DeltaY
		angle2 = (self.x0-self.x2)*self.DeltaX + (self.y0-self.y2)*self.DeltaY
		if angle1<0:
			return 1
		elif angle2<0:
			return 2
		else:
			return 0
	def projectPointToRoad(self):
		'''
		正常的路点匹配,返回道路上点.
		'''
		if self.DeltaX==0:
			return (self.x1, self.y0)
		elif self.DeltaY==0:
			return (self.x0, self.y1)
		else:
			x = (self.ConstA*self.DeltaX + self.ConstB*self.DeltaY)/(self.DeltaPattern)
			y = (self.ConstA*self.DeltaY - self.ConstB*self.DeltaX)/(self.DeltaPattern)
			return (x,y)
	@property
	def mappingPoint(self):
		'''
		主属性,返回点或 false
		'''
		if self.distancePointToRoad():
			possibility = self.judgePointLocation()
			if possibility==0:
				return self.projectPointToRoad()
			elif possibility==1:
				if self.judgeOutOfDistance():
					return (self.x1,self.y1)
				else:
					return False
			else:
				if self.judgeOutOfDistance():
					return (self.x2,self.y2)
				else:
					return False
		else:
			return False


