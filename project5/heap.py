from swap import swap

def less(x, y):
    return x < y

def less_key(x, y):
    return x.key < y.key

def left(i):
    return 2 * i + 1

def right(i):
    return 2 * (i + 1)

def parent(i):
    return (i-1) / 2

# Student code -- fill in all the methods that have pass as the only statement
class Heap:
    def __init__(self, data, 
                 less = less):
        self.data = data
        self.less = less
        self.build_min_heap()
        
    def __repr__(self):
        return repr(self.data)
    
    def minimum(self):
        if self.data:
            return self.data[0]
        else:
            return None

    def insert(self, obj):
        self.data.append(obj)
        self.build_min_heap()

    def extract_min(self):
        answ = self.data[0]
        del(self.data[0])
        return answ
        
    def min_heapify(self, i):
        n = len(self.data)
        l = left(i)
        r = right(i)
        if l<n and self.data[i] > self.data[l]:
            largest = l
        else:
            largest = i
        if r <n and self.data[largest] > self.data[r]:
            largest = r
        if largest != i:
            swap(self.data, i, largest)
            self.min_heapify(largest)
        
    
    def build_min_heap(self):
        n = len(self.data)
        last_parent = n / 2 - 1
        if self.data:
            for i in range(last_parent, -1, -1):
                self.min_heapify(i)
    
class PriorityQueue:
    def __init__(self, less=less_key):
        self.heap = Heap([], less)

    def __repr__(self):
        return repr(self.heap)

    def push(self, obj):
        self.heap.insert(obj)

    def pop(self):
        return self.heap.extract_min()

if __name__ == "__main__":
    # unit tests here
    pass
