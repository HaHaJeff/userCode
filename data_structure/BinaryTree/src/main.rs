type TreeNode<Key, Val> = Option<Box<Node<Key, Val>>>;

#[derive(Debug)]
struct Node<Key: PartialOrd, Val: std::fmt::Display> {
    left: TreeNode<Key, Val>,
    right: TreeNode<Key, Val>,
    key: Key,
    val: Val, 
}

trait BinaryTree<Key: PartialOrd, Val: std::fmt::Display> {
    fn preOrder(&self);
    fn inOrder(&self);
    fn posOrder(&self);
}

trait BinarySearchTree<Key: PartialOrd, Val: std::fmt::Display> {
    fn insert(&mut self, key: Key, val: Val);
}

impl<Key: PartialOrd, Val: std::fmt::Display> Node<Key, Val> {
    fn new(key:Key, val: Val) -> Self {
        Node {
            left: None,
            right: None,
            key: key,
            val: val,
        }
    }
}

impl<Key: PartialOrd, Val: std::fmt::Display> BinarySearchTree<Key, Val> for Node<Key, Val>{
    fn insert(&mut self, key: Key, val: Val) {
        if self.key < key {
            if let Some(ref mut right) = self.right {
                right.insert(key, val);
            } else {
                self.right = Some(Box::new(Node::new(key, val)));
            }
        } else {
            if let Some(ref mut left) = self.left {
                left.insert(key, val);
            } else {
                self.left = Some(Box::new(Node::new(key, val)));
            }
        }
    }
}

type BST<Key, Val> = Node<Key, Val>;
fn test_insert() {
    let mut root = BST::<i32, i32>::new(3, 4);
    root.insert(2, 3);
    root.insert(4, 6);
    root.insert(5, 5);
    if let Some(ref left) = root.left {
        assert_eq!(left.val, 3);
    }
    println!("{:?}", root);
}

fn main() {
    test_insert();
}
