#include <string.h>
#include "bloomfilter.h"

const uint32_t sMurmurMagic = 0xc6a4a793;

inline uint32_t decodeFixed32(const char* ptr) {
  uint32_t result;
  memcpy(&result, ptr, sizeof(result));
  return result;
}

uint32_t hashFunc(const char* data, size_t n, uint32_t seed) {
  const uint32_t m = sMurmurMagic;
  const uint32_t r = 24;
  const char* limit = data + n;
  uint32_t h = seed ^ (n*m);

  while ( data+4 <= limit ) {
    uint32_t w = decodeFixed32(data);
    data += 4;
    h += w;
    h *= m;
    h ^= (h >> 16);
  }

  switch(limit - data) {
    case 3:
      h += static_cast<unsigned char>(data[2]) << 16;
    case 2:
      h += static_cast<unsigned char>(data[1]) << 8;
    case 1:
      h += static_cast<unsigned char>(data[0]);
      h *= m;
      h ^= (h >> r);
      break;
  }
  return h;
}

Key::Key(const int32_t key) 
  : key_(key)

{ 
}

uint32_t Key::hash(uint32_t seed) const {
  return hashFunc(reinterpret_cast<const char*>(&key_), sizeof(key_), seed);
}
