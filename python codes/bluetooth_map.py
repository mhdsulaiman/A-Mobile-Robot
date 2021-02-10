# -*- coding: utf-8 -*-
"""
Created on Fri Dec  1 12:36:21 2017

@author: Nazeeh Saifi 
"""


import numpy as np
import serial
from time import sleep


map_1=np.array([(0,0,0,0,0),
				 (0,0,1,0,0),
				 (0,0,0,0,0),
                (0,0,1,1,1),
                (0,0,0,0,0)])

ser=serial.Serial('COM6',38400,timeout=2)

def send_to_arduino(path1):
    sleep(1)
    ser.write(path1.encode('utf-8'))
    ser.close()


    
def recive_from_arduino():
    # ser=serial.Serial('COM4',38400,timeout=2)
    ser.open()
    while True:
       p1=ser.readline().decode('utf-8')
       if(p1==''):{}#donothing
       elif(p1!="END"):
          print("there is a problem in :",p1)
          return p1
          break
       else:
          print("there is no object detected")
          break
    ser.close()
   
           
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
        
        
class Node(object):
    def __init__(self, name):
        """Assumes name is a string"""
        self.name = name
#        num=''
#        for i in self.name:
#            if i not in string.punctuation:
#                num+=i
#        self.num=num
        
    def getName(self):
        return self.name
#    def getnum_str(self):
#        return self.num
#                
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
                result = result + src.getName() + '->'\
                         + dest.getName() + '\n'
        return result[:-1] #omit final newline

#class Graph(Digraph):
#    def addEdge(self, edge):
#        Digraph.addEdge(self, edge)
#        rev = Edge(edge.getDestination(), edge.getSource())
#        Digraph.addEdge(self, rev)
    
def buildMapGraph(graphType):
    g = graphType()
    (i,j)=map_1.shape
    for x in range(0,i):
        for y in range(0,j):
            if map_1[x][y]==0:
                g.addNode(Node("("+str(x)+","+str(y)+")"))
    			
    return g
	
def linknodes(g):
    (i,j)=map_1.shape
    for x in range(0,i):
        for y in range(0,j):
            if map_1[x][y]==0:
                
                if g.Node_is_there("("+str(x)+","+str(y+1)+")")==True:
                    g.addEdge(Edge(g.getNode("("+str(x)+","+str(y)+")"), g.getNode("("+str(x)+","+str(y+1)+")")))
                
                
                if g.Node_is_there ("("+str(x+1)+","+str(y)+")")==True:#(1,0)
                    g.addEdge(Edge(g.getNode("("+str(x)+","+str(y)+")"), g.getNode("("+str(x+1)+","+str(y)+")")))
				    
                
                
                if g.Node_is_there("("+str(x-1)+","+str(y)+")")==True:
                    g.addEdge(Edge(g.getNode("("+str(x)+","+str(y)+")"), g.getNode("("+str(x-1)+","+str(y)+")")))
                    
                
					
                if g.Node_is_there("("+str(x)+","+str(y-1)+")")==True:
                    g.addEdge(Edge(g.getNode("("+str(x)+","+str(y)+")"), g.getNode("("+str(x)+","+str(y-1)+")")))
	
    """
	g.addEdge(Edge(g.getNode('(0,0)'), g.getNode('(0,1)')))
    g.addEdge(Edge(g.getNode('(0,1)'), g.getNode('(1,1)')))
    g.addEdge(Edge(g.getNode('(1,1)'), g.getNode('(2,1)')))
    g.addEdge(Edge(g.getNode('(2,1)'), g.getNode('(3,1)')))
    g.addEdge(Edge(g.getNode('(2,1)'), g.getNode('(3,2)')))

    
   
    
    
    g.addEdge(Edge(g.getNode('(0,1)'), g.getNode('(0,2)')))
    g.addEdge(Edge(g.getNode('(0,2)'), g.getNode('(0,3)')))
    g.addEdge(Edge(g.getNode('(0,3)'), g.getNode('(1,3)')))
    g.addEdge(Edge(g.getNode('(1,3)'), g.getNode('(2,3)')))
    g.addEdge(Edge(g.getNode('(2,3)'), g.getNode('(3,3)')))
    g.addEdge(Edge(g.getNode('(3,3)'), g.getNode('(3,2)')))
	"""

    



