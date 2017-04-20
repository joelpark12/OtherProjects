def pos(k, m):
    spot = k % m
    return spot

class Hashtable:
    def __init__(self, dict):
        self.keyed = []
        self.tuples = []
        self.dict = dict
        self.size = len(dict)
        if self.size == 0:
            self.table = [[]]
        else:
            self.table = [[] for i in range(self.size)]

        for i in self.dict:
            self.keyed.append(hash(i))
        for i in self.dict:
            self.tuples.append((hash(i), dict[i]))
        print self.tuples 
        
            
    def __getitem__(self, key):
        for i in self.tuples:
            if hash(key) in i:
                return i[1]
    
       
    def __setitem__(self, key, value):
        z = pos(hash(key), len(self.table))

        if self.__getitem__(key):
            for i in self.tuples:
                if hash(key) in i:
                    i = (hash(key), value)
        else: 
            self.table[z].append(value)
            self.tuples.append((hash(key), value))
            self.keyed.append(hash(key))

        

    def __delitem__(self, key):
        for i in self.tuples:
            if hash(key) in i:
                del i
        for i in self.keyed:
            if hash(key) in i:
                del i
        print "am i deleting anything?"
    
    def keys(self):
        return self.keyed

