/*************************************************************************
    > File Name: main.cpp
    > Author: MSGF_NGINX
    > Mail: 327767852@qq.com
    > Created Time: 2017年10月13日 星期五 08时53分23秒
 ************************************************************************/

#include <iostream>

#include <vector>

#include <map>
using namespace std;


struct Node {
    int weight;
    vector<Node *> sons;
};

map<Node *, bool> dpMap;

typedef vector<Node *>::iterator ItNode;

int GetCondition(struct Node* root) {

    if((root->sons).empty()) {
        if(root->weight <0) return  false;
        return true;
    }
    ItNode it = root->sons.begin();

//    if(dpMap.find(root) != dpMap.end()) return dpMap[root];

    bool temp = true;
    while(it != (root->sons).end()) {
        temp &=  GetCondition(*it);
        it++;
    }
    dpMap[root] = temp & dpMap[root];


}

int main(void) {
    struct Node root;
    struct Node root1;
    struct Node root2;
    root.weight = 1;
    root1.weight = -2;
    root2.weight = 3;

    struct Node root11;
    struct Node root12;
    struct Node root13;
    root11.weight = 4;
    root12.weight = 5;
    root13.weight = 6;

    struct Node root21;
    root21.weight = -1;

    root2.sons.push_back(&root21);

    root.sons.push_back(&root1);
    root.sons.push_back(&root2);
    root1.sons.push_back(&root11);
    root1.sons.push_back(&root12);
    root1.sons.push_back(&root13);

    struct Node root111, root112;
    struct Node root121, root122;
    root111.weight = 7;
    root112.weight = -2;
    root121.weight = 8;
    root122.weight = 9;

    root11.sons.push_back(&root111);
    root11.sons.push_back(&root112);
    root12.sons.push_back(&root121);
    root12.sons.push_back(&root122);

    dpMap[&root] = true;
    dpMap[&root1] = false;
    dpMap[&root2] = true;
    dpMap[&root11] = true;
    dpMap[&root12] = true;
    dpMap[&root13] = true;
    dpMap[&root21] = false;
    dpMap[&root111] = true;
    dpMap[&root112] = false;
    dpMap[&root121] = true;
    dpMap[&root122] = true;


    GetCondition(&root);


    return 0;

}