def printPath(path):
    """Assumes path is a list of nodes"""
    result = ''
    for i in range(len(path)):
        result = result + str(path[i])
        if i != len(path) - 1:
            result = result + '->'
    return result 




"""please choose one of the following algorithms by un commenting it"""



def DFS(graph, start, end, path, shortest, toPrint = False):
    """Assumes graph is a Digraph; start and end are nodes;
          path and shortest are lists of nodes
       Returns a shortest path from start to end in graph"""
    path = path + [start]
    
    if toPrint:
        print('Current DFS path:', printPath(path))
    if start == end:
        return path
    else:
        for node in graph.childrenOf(start):
            if node not in path: #avoid cycles
                if shortest == None or len(path) < len(shortest):
                    newPath = DFS(graph, node, end, path, shortest,
                                  toPrint)
                    if newPath != None:
                        shortest = newPath
            elif toPrint:
                print('Already visited', node)
        return shortest
  
    


def shortestPath(graph, start, end, toPrint = False):
    """Assumes graph is a Digraph; start and end are nodes
       Returns a shortest path from start to end in graph"""
    return DFS(graph, start, end, [], None, toPrint)






#printQueue = True 
#def BFS(graph, start, end, toPrint = False):
#    """Assumes graph is a Digraph; start and end are nodes
#       Returns a shortest path from start to end in graph"""
#    initPath = [start]
#    pathQueue = [initPath]
#    while len(pathQueue) != 0:
#        #Get and remove oldest element in pathQueue
#        if printQueue:
#            print('Queue:', len(pathQueue))
#            for p in pathQueue:
#                print(printPath(p))
#        tmpPath = pathQueue.pop(0)
#        if toPrint:
#            print('Current BFS path:', printPath(tmpPath))
#            print()
#        lastNode = tmpPath[-1]
#        if lastNode == end:
#            return tmpPath
#			#who ever reach this return first end the loop and return his tmpath
#        for nextNode in graph.childrenOf(lastNode):
#            if nextNode not in tmpPath:
#                newPath = tmpPath + [nextNode]
#                pathQueue.append(newPath)
#    return None 
	#we don't reach this point unless we didn't find a path and we pop out every pathQueue 
	#between dest and src and in this case the none is dealt with
	#in the testsp fucntion 
	

#def shortestPath(graph, start, end, toPrint = False):
#    """Assumes graph is a Digraph; start and end are nodes
#       Returns a shortest path from start to end in graph"""
#    return BFS(graph, start, end, toPrint)
#
    
def testSP(source, destination,p):
    g = buildMapGraph(Digraph)
    linknodes(g)
    sp = shortestPath(g, g.getNode(source), g.getNode(destination), toPrint = True)
#when i changed toPrint==False the program stops printing every step of path
    if sp != None:
#        send path to bluetooth
#        making a list of num_str ['00','01']
        path_str=''
        for node in sp:
            for char in node.getName():
                if char not in "(),":
                    path_str+=char
        print('Shortest path from', source, 'to',
              destination, 'is (path_str) is:',path_str)
        if(p!=1):
           check=input('do you want to send this path to arduino (y/n):')
        elif(p==1):check='y'
        
        if check=='y':
            p=1#no need to repeat the Question 
            global path_lon
            send_to_arduino(path_str)
            path_lon=sp
            global k
            k=recive_from_arduino()  
        else:
            pass
            ser.close()
        
    else:
#send to ardduino using bluetooth that there is no path
        print('There is no path from', source, 'to', destination)
        ser.close()

if __name__=='__main__':
    source=input("please input the source coordinates like '(X,Y)':")
    destination=input("please input the destination coordinates like '(X,Y)':")
    testSP(source, destination,0)
    
    while(k!=None):
      
      (m,n)=edit_matrix(k)
      map_1[m][n]=1
      print("(",m,",",n,")")
      
      index_Nsource=get_new_source_index(path_lon,"("+str(m)+","+str(n)+")")
      index_Des1=index_Nsource+1
      
      new_source=path_lon[index_Nsource].getName()
      Des1=path_lon[index_Des1].getName()
      
     
      
      if(Des1==destination):#if there is an object in destination
          print("There is an object in your Destination -_- \nI will stop here ^_^")
          ser.close()
          break
      else:
          print("the new path from",new_source,"to", destination)
          testSP(new_source,destination,1)