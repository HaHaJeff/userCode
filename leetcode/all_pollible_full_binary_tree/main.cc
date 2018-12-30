/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
#include "leetcode.h"
using namespace std;

// 完全二叉树的节点必为奇数
// allBT(i)  allBT(n-i-1)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
	vector<TreeNode*> allPossibleFBT(int N) {
		vector<TreeNode*> results;

		results = allFBT(N);
        
        return results;
	}

	vector<TreeNode*> allFBT(int N) {
		vector<TreeNode*> results;
		if (caches_.find(N) != caches_.end()) { return caches_[N]; }
		if (N & 1 == 0) { return results; }
		if (N == 1) {
			TreeNode* node = new TreeNode(0);
			results.push_back(node);
		} else {
            for (int i = 1; i < N; i+=2) {
			    // 以i为根节点的左右子树组合
			    vector<TreeNode*> leftTrees = allFBT(i);
			    vector<TreeNode*> rightTrees = allFBT(N - i - 1);
			    for (int l = 0; l < leftTrees.size(); l++) {
				    for (int r = 0; r < rightTrees.size(); r++) {
					    TreeNode* root = new TreeNode(0);
					    root->left = leftTrees[l];
					    root->right = rightTrees[r];
					    results.push_back(root);
				    }
			    }			
		    }
        }
		caches_[N] = results;
		return results;
	}
private:
	unordered_map<int, vector<TreeNode*>> caches_;
};
