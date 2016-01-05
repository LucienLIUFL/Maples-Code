#!/usr/bin/env python
#-*- coding:utf-8 -*-
from reader import DataReader 
from reader import MapReader 
from tool import * 
from match import Mapping 
from stAnalysis import * 
import networkx as nx
def readTaxiData(filename):
	TaxiDataList = DataReader(filename).dataProcess
	return TaxiDataList
def matchCandidateNodes(TaxiData, Graph):
	CandidateNodesList = []
	for i in TaxiData:
		templist = []
		for j in Graph.edges():
			temp = Mapping(i,j).mappingPoint
			if not temp:
				continue
			else:
				templist.append(temp)
		CandidateNodesList.append(templist)
	return removeRedundancy(TaxiData, CandidateNodesList)

def matchMapNodes(CandidateNodesList, Graph):
	MatchedNodesList = []
	for i in CandidateNodesList:
		temp = []
		for j in i:
			Possibility = matchMapPoint(j, Graph.nodes(), Graph.edges())
			if Possibility:
				temp.append(Possibility)
			else:
				temp.append('None')
		MatchedNodesList.append(temp)
	return MatchedNodesList

def calculateSTScoreMatrix(TaxiData,CandidateNodesList, MatchedNodesList, Graph):
	ScoreMatrix = []
	for i in range(len(MatchedNodesList)-1):
		matrix = []
		countj = 0
		for j in MatchedNodesList[i]:
			row = []
			countk = 0
			for k in MatchedNodesList[i+1]:
				ShortestPath = findShortestPath(j, k, Graph)
				if ShortestPath==0:
					QueryTuple = (TaxiData[i],TaxiData[i+1])
					CandidateTuple = (CandidateNodesList[i][countj],CandidateNodesList[i+1][countk])
					result = calculateZeroScore(QueryTuple, CandidateTuple)
					row.append(result)
				elif ShortestPath==-1:
					row.append(ShortestPath)
				else:
					QueryTuple = (TaxiData[i],TaxiData[i+1])
					CandidateTuple = (CandidateNodesList[i][countj],CandidateNodesList[i+1][countk])
					result = calculateScore(QueryTuple, CandidateTuple, ShortestPath)
					row.append(result)
				countk += 1
			countj += 1
			matrix.append(row)
		ScoreMatrix.append(matrix)
	return ScoreMatrix

def findEffectivePathIndex(ScoreMatrix):
	EffectiveGroup = []
	for i in range(len(ScoreMatrix)):
		MaxElement = findMaxElement(ScoreMatrix[i])
		if MaxElement==-1:
			continue
		else:
			EffectiveGroup.append(i)
			
	EffectivePathIndex =[]
	Path = []
	for i in EffectiveGroup:
		if (i+1) in EffectiveGroup:
			Path.append(i)
		else:
			Path.append(i)
			EffectivePathIndex.append(Path)
			Path = []
	return EffectivePathIndex


def createSelectNodesGraph(CandidateNodesList, EffectivePathIndexElement, ScoreMatrix):
	SelectNodesGraph = nx.Graph()
	for Index in EffectivePathIndexElement:
		for j in range(len(CandidateNodesList[Index])):
			for k in range(len(CandidateNodesList[Index+1])):
				Point1 = CandidateNodesList[Index][j]
				Point2 = CandidateNodesList[Index+1][k]
				Weighted = 1.0 - (ScoreMatrix[Index][j][k])
				SelectNodesGraph.add_weighted_edges_from([(Point1,Point2,Weighted)])
	return SelectNodesGraph

def findMaxScorePath(CandidateNodesList,SelectNodesGraph, i):
	CanPath = []
	for j in CandidateNodesList[i[0]]:
		for k in CandidateNodesList[i[-1]]:
			CanPath.append((nx.astar_path(SelectNodesGraph,j,k),nx.astar_path_length(SelectNodesGraph,j,k)))
	MaxScore = min([j[1] for j in CanPath])
	for j in CanPath:
		if MaxScore==j[1]:
			MaxScorePath = j[0]
	return MaxScorePath

def findEffectivePath(MaxScorePath, CandidateNodesList, MatchedNodesList, Graph, i):
	EffectivePath = []
	for j in range(len(MaxScorePath)-1):
		matchedindex1 = CandidateNodesList[i[j]].index(MaxScorePath[j])
		matchedindex2 = CandidateNodesList[i[j+1]].index(MaxScorePath[j+1])
		PointBegin = MatchedNodesList[i[j]][matchedindex1]
		PointEnd = MatchedNodesList[i[j+1]][matchedindex2]
		Ju = nx.astar_path(Graph,PointBegin,PointEnd)
		if len(Ju)==1:
			EffectivePath.append([])
		else:
			EffectivePath.append(Ju)
	return EffectivePath
def findTheLastPath(MaxScorePath, EffectivePath):
	TheLastPath = []
	for i in range(len(MaxScorePath)):
		TheLastPath.append(MaxScorePath[i])
		if i==(len(MaxScorePath)-1):
			break
		TheLastPath.extend(EffectivePath[i])
	return TheLastPath










def mappingOnePath(TaxiData, Graph):
	CandidateNodesList = []
	TaxiData,CandidateNodesList = matchCandidateNodes(TaxiData, Graph)
	for i in CandidateNodesList:
		open("Cand.txt","a").write(str(len(i))+",")
#	MatchedNodesList = matchMapNodes(CandidateNodesList, Graph)
#	ScoreMatrix = calculateSTScoreMatrix(TaxiData, CandidateNodesList, MatchedNodesList, Graph)
#	EffectivePathIndex = findEffectivePathIndex(ScoreMatrix)
#	Road = []
#	for i in EffectivePathIndex:
#		SelectNodesGraph = createSelectNodesGraph(CandidateNodesList, i, ScoreMatrix)
#		MaxScorePath = findMaxScorePath(CandidateNodesList, SelectNodesGraph, i)
#		EffectivePath = findEffectivePath(MaxScorePath, CandidateNodesList, MatchedNodesList, Graph, i)
#		TheLastPath = findTheLastPath(MaxScorePath, EffectivePath)
#		for j in range(len(TheLastPath)-1):
#			Road.append((TheLastPath[j],TheLastPath[j+1]))
#		del SelectNodesGraph
#	return Road

def mappingOneTaxi(filename, Graph, G):
	TaxiDataList = readTaxiData(filename)
	for i in TaxiDataList:
		try:
			mappingOnePath(i, Graph)
#			Road = mappingOnePath(i, Graph)
#			G.add_edges_from(Road)
#			del Road
		except Exception,e:
			fp = open('log.txt','a')
			fp.write(str(e)+'\t'+str(i)+'\n\n')
			fp.close()
	nx.write_shp(G, './Graph')
	return






