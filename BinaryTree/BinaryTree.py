
class TreeNode():
    def __init__(self, x):
        self.val = x
        self.par = None
        self.left = None
        self.right = None
       
class BinaryTree():
    def __init__(self):
        self.root = None
        
    def get_root(self):
        return self.root
        
    def search(self,k):
        if self.root == None:
            return None
        else:
            current_root = self.root
            while current_root != None:
                if current_root.val == k:
                    return current_root
                else:
                    if k < current_root.val:
                        current_root = current_root.left
                    elif k > current_root.val:
                        current_root = current_root.right
            return None            
        
    def predecessor(self, node):
        if node.left != None:
            return self.maximum(node.left)
        else:
            pre = node.par
            while pre != None and pre.left == node:
                node = pre
                pre = pre.par
            return pre
            
    def successor(self, node):
        if node.right != None:  # case1 : node has  right child, return the min of right subtree
            return self.minimum(node.right)
        else:                   # case2 : node has no right child
            suc = node.par
            while suc != None and suc.right == node:
                node = suc
                suc = suc.par
            return suc
                          
    def minimum(self,node):
        min_node = node
        current_root = node
        while current_root.left != None:
            min_node = current_root.left.val
            current_root = current_root.left
        return min_node    
            
    def maximum(self,node):
        max_node = node
        current_root = node
        while current_root.right != None:
            max_node = current_root.right.val
            current_root = current_root.right
        return max_node
    
    def delete(self, node):
        if node.left == None or node.right == None:
            parent = node.par
            if node.right != None:
                node.right.par = parent
                if parent.right == node:
                    parent.right = node.right
                else:
                    parent.left = node.right
            else:
                if parent.right == node:
                    parent.right = node.left
                else:
                    parent.left = node.left
                if node.left != None:
                    node.left.par = parent                           
        else:  #case 3  have two children
            suc = self.successor(node)
            # the suc of this node won't have left child
            # delete the suc
            sucpar = suc.par
            if sucpar.right == suc:
                sucpar.right = suc.right
            else:
                sucpar.left = suc.right
            if suc.right != None:
                suc.right.par = suc.par
            
  
    
    def insert(self, node):
        if self.root == None:
            self.root = node
        else:
            current_root = self.root 
            while current_root != None:
                if node.val < current_root.val:
                    current_par = current_root
                    current_root = current_root.left
                    mark = 'left'
                elif node.val > current_root.val:
                    current_par = current_root
                    current_root = current_root.right
                    mark = 'right'
        
            if mark == 'left':
                current_par.left = node
                node.par = current_par
            elif mark == 'right':
                current_par.right = node
                node.par = current_par
                
    def inorder_traversal(self,node):
        if node == None:
            return []
        else:
            traversal = []
            traversal.extend(self.inorder_traversal(node.left))
            traversal.append(node.val)
            traversal.extend(self.inorder_traversal(node.right))          
            return traversal
        
               
binary_tree = BinaryTree()
node5 = TreeNode(5)
binary_tree.insert(node5)
node2 = TreeNode(2)
binary_tree.insert(node2)

node3 = TreeNode(1)
binary_tree.insert(node3)
node4 = TreeNode(8)
binary_tree.insert(node4)
root_node = binary_tree.get_root()

print binary_tree.inorder_traversal(root_node)

node = binary_tree.search(5)
print binary_tree.predecessor(node).val
print binary_tree.successor(node).val

