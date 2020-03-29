use std::cmp;
use std::cmp::Ordering;

type TreeNode<Key, Val> = Option<Box<Node<Key, Val>>>;

#[derive(Debug, Clone)]
pub struct Node<Key, Val>
    where Key: Ord+std::fmt::Display+Copy,
          Val: std::fmt::Display+Copy
{
    pub left: TreeNode<Key, Val>,
    pub right: TreeNode<Key, Val>,
    pub key: Key,
    pub val: Val, 
}

pub struct BinaryTree<Key, Val>
    where Key: Ord+std::fmt::Display+Copy,
          Val: std::fmt::Display+Copy
{
    pub root: TreeNode<Key, Val>
}

impl <Key, Val> BinaryTree<Key, Val>
    where Key: Ord+std::fmt::Display+Copy,
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
                self.root = delete(node, key);
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
    where Key: Ord+std::fmt::Display+Copy,
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

fn delete <Key, Val>(node: &mut Box<Node<Key, Val>>, key: Key) -> Option<Box<Node<Key,Val>>>
    where Key: Ord+std::fmt::Display+Copy,
          Val: std::fmt::Display+Copy
{
}

fn find_max<Key, Val>(node: &mut Box<Node<Key,Val>>) -> Option<Box<Node<Key,Val>>>
    where Key: Ord+std::fmt::Display+Copy,
          Val: std::fmt::Display+Copy
{
    /*
    while let Some(ref mut right) = node.right {
        match right {
            Some(ref mut n) => n = node.right,
            None
        }
    }
    */
    None
}
impl<Key, Val> Node<Key, Val> 
    where Key: Ord+std::fmt::Display+Copy,
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
        println!("<{},{}>", self.key, self.val);
        if let Some(ref left) = self.left {
            left.print();
        }
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

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_insert() -> Result<(), String> {
        let mut tree = BinaryTree::<i32, i32>::new();
        assert_eq!(tree.insert(5, 3), true);
        assert_eq!(tree.insert(2, 3), true);
        assert_eq!(tree.insert(4, 3), true);
        Ok(())
    }
}

fn main()
{

}