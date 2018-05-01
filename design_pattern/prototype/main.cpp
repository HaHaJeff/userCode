/*************************************************************************
    > File Name: main.cpp
    > Author: MSGF_NGINX
    > Mail: 327767852@qq.com
    > Created Time: 2017年01月30日 星期一 19时55分18秒
 ************************************************************************/

#include<iostream>
using namespace std;

class CPrototype {
public:
	virtual CPrototype* clone() = 0;
private:
protected:
};

class CPrototypeA : public CPrototype{
private:
public:
	virtual CPrototype* clone() {
		cout << "克隆A" << endl;
		return new CPrototypeA(*this);
	};
protected:
};

class CPrototypeB : public CPrototype{
private:
public:
	virtual CPrototype* clone() {
		cout << "克隆B" << endl;
		return new CPrototypeB(*this);
	};
protected:
};

int main(void) {
	CPrototypeB b;
	CPrototype *bClone = b.clone();
	delete bClone;
	bClone = NULL;
	return 0;

}



