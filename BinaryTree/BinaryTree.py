
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
        
    def search(self,root,k):
        if root == None or root.val == k:
            return root
        else:
            if k < root.val:
                return search(root.left,k)
            else:
                return search(root.right,k)
                
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
                          
    def minimum(self,root):
        while root.left != None:
            root = root.left
        return root    
            
    def maximum(self,node):
        while root.right != None:
            root= root.right
        return root

    
    def delete(self,node):
        if node.left == None or node.right == None:
            delnode = node
        else:
            delnode = self.successor(node)
        childnode = None
        delnodepar = delnode.par
        if delnode.left != None:
            childnode = delnode.left
        else:
            childnode = delnode.right
        if childnode != None:    # in case of delnode have no child
            childnode.par = delnode
        if delnodepar != None:     # in case of delnode is the root
            if delnode == delnodepar.left:
                delnodepar.left = childnode
            else:
                delnodepar.right = childnode
        else:
            self.root = childnode
        
        if delnode != node:
            node.val = delnode.val
        return delnode
        
    
    def insert(self,node):
        if self.root == None:
            self.root = node
        else:
            current_root = self.root
            rootpar = current_root.par
            while current_root != None:
                rootpar = current_root
                if node.val < current_root.val:
                    current_root = current_root.left
                elif node.val > current_root.val:
                    current_root = current_root.right
            node.par = rootpar
            if node.val < rootpar.val:
                rootpar.left = node
            else:
                rootpar.right = node
  
                
    def inorder_traversal(self,root):
        if root == None:
            return []
        else:
            traversal = []
            traversal.extend(self.inorder_traversal(root.left))
            traversal.append(root.val)
            traversal.extend(self.inorder_traversal(root.right))          
            return traversal
        
               
binary_tree = BinaryTree()

root_node = binary_tree.get_root()
node5 = TreeNode(5)
binary_tree.insert(node5)
node2 = TreeNode(2)
binary_tree.insert(node2)
root_node = binary_tree.get_root()

node3 = TreeNode(1)
binary_tree.insert(node3)
node4 = TreeNode(8)
binary_tree.insert(node4)
root_node = binary_tree.get_root()

print root_node.val
print binary_tree.inorder_traversal(root_node)
print binary_tree.delete(node4).val
print binary_tree.inorder_traversal(root_node)

# print binary_tree.inorder_traversal(root_node)
# node = binary_tree.search(5)
# binary_tree.delete(node)


# print binary_tree.inorder_traversal(root_node)


