type TreeNode<Key, Val> = Option<Box<Node<Key, Val>>>;

#[derive(Debug, Clone)]
pub struct Node<Key, Val>
    where Key: PartialOrd+std::fmt::Display+Copy,
          Val: std::fmt::Display+Copy
{
    left: TreeNode<Key, Val>,
    right: TreeNode<Key, Val>,
    key: Key,
    val: Val, 
}

pub struct BinaryTree<Key, Val>
    where Key: PartialOrd+std::fmt::Display+Copy,
          Val: std::fmt::Display+Copy
{
    pub root: TreeNode<Key, Val>
}

impl <Key, Val> BinaryTree<Key, Val>
    where Key: PartialOrd+std::fmt::Display+Copy,
          Val: std::fmt::Display+Copy
{
    pub fn new() -> Self {
        BinaryTree {
            root: None
        }
    }

    pub fn is_empty(&self) -> bool {
        !self.root.is_some()
    }

    pub fn insert(&mut self, key: Key, val: Val) -> bool {
        match self.root {
            Some(ref mut node) => {
                insert(node, key, val);
                true
            },
            None => {
                self.root = Some(Box::new(Node::new(key, val)));
                true
            }
        }
    }

    pub fn delete(&mut self, key: Key) -> bool {
        match self.root {
            Some(ref mut node) => {
                true
            },
            None => {
                false
            }
        }
    }
    
    pub fn print(&self) {
        match self.root {
            Some(ref node) => node.print(),
            None => panic!(),
        }
    }
}

fn insert<Key, Val>(node: &mut Box<Node<Key, Val>>, key: Key, val: Val)
    where Key: PartialOrd+std::fmt::Display+Copy,
          Val: std::fmt::Display+Copy
{
    if node.key < key {
        if let Some(ref mut right) = node.right {
            insert(right, key, val);
        } else {
            node.right = Some(Box::new(Node::new(key,val)));
        }
    } else {
        if let Some(ref mut left) = node.left {
            insert(left, key, val);
        } else {
            node.left = Some(Box::new(Node::new(key, val)))
        }
    }
}

impl<Key, Val> Node<Key, Val> 
    where Key: PartialOrd+std::fmt::Display+Copy,
          Val: std::fmt::Display+Copy
{
    fn new(key:Key, val: Val) -> Self {
        Node {
            left: None,
            right: None,
            key: key,
            val: val,
        }
    }

    fn print(&self) {
        if let Some(ref left) = self.left {
            left.print();
        }
        println!("<{},{}>", self.key, self.val);
        if let Some(ref right) = self.right {
            right.print();
        }
    }

    fn left(&self) -> &TreeNode<Key,Val> {
        &self.left
    }

    fn right(&self) -> &TreeNode<Key,Val> {
        &self.right
    }

    fn key(&self) -> Key {
        self.key
    }

    fn val(&self) -> Val {
        self.val
    }
}

fn test_insert() {
    let mut tree = BinaryTree::<i32, i32>::new();
    tree.insert(5, 3);
    tree.insert(2, 3);
    tree.insert(4, 3);
    tree.insert(6, 3);
    tree.insert(1, 3);
    tree.insert(3, 3);
    tree.print();
}

fn main() {
    test_insert();
}
