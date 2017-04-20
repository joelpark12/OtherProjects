# AVL Trees, by Elizabeth Feicke

class AVLNode:
    def __init__(self, key, left=None, right=None, parent=None):
        self.key = key
        self.left = left
        self.right = right
        self.parent = parent
        def predecessor(self, n):
            if n.left == None:
                return leastanc(n)
            else:
                return (maxx(n.left))
                
        def successor(self, n):
            if n.right == None:
                return greatanc(n)
            else:
                return (minn(n.right))
        def search(self, k, less):
            if less(k, self.key):
                if self.left != None:
                    return (self.left.search(k, less))
                else:
                    return None
            elif less(self.key, k):
                if self.right != None:
                    return (self.right.search(k, less))
                else:
                     return None
            else:
                return self
        def delete(self, n):
            if n:
                x = countkids(n)
                if x == 0:
                    if n.parent.left == n:
                        n.parent.left = None
                        return n
                    else:
                        n.parent.right = None
                        return n
                elif x==1:
                    if n.left:
                        child = n.left
                    else:
                        child = n.right
                    if n.parent:
                        if n.parent.left == n:
                            n.parent.left = child
                            return n
                        else:
                            n.parent.right = child
                            return n
                else:
                    n.parent = n
                    nex = n.right
                    while nex.left:
                        n.parent = nex
                        nex = nex.left
                    n.key = nex.key
                    if n.parent.left == nex:
                        n.parent.left = nex.right
                    else:
                        n.parent.right = nex.right
        def insert(self, k, less):
            if less(k, self.key):
                if self.left == None:
                    self.left=BSTNode(k, None, None, self)
                    return self.left
                else:
                    return self.left.insert(k, less)
            elif less(self.key, k):
                if self.right == None:
                    self.right=BSTNode(k, None, None, self)
                    return self.right
                else:
                    return self.right.insert(k, less)
        
def less_than(x,y):
    return x < y
def inorder(n):
    ret = []
    if n.left:
        ret += inorder(n.left)
    ret.append(n.key)
    if n.right:
        ret += inorder(n.right)
    return ret
def minn(node):
    if node.left != None:
        return minn(node.left)
    else:
        return node
def maxx(node):
    if node.right != None:
        return maxx(node.right)
    else:
        return node
def greatanc(n):
    p= n.parent
    if p != None and n == p.right:
        return greatanc(p)
    else:
        return p
def leastanc(n):
    p= n.parent
    if p != None and n == p.right:
        return leastanc(p)
    else:
        return p
def inordertree(t):
    if t.root:
        inorder(t.root)
def countkids(n):
    x = 0
    if n.right != None:
        x += 1
    elif n.left != None:
        x += 1
    else:
        x += 0
    return x
def height(n):
    if n.left and n.right:
        return 1 + max(height(n.left), height(n.right))
    elif n.left:
        return 1 + height(n.left)
    elif n.right:
        return 1 + height(n.left)
    else:
        return 0
def isAVL(n):
    if height(n.left) == height(n.right):
        return True
    elif height(n.left) == height(n.right) + 1:
        return True
    elif height(n.left) == height(n/right) - 1:
        return True
    else:
        return False

class AVLTree:
    def __init__(self, root = None, less=less_than):
        self.root = root
        self.less = less

    # takes value, returns node with key value
    def insert(self, k):
        if self.root == None:
            return BSTNode(k)
        else:
            return self.root.insert(k, self.less)

    # takes node, returns node
    # return the node with the smallest key greater than n.key
    def successor(self, n):
        if self.root == None:
            return None
        else:
            self.root.successor(n)

    # return the node with the largest key smaller than n.key
    def predecessor(self, n):
        if self.root== None:
            return None
        else:
            return self.root.predecessor(n)

    # takes key returns node
    # can return None
    def search(self, k):
        if self.root == None:
            return None
        else:
            return self.root.search(k, self.less)
            
    # takes node, returns node
    def delete_node(self, n):
        if self.root == None:
            return None
        else:
            return self.root.delete(n)

