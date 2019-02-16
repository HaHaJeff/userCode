#include "header.h"
// 两个栈实现队列
// 思路：一个栈作为push专用，一个栈作为pop专用
class Solution4
{
public:
	void push(int node) {
		stack1.push(node);
	}

	int pop() {
		if (stack2.empty()) {
			while (!stack1.empty()) {
				stack2.push(stack1.top());
				stack1.pop();
			}
		}
		int top = stack2.top();
		stack2.pop();
		return top;
	}

private:
	stack<int> stack1;
	stack<int> stack2;
};