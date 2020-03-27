use std::vec;

pub struct BTNode<Key: PartialOrd, Val> {
    isLeaf: bool,

}

pub trait BTree<Key: PartialOrd> {
    /// If the entry of key exists, panic
    fn insert(&mut self, key: Key, val: Val);
    /// If the entry of key not exists, panic
    fn delete(&mut self, key: Key);
    /// If the entry of key not exists, error
    fn search(&self, key: Key) -> Val;
}