import os, string, sys

import copy
import itertools
from collections import deque

# appends padding spaces if the number is smaller than the largest value
# e.g. if the largest val=1245, 1 will be represented as '1   '
def format_num(n, maxSpaces):
    strNum = str(n)
    return strNum + ' ' * (maxSpaces - len(strNum))

# Just a wrapper over python dict to preserve things
# like height, width; also a pretty printing function provided
class Grid:
    def __init__(self, w, h, d):
        self.width = w
        self.height = h
        self.d = d
    
    # pretty print the grid using the number formatter
    def pretty_print_grid(self):
        nSpaces = len(str(max(self.d.values()))) + 1
        strDelim = '|' + ('-' + (nSpaces * ' ')) * self.width + '|'
        print strDelim
        for y in range(self.height):
            print '|' + ' '.join([format_num(self.d[(x, y)], nSpaces) for x in range(self.width)]) + '|'
        print strDelim

# The grid is basically a dictionary. We can treat this as a graph where each node has 4 neighbors.
# Each neighbor contributes an in-edge as well as an out-edge.
# You might want to use this to construct you solution
class Graph:
    def __init__(self, grid):
        self.grid = grid
    
    def vertices(self):
        return self.grid.d.keys()
    
    def adj(self, (x, y)):
        return [u for u in [(x+1, y), (x-1, y), (x, y+1), (x, y-1)] if u in self.grid.d.keys()]
    
    # put the value val for vertex u
    def putVal(self, u, val):
        self.grid.d[u] = val
    
    def getVal(self, u):
        return self.grid.d[u]

# Takes the grid and the points as arguments and returns a list of paths
# The grid represents the entire chip
# Each path represents the wire used to connect components represented by points
# Each path connects a pair of points in the points array; avoiding obstacles and other paths
# while minimizing the total path length required to connect all points
# If the points cannot be connected the function returns None
def bfs(graph, points):
    parents = {}
    visited = set([points[0]])
    queue, path =  deque([points[0]]), [points[1]]
    while queue:
        vertex = queue.popleft()
        n = graph.adj((vertex[0],vertex[1]))
        for i in n:
            if i == points[1]:
                parents[i] = vertex
                while points[0] not in path:
                    path = [parents[path[0]]] + path
                return list(path)
            if graph.getVal(i) == 0: 
                if i not in visited:
                    visited.add(i)
                    queue.append(i)
                    parents[i] = vertex
    return None

def find_paths(grid, points):
    g = Graph(grid)
    allPoints = []
    perm = itertools.permutations(points)
    for x in perm:
        allPoints = []
        g2 = copy.deepcopy(g) 
        for i in x:
            
            temp = bfs(g2,i)
            if not temp:
                break
            for point in temp:
                g2.putVal(point, g2.getVal(temp[0]))

            blah = True
            #for point in temp:
             #   for path in allPoints:
              #      if point in path:
               #         blah = False

            if blah:
                allPoints.append(temp)
        if len(allPoints) == len(points):
            break
    return allPoints
# check that the paths do not cross each other, or the obstacles; returns False if any path does so
def check_correctness(paths, obstacles):
    s = set()
    for path in paths:
        for (x, y) in path:
            if (x, y) in s: return False
            for o in obstacles:
                if (o[0] <= x <= o[2]) and (o[1] <= y <= o[3]):
                    return False
            s.add((x, y))
    return True

def main():
    # read all the chip related info from the input file
    with open(sys.argv[1]) as f:
        # first two lines are grid height and width 
        h = int(f.readline())
        w = int(f.readline())
        
        # third line is the number of obstacles; following numObst lines are the obstacle co-ordinates
        numObst = int(f.readline())
        obstacles = []
        for n in range(numObst):
            line = f.readline()
            obstacles.append([int(x) for x in line.split()])
        
        # read the number of points and their co-ordinates
        numPoints = int(f.readline())
        points = []
        for n in range(numPoints):
            line = f.readline()
            pts = [int(x) for x in line.split()]
            points.append(((pts[0], pts[1]), (pts[2], pts[3])))
    grid = dict(((x, y), 0) for x in range(w) for y in range(h))
    # lay out the obstacles
    for o in obstacles:
        for x in range(o[0], o[2] + 1):
            for y in range(o[1], o[3] + 1):
                grid[(x, y)] = -1
    
    cnt = 1 # route count
    for (s, d) in points:
        grid[s] = cnt
        grid[d] = cnt
        cnt += 1
    
    numPaths = cnt - 1
    g = Grid(w, h, grid)
        
    g.pretty_print_grid()

    paths = find_paths(g, points)
    if paths is None:
        print "Cannot connect all the points!"
    else:
        # check the correctness
        if not check_correctness(paths, obstacles):
            raise ("Incorrect solution, some path cross each other or the obstacles!")
        print "Paths:"
        totLength = 0
        for p in paths:
            print p
            totLength += len(p)
        print "Total Length: " + str(totLength)
    
if __name__ == "__main__":
    main()
