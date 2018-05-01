#include <iostream>
using namespace std;

class CProduct {
public:
    CProduct(){};
    virtual void operate() = 0;
protected:

private:
};


class CConcrateProdA : public CProduct {
public:
    CConcrateProdA(){};

    virtual void operate() {
        cout << "具体产品A" << endl;
    };
protected:
private:
};

class CConcrateProdB : public CProduct {
public:
    CConcrateProdB(){};

    virtual void operate() {
        cout << "具体产品B" << endl;
    };
protected:
private:
};

class CFactory {
public:
    CFactory(){};

    CProduct* createProduction(int tag) {
        CProduct *ret = NULL;

        switch(tag) {
            case 0:
                ret = new CConcrateProdA;
                break;
            case 1:
                ret = new CConcrateProdB;
                break;
            default:
                break;
        }

        return ret;
    };

protected:
private:
};

int main(void) {
    CProduct *pro = NULL;
    CFactory fac;
    pro = fac.createProduction(0);

    if(NULL == pro) {
        return -1;
    }

    pro->operate();

    delete pro;
    pro = NULL;

    return 0;
}
