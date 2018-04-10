#include <iostream>

using namespace std;


class CProduct {
public:
protected:
    CProduct(){};
private:
};

class CConcreteProductA : public CProduct {
public:
    CConcreteProductA() {
        cout << "具体产品A" << endl;
    }
protected:
private:
};

class CConcreteProductB : public CProduct {
public:
    CConcreteProductB() {
        cout << "具体产品B" << endl;
    }
protected:
private:
};

class CMethodFac {
public:
    virtual CProduct* product() = 0;
protected:
private:
};

class CProductAFac : public CMethodFac {
public:
    virtual CProduct* product() {
        return new CConcreteProductA;
    }
protected:
private:
};

class CProductBFac : CMethodFac {
public:
    virtual CProduct* product() {
        return new CConcreteProductB;
    }
protected:
private:
};

int main(void) {
    CMethodFac* pFac = new CProductAFac;
    pFac->product();
    delete pFac;
    pFac = NULL;
    return 0;

}
