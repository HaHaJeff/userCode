#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "chash.h"


std::vector<std::string> nodes = {
    "192.168.1.1",
    "192.168.1.2",
    "192.168.1.3",
    "192.168.1.4",
    "192.168.1.5"

};

struct VNode {
    VNode() {}
    VNode(std::size_t node_id, std::size_t vnode_id) : node_id_(node_id), vnode_id_(vnode_id) {}

    std::string ToStr() const {
        char buff[80];
        snprintf(buff, sizeof(buff), "%s-%ld", nodes[node_id_].c_str(), vnode_id_);
        std::string str(buff);
        return str;
    }    

    std::size_t node_id_;
    std::size_t vnode_id_;
};

struct Hasher {
    std::size_t operator()(const VNode& node) {
        return std::hash<std::string>{}(node.ToStr());
    }

    typedef std::size_t result_type; 
};

int main()
{
    typedef CHash<VNode, Hasher> TCHash;
    TCHash chash;

    for (std::size_t i = 0; i < 5; i++) {
        for (std::size_t j = 0; j < 100; j++) {
            chash.Insert(VNode(i,j));
        }
    }

    TCHash::Iterator iter = chash.Begin();
    TCHash::RIterator last = chash.RBegin();
    TCHash::Iterator prev = chash.Begin();

    std::cout << "vnode: " << iter->second.ToStr() << "\thash: " << iter->first << "\t contains:" << last->first - iter->first << std::endl;


    while (++iter != chash.End()) {
        std::cout << "vnode: " << iter->second.ToStr() << "\thash: " << iter->first << "\t contains:" << iter->first - prev->first << std::endl;
        prev = iter;
    }

}