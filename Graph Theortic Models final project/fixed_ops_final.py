# -*- coding: utf-8 -*-
"""
Damascus University 
Department Of Computer & Automation Engineering
authors: Nazeeh Saifi & M Suliman Tanbari
"""


import numpy as np
import serial
import string
from time import sleep
from skimage import io
from skimage import color

"""======= initilizing the serial port  =========="""
ser=serial.Serial()
ser.port='COM6'
ser.baudrate=38400
ser.timeout=2
"""================================================"""
					
# """======= using scikit image to get the graph =========="""
# image=io.imread(r'E:\Computer & Automation Eng\Books\projects\FINAL YEAR PROJECT\python&arduino\codes\bluetooth\fixed_ops_final\cython\100.png')
# graph_map=color.rgb2grey(image).astype(int)
# """========================================"""
graph_map=np.array([(1,1,1,0),
				     (1,0,1,1),
				     (1,1,1,0),
                     (0,0,1,1)])
"""======= using ser obj to send and recieve from arduino =========="""	
def send_to_arduino(path1):
    ser.open()
    sleep(1)
    ser.write(path1.encode('utf-8'))
    sleep(1)
    ser.flushInput()
    ser.close()

def recieve_from_arduino():
	ser.open()
	while (ser.isOpen()):
		if (ser.inWaiting()>0):
			p1=ser.readline().decode('utf-8')
			sleep(1)
			if(p1=='end\r\n'):
				ser.flushOutput()
				ser.close()
				return "end"
				  
			else:
				ser.flushOutput()
				ser.close()
				return p1
"""========================================================="""
	
	
        
def edit_matrix(num):
        num1=int(num)
        if (num1==0):
            x=0
            y=0
        elif (num1==1):
            y=1
            x=0
        else:
            y=num1%10
            x=num1//10
        return (x,y)
		
def get_new_source_index(list_path,problem_node_str):
    for i in range (0,len(list_path)):
        if list_path[i].getName()==problem_node_str:
            return i-1		
    
	
"""===== Graph-Theroitic Model======"""
class Node(object):
    def __init__(self, name):
        """Assumes name is a string"""
        self.name = name

        
    def getName(self):
        return self.name

    def __str__(self):
        return self.name

class Edge(object):
    def __init__(self, src, dest):
        """Assumes src and dest are nodes"""
        self.src = src
        self.dest = dest
    def getSource(self):
        return self.src
    def getDestination(self):
        return self.dest
    def __str__(self):
        return self.src.getName() + '->' + self.dest.getName()
               
class Digraph(object):
    """edges is a dict mapping each node to a list of
    its children"""
    def __init__(self):
        self.edges = {}
    def addNode(self, node):
        if node in self.edges:
            raise ValueError('Duplicate node')
        else:
            self.edges[node] = []
    def addEdge(self, edge):
        src = edge.getSource()
        dest = edge.getDestination()
        if not (src in self.edges and dest in self.edges):
            raise ValueError('Node not in graph')
        self.edges[src].append(dest)
    def childrenOf(self, node):
        return self.edges[node]
    def hasNode(self, node):
        return node in self.edges
    def getNode(self, name):
        for n in self.edges:
            if n.getName() == name:
                return n
        raise NameError(name)
	
    def Node_is_there(self,name):
        for n in self.edges:
            if n.getName() == name:
                return True
        
		
    def __str__(self):
        result = ''
        for src in self.edges:
            for dest in self.edges[src]:
                result = result + src.getName() + '->'+ dest.getName() + '\n'
        return result[:-1] #omit final newline

class undiGraph(Digraph):
   def addEdge(self, edge):
       Digraph.addEdge(self, edge)
       rev = Edge(edge.getDestination(), edge.getSource())
       Digraph.addEdge(self, rev)
    
def buildMapGraph(graphType):
    g = graphType()
    (i,j)=graph_map.shape
    for x in range(0,i):
        for y in range(0,j):
            if graph_map[x][y]==1:
                g.addNode(Node("("+str(x)+","+str(y)+")"))			
    return g
	
def linknodes(g):
    (i,j)=graph_map.shape
    for x in range(0,i):
        for y in range(0,j):
            if graph_map[x][y]==1:
                
                if g.Node_is_there("("+str(x)+","+str(y+1)+")")==True:
                    g.addEdge(Edge(g.getNode("("+str(x)+","+str(y)+")"), g.getNode("("+str(x)+","+str(y+1)+")")))
                
                
                if g.Node_is_there ("("+str(x+1)+","+str(y)+")")==True:#(1,0)
                    g.addEdge(Edge(g.getNode("("+str(x)+","+str(y)+")"), g.getNode("("+str(x+1)+","+str(y)+")")))

def printPath(path):
    """Assumes path is a list of nodes"""
    result = ''
    for i in range(len(path)):
        result = result + str(path[i])
        if i != len(path) - 1:
            result = result + '->'
    return result 



"""
======================= IMPORTANT NOTES ========================================
1-please choose one of the following algorithms by uncommenting it
2-make sure to uncomment the algorithm with the shortest path function below it
================================================================================
"""


"""===== Algorithm number (1) DFS='Depth First Search'===== ======"""

# def DFS(graph, start, end, path, shortest, toPrint = False):
   # """Assumes graph is a Digraph; start and end are nodes;
         # path and shortest are lists of nodes
      # Returns a shortest path from start to end in graph"""
   # path = path + [start]
   
   # if toPrint:
       # print('Current DFS path:', printPath(path))
   # if start == end:
       # return path
   # else:
       # for node in graph.childrenOf(start):
           # if node not in path: #avoid cycles
               # if shortest == None or len(path) < len(shortest):
                   # newPath = DFS(graph, node, end, path, shortest,
                                 # toPrint)
                   # if newPath != None:
                       # shortest = newPath
           # elif toPrint:
               # print('Already visited', node)
       # return shortest
 
   
# def shortestPath(graph, start, end, toPrint = False):
   # """Assumes graph is a Digraph; start and end are nodes
      # Returns a shortest path from start to end in graph"""
   # return DFS(graph, start, end, [], None, toPrint)
   
"""==================== The end of algorithm (1) ================"""


"""===== Algorithm number (2) DFS='Breadth First Search'===== """

printQueue = False 
def BFS(graph, start, end, toPrint = False):
    """Assumes graph is a Digraph; start and end are nodes
       Returns a shortest path from start to end in graph"""
    initPath = [start]
    pathQueue = [initPath]
    while len(pathQueue) != 0:
        #Get and remove oldest element in pathQueue
        if printQueue:
            print('Queue:', len(pathQueue))
            for p in pathQueue:
                print(printPath(p))
        tmpPath = pathQueue.pop(0)
        if toPrint:
            print('Current BFS path:', printPath(tmpPath))
            print()
        lastNode = tmpPath[-1]
        if lastNode == end:
            return tmpPath
			#who ever reach this return first end the loop and return his tmpath
        for nextNode in graph.childrenOf(lastNode):
            if nextNode not in tmpPath:
                newPath = tmpPath + [nextNode]
                pathQueue.append(newPath)
    return None 
	#we don't reach this point unless we didn't find a path and we pop out every pathQueue 
	#between dest and src and in this case the none is dealt with
	#in the testsp fucntion 

def shortestPath(graph, start, end, toPrint = False):
    """Assumes graph is a Digraph; start and end are nodes
       Returns a shortest path from start to end in graph"""
    return BFS(graph, start, end, toPrint)

"""==================== The end of algorithm (2) ================"""



def testSP(source, destination):
	g = buildMapGraph(undiGraph)
	linknodes(g)
	print(source,destination)
	return shortestPath(g, g.getNode(source), g.getNode(destination), toPrint = False)
    

if __name__=='__main__':
	source=input("please input the source coordinates like '(X,Y)':")
	destination=input("please input the destination coordinates like '(X,Y)':")
	sp= testSP(source, destination)
	key=0
	while True:
		if sp != None:
			path_str=''
			for node in sp:
				for char in node.getName():
					if char not in "(,)":
						path_str+=char
			print('Shortest path from', source, 'to',destination, 'is', printPath(sp),'and path_str is:',path_str)
			if key==1:
				check='y'
			else:
				check=input('do you want to send this path to arduino (y/n):')
			if check=='y':
				send_to_arduino(path_str)
			else:
				pass
		else:
			print('There is no path from', source, 'to', destination)
			break
		if check=='y':
			prob_or_end=recieve_from_arduino()
			print("prob_or_end:",prob_or_end)
		else: pass
		try:
			if (prob_or_end =="end"):
				print("the agent reachend the destination")
				break
			else :
				(m,n)=edit_matrix(prob_or_end)
				print((m,n))
				graph_map[m][n]=0
				index_Nsource=get_new_source_index(sp,"("+str(m)+","+str(n)+")")
				new_source=sp[index_Nsource].getName()
				if (("("+str(m)+","+str(n)+")")==destination):
					print("i am at the closest point to destination and there is an obstacle in it>>>>")
					break
				sp=testSP(new_source,destination)
			key=1	
		except IndexError:
			print("the agent reachend the destination")
			break		
		except NameError:
			print("Error")
			break
		
		
