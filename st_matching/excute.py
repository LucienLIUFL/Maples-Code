import networkx as nx
from algorithm.core import mappingOneTaxi
from algorithm.reader import MapReader
def mappingOneDay():
	for i in range(13340):
		try:
			g = nx.read_shp('./Graph/edges.shp')
			G = nx.Graph()
			G.add_edges_from(g.edges())
			filename = './data/' + str(i) + '.txt'
			Graph = MapReader().mapGraph
			mappingOneTaxi(filename, Graph, G)
			del g
			del G
		except Exception,e:
			fp = open('log_taxi.txt','a')
			fp.write(str(e)+'\n'+str(i)+'.txt'+'\n')
			fp.close()

mappingOneDay()
