#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <unordered_map>
#include <list>
#include <cstddef>
#include <stdexcept>
#include <iostream>


namespace cache {

  // 非线程安全
  // 头部数据为最热的
  template <typename key_t, typename value_t>
  class LRUCache {
    public:
      typedef typename std::pair<key_t, value_t> key_value_pair_t;
      typedef typename std::list<key_value_pair_t>::iterator list_iterator_t;

    public:
      //缓存链表长度,超出max_size之后应该进行缓存替换
      LRUCache(size_t max_size) : max_size_(max_size){}

      // 新数据插入链表头部
      // 如果新数据已经存在，那么在插入之后进行删除, 为了提高效率，采用一个unorder_map对数据位置进行记录
      // 如果超出缓存长度，删除尾部
      void Put(const key_t& key, const value_t& value) {
        auto iter = cache_items_map_.find(key);

        // insert
        cache_items_list_.push_front(key_value_pair_t(key, value));

        // 如果存在数据
        if (iter != cache_items_map_.end()) {
          cache_items_list_.erase(iter->second);
          //cache_items_map_.erase(iter);
        }

        cache_items_map_[key] = cache_items_list_.begin();

        // 替换缓存
        if (cache_items_map_.size() > max_size_) {
          auto last = cache_items_list_.end();
          last--;
          cache_items_map_.erase(last->first);
          cache_items_list_.pop_back();
        }
      }

      // Get操作过后应该将访问的数据移动至头部
      const value_t& Get(const key_t& key) {
        auto iter = cache_items_map_.find(key);
        if (iter == cache_items_map_.end()) {
          throw std::range_error("There is no such key in cache");
        } else {
          cache_items_list_.splice(cache_items_list_.begin(), cache_items_list_, iter->second);
          // FIXME: update iter in map, but list iter is pointer, so maybe not need update
          cache_items_map_[iter->first] = cache_items_list_.begin();
          return iter->second->second;
        }
      }

      bool Exists(const key_t& key) const {
        return cache_items_map_.find(key) != cache_items_map_.end();
      }

      size_t Size() const {
        return cache_items_map_.size();
      }

      void Print() const {
          for (auto& i : cache_items_list_) {
              std::cout << "key:" << i.first << "\tvalue:" << i.second << std::endl; 
          }
      }
    private:
      //禁止拷贝,赋值
      LRUCache(const LRUCache&) {}
      void operator=(const LRUCache&){}

    private:
      // 因为删除操作可能会很多，所以选择list而非vector
      // 选用map记录key对应的list_node在list中的位置，从而快速查找删除
      // 每次插入新的node，直接插入到链表头部，并在map中查找新的node是否
      // 在map中出现过，如果出现则直接删除该node在list中的位置，从而保证
      // 只有一个list中只有一个包含相同key的node
      // map的好处是：如果插入的node在list中已经存在了话可以快速删除该node
      std::unordered_map<key_t, list_iterator_t> cache_items_map_;
      std::list<key_value_pair_t> cache_items_list_;
      size_t max_size_;
  };
}

#endif
