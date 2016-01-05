#!/usr/bin/env python
#-*- coding:utf-8 -*-
#**********************************************************************************************
#filename:data.py
#用于对出租车数据进行处理,读取有效信息
#更新日期:201505024
#**********************************************************************************************
import networkx as nx
class DataReader(object):
	'''
	出租车数据读取
	返回路径列表[(经度,纬度,时间点),...]
	'''
	def __init__(self,filename):
		self.OpenDataFile = open(filename)
	@property
	def dataProcess(self):
		#数据处理方法返回列表
		DataProcessList = []
		for i in self.OpenDataFile:
			if i.strip() == '':
				try:
					DataProcessList.append(path)
				except:
					pass
				path = []
				continue
			temp = i.strip().split(',')
			x = temp[0].find(' ')
			time = int(temp[0][x+1:x+3])*3600 + int(temp[0][x+4:x+6])*60 + int(temp[0][x+7:x+9])
			path.append((float(temp[1]),float(temp[2]),time))
		return DataProcessList

class MapReader(object):
	'''
	地图数据读取
	返回连续的点集为路径
	MapInfoData=[路0,路1,...]
	路=[点0,点1,...点n]
	'''
	def __init__(self):
		self.MapData = nx.read_shp('./map/111.shp')
	@property
	def roadList(self):
		'''
		路段信息,为包含头尾点的列表
		[[Point, Point],[Point, Point],...,]
		'''
		RoadList = self.MapData.edges()
		return RoadList
	@property
	def nodeList(self):
		'''
		路点集合
		'''
		nodeList = self.MapData.nodes()
	@property
	def mapGraph(self):
		'''
		返回原图
		'''
		return self.MapData







