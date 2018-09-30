#ifndef CHASH_H
#define CHASH_H
#include <map>
// Key:   hash value
// Value: T(means node or virtual node)  
template <typename T, typename Hash, typename Alloc = std::allocator<std::pair<const typename Hash::result_type, T>>>
class CHash {
public:
    typedef typename Hash::result_type Key;
    typedef std::map<Key, T, std::less<Key>, Alloc> Map;
    typedef typename Map::value_type Value;
    typedef Value& Ref;
    typedef const Value& CRef;
    typedef typename Map::iterator Iterator;
    typedef typename Map::reverse_iterator RIterator;

public:
    CHash() {
    }

    ~CHash() {
    }

public:
    std::size_t Size() const {
        return nodes_.size();
    }

    bool Empty() const {
        return nodes_.empty();
    }

    void Erase(Iterator iter) {
        nodes_.erase(iter);
    }

    void Erase(const T& node) {
        Value hash = hasher_(node);
        return nodes_.erase(hash);
    }

    std::pair<Iterator, bool> Insert(const T& node) {
        Key hash = hasher_(node);
        return nodes_.insert(Value(hash, node));
    }

    // return first location which don't less than the key
    Iterator Find(const Key& key) {
        if (nodes_.empty()) {
            return nodes_.end();
        }

        Iterator iter = nodes_.lower_bound(key);
        // ring hash
        if (iter == nodes_.end()) {
            iter = nodes_.begin();
        }
        return iter;
    }

    Iterator Begin() {
        return nodes_.begin();
    }

    Iterator End() {
        return nodes_.end();
    }

    RIterator RBegin() {
        return nodes_.rbegin();
    }
    
    RIterator REnd() {
        return nodes_.rend();
    }
private:
    Hash hasher_;
    Map nodes_;
};

#endif