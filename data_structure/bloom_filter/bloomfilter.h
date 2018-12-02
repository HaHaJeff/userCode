#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

const  uint32_t gMagicHash = 0xbc9f1d34;

inline uint32_t decodeFixed32(const char* ptr);
uint32_t hashFunc(const char* data, size_t n, uint32_t seed);

class Key {
  public:
    Key(const int32_t key);
    uint32_t hash(uint32_t seed) const;
  private:
    int32_t key_;
};


// BloomFilter删除操作会导致正确性问题
template <typename T>
class BloomFilter {
  public:
    BloomFilter(const int32_t n, const double flasePositiveP);
    void insert(const T& key);
    bool keyMayMatch(const T& key);
    void printSelf();

#ifdef OPT
    void insertOpt(const T & key);
    bool keyMayMatchOpt(const T& key);
#endif
  private:
    std::vector<char> bits_;
    int32_t k_;  //hash函数个数
    int32_t m_;  //布隆过滤器大小
    int32_t n_;  //数据个数
    double p_;   //失误率
};


// m = -(n*lnp)/(ln2*ln2)
// k = ln2*m/n = -lnp/ln2
template<typename T>
BloomFilter<T>::BloomFilter(const int32_t n, const double falsePositiveP)
  : bits_(), k_(0), m_(0), n_(n), p_(falsePositiveP) {
    k_ = static_cast<int32_t>(-std::log(p_)/std::log(2));
    m_ = static_cast<int32_t>(k_*n_*1.0/std::log(2));
    bits_.resize((m_+7)/8, 0);
}

template<typename T>
void BloomFilter<T>::insert(const T& key) {
  uint32_t hashVal = gMagicHash;
  for (int i = 0; i < k_; ++i) {
    hashVal = key.hash(hashVal);
    const uint32_t bitPos = hashVal % m_;
    bits_[bitPos/8] |= 1 << (bitPos%8);
  }
}

template<typename T>
bool BloomFilter<T>::keyMayMatch(const T& key) {
  uint32_t hashVal = gMagicHash;
  for (int i = 0; i < k_; ++i) {
    hashVal = key.hash(hashVal);
    const uint32_t bitPos = hashVal % m_;
    if ((bits_[bitPos/8] & (1<<(bitPos%8))) == 0) {
      return false;
    }
  }
  return true;
}

template<typename T>
void BloomFilter<T>::printSelf() {
  std::cout << "hash func num: " << k_ << std::endl;
  std::cout << "bloomfilter size: " << m_ << std::endl;
  std::cout << "data num: " << n_ << std::endl;
  std::cout << "fasle false positive: " << p_ << std::endl;
}

#ifdef OPT
template<typename T>
void BloomFilter<T>::insertOpt(const T& key) {
  uint32_t hashVal = key.hash(gMagicHash);
  const uint32_t delta = (hashVal >> 17) | (hashVal << 15);
  for (int i = 0; i < k_; ++i) {
    const uint32_t bitPos = hashVal % m_;
    bits_[bitPos/8] |= 1 << (bitPos%8);
    hashVal += delta;
  }
}

template<typename T>
bool BloomFilter<T>::keyMayMatchOpt(const T& key) {
  uint32_t hashVal = key.hash(gMagicHash);
  const uint32_t delta = (hashVal >> 17) | (hashVal << 15);
  for (int i = 0; i < k_; ++i) {
    const uint32_t bitPos = hashVal % m_;
    if ((bits_[bitPos/8] & (1<<(bitPos%8))) == 0) {
      return false;
    }
    hashVal += delta;
  }
  return true;
}
#endif

#endif
