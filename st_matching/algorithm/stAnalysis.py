#!/usr/bin/env python
#-*- coding:utf-8 -*-
from tool import calculateLength
from tool import normalDistribution
import networkx as nx
import reader
import match
from math import sqrt
def matchMapPoint(Point,Nodes,Edges):
	'''
	将候选点匹配到路段上,便于查找最短路径
	'''
	if Point in Nodes:
		return Point
	else:
		x0 = Point[0]
		y0 = Point[1]
		for i in Edges:
			x1 = i[0][0]
			y1 = i[0][1]
			x2 = i[1][0]
			y2 = i[1][1]
			DeltaX = x1 - x2 
			DeltaY = y1 - y2 
			ConstA = x0*DeltaX + y0*DeltaY
			ConstB = x2*DeltaY - y2*DeltaX
			DeltaPattern = DeltaY**2 + DeltaX**2
			numrator = abs(DeltaY*x0 - DeltaX*y0 - ConstB)
			denominator = sqrt(DeltaPattern)
			if denominator==0:#除零错误排除
				return False
			distance = numrator/denominator
			if distance<=0.000000000000025:#函数准许一部分的误差
				return i[0]
		return False#没有匹配到





def findShortestPath(Point1,Point2,Graph):
	'''
	寻找最短路径,并记录最大速度限制和路径长度
	'''
	try:
		ShortestPath = nx.astar_path(Graph,Point1,Point2)
		ShortestPathLength = 0
		if len(ShortestPath)==1:
			return 0
		MaxSpeed = []
		for i in range(len(ShortestPath)-1):
			ShortestPathLength += calculateLength(ShortestPath[i],ShortestPath[i+1])
			#记录路段距离
			MaxSpeed.append(Graph.get_edge_data(ShortestPath[i],ShortestPath[i+1])['MAX_SPEED'])
			#记录最大速度限制
		#return ShortestPath,ShortestPathLength  条件使用
		return MaxSpeed,ShortestPathLength
	except Exception, e:#处理不可达情况
		pass
	return -1




def calculateScore(QueryTuple,CandidateTuple,ShortestPath):
	'''
	ST Algorithm 核心部分
	时空得分计算
	'''
	#空间得分计算
	TimeInc = abs(QueryTuple[0][2]-QueryTuple[1][2])#时间增量计算
	if TimeInc==0:
		return -1
	QueryLength = calculateLength(QueryTuple[0],QueryTuple[1])
	#采样点欧氏距离计算
	NormDistance = calculateLength(QueryTuple[1],CandidateTuple[1])
	#正态分布距离计算
	SpatialArgument = normalDistribution(NormDistance)*(QueryLength/ShortestPath[1])
	#ShortestPath[1]是路段距离记录
	#******************************************************************************
	#时间得分计算
	AverageSpeed = ShortestPath[1]/TimeInc
	#候选点平均速度计算
	SpeedProductSum = 0
	SpeedPowerSum = 0
	AverageSpeedSum = 0
	for i in ShortestPath[0]:#这里是最大速度的记录列表
		SpeedProductSum += i*AverageSpeed
		SpeedPowerSum += i**2
		AverageSpeedSum += AverageSpeed**2
	if (sqrt(SpeedPowerSum)*sqrt(AverageSpeedSum))==0:
		return -1
	TimeArgument = SpeedProductSum/(sqrt(SpeedPowerSum)*sqrt(AverageSpeedSum))
	return TimeArgument*SpatialArgument

def calculateZeroScore(QueryTuple,CandidateTuple):
	TimeInc = abs(QueryTuple[0][2]-QueryTuple[1][2])#时间增量计算
	if TimeInc==0:
		return -1
	QueryLength = calculateLength(QueryTuple[0],QueryTuple[1])
	#采样点欧氏距离计算
	NormDistance = calculateLength(QueryTuple[1],CandidateTuple[1])
	#正态分布距离计算
	CandidateLength = calculateLength(CandidateTuple[0],CandidateTuple[1])
	SpatialArgument = normalDistribution(NormDistance)*(QueryLength/CandidateLength)
	#******************************************************************************
	return SpatialArgument




























'''



class STAnalysis(object):
	def __init__(self,QueryPoint1,QueryPoint2,CandinaryPoint1,CandinaryPoint2,Graph):
		self.EuclidianDistance = calculateLength(QueryPoint1,QueryPoint2)
		self.NormDistance = calculateLength(QueryPoint2,CandinaryPoint2)
		self.Graph = Graph
		self.Q1 = QueryPoint1
		self.Q2 = QueryPoint2
		self.C1 = CandinaryPoint1
		self.C2 = CandinaryPoint2
	def judgePointNotExist(self):
		if self.C1 in self.Graph.nodes():
			if self.C2 in self.Graph:
				return (self.C1,self.C2)
'''
		#需要改
'''
		mindistance = calculateLength(self.C2,self.Graph.nodes()[])
		minpoint = self.Graph.nodes()[0]
		for i in self.Graph.nodes():
			if calculateLength(self.C2,i)<mindistance:
				minpoint = i
				mindistance = calculateLength(self.C2,i)
		C2 = minpoint
		mindistance = calculateLength(self.C1,self.Graph.nodes()[0])
		minpoint = self.Graph.nodes()[0]
		for i in self.Graph.nodes():
			if calculateLength(self.C1,i)<mindistance:
				minpoint = i
				mindistance = calculateLength(self.C1,i)
		C1 = minpoint 
		return (C1,C2)
	def STAnalysisFunc(self):
		CandinaryTuple = self.judgePointNotExist()
		shortestpath = nx.astar_path(self.Graph,CandinaryTuple[0],CandinaryTuple[1])
		shortestpathlength = 0
		for i in range(len(shortestpath)-1):
			shortestpathlength += calculateLength(shortestpath[i], shortestpath[i+1])
		if shortestpathlength==0:
			return self.NormDistance*self.EuclidianDistance
		spatialargument = self.NormDistance*(self.EuclidianDistance/shortestpathlength)
		return spatialargument
if __name__ == '__main__':
	datalist = reader.DataReader('8011.txt').dataProcess
	RoadList = reader.MapReader().roadList
	Candirary = []
	#print len(datalist[0])
	for i in datalist[0]:
		Temp = []
		for j in RoadList:
			temp = Mapping(i,j).mappingPoint
			if not temp:
				continue
			else:
				Temp.append(temp)
		Candirary.append(Temp)
	#print len(Candirary)
	for i in Candirary:
		print i
'''