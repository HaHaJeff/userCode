#include "header.h"
// ����ջʵ�ֶ���
// ˼·��һ��ջ��Ϊpushר�ã�һ��ջ��Ϊpopר��
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