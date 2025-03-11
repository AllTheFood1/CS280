using System.ComponentModel.DataAnnotations;

namespace RedBlackTree
{
    public class Node
    {
        public int? value;
        public Node? parent;
        public Node? leftChild;
        public Node? rightChild;
        public bool color = false;

        public Node(int? value, Node? parent, Node? leftChild, Node? rightChild, bool color = false)
        {
            this.value = value;
            this.parent = parent;
            this.leftChild = leftChild;
            this.rightChild = rightChild;
            this.color = color;
        }
        public Node(){ }
    }
    public class RedBlackTree
    {
        private Node? root;
        public void AddNode(int value)
        {
            Node? tmp = root;
            if(tmp == null)
            {
                Node newNode = new Node(value, null, new Node(), new Node());
                newNode.leftChild.parent = newNode;
                newNode.rightChild.parent = newNode;
                root = newNode;
            }else
            {
                Node newParent = root;
                while(tmp.value != null)
                {
                    newParent = tmp;
                    if(value < tmp.value)
                    {
                        tmp = tmp.leftChild;
                    }else if(value > tmp.value)
                    {
                        tmp = tmp.rightChild;
                    }
                }
                if(value < newParent.value)
                {
                    newParent.leftChild.value = value;
                    newParent.leftChild.leftChild = new Node();
                    newParent.leftChild.leftChild.parent = newParent;
                    newParent.leftChild.rightChild = new Node();
                    newParent.leftChild.rightChild.parent = newParent;
                }else if(value > newParent.value)
                {
                    newParent.rightChild.value = value;
                    newParent.rightChild.rightChild = new Node();
                    newParent.rightChild.rightChild.parent = newParent;
                    newParent.rightChild.leftChild = new Node();
                    newParent.rightChild.leftChild = newParent;
                }
            }
        }
        public void DeleteNode(int value)
        {
            Node? toDelete = Search(value);
            if((toDelete.leftChild.value == null && toDelete.rightChild.value != null) || (toDelete.rightChild.value == null && toDelete.leftChild.value != null))
            {
                if(toDelete.parent == null)
                {
                    if(toDelete.leftChild.value == null)
                    {
                        
                    }
                }else if(toDelete.parent.rightChild == toDelete)
                {
                    toDelete.parent.rightChild = toDelete.rightChild;
                    toDelete.rightChild.parent = toDelete.parent;
                }else if(toDelete.parent.leftChild == toDelete)
                {
                    toDelete.parent.leftChild = toDelete.leftChild;
                    toDelete.leftChild.parent = toDelete.parent;
                }
            }else if(toDelete.leftChild.value != null && toDelete.rightChild.value != null)
            {
                
            }
            toDelete = null;
            GC.Collect();
            GC.WaitForPendingFinalizers();
        }
        public Node? Search(int value)
        {
            Node? tmp = root; 
            if(tmp == null)
            {
                return null;
            }else
            {
                while(tmp.value != null)
                {
                    if(tmp.value == value)
                    {
                        return tmp;
                    }
                    if(value > tmp.value)
                    {
                        tmp = tmp.rightChild;
                    }else if(value < tmp.value)
                    {
                        tmp = tmp.leftChild;
                    }
                }
            }
            return null;
        }
    }
    
    class Program
    {
        public static void Main(string[] args)
        {
            RedBlackTree tree = new RedBlackTree();
        }
    }
}