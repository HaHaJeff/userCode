#include <iostream>

using namespace std;

class CComponent {
public:
    CComponent() {};
    virtual void decorator() = 0;
protected:
private:
};

class CConcrateComponent : public CComponent {
public:
    CConcrateComponent() {};

    virtual void decorator() {
        cout << "具体组件的装饰" << endl;
    };
protected:
private:
};

class CDecorator : public CComponent{
public:
    CDecorator() {};
    
    void setDecorator(CComponent *component) {
        m_component = component;
    }
    
   virtual void decorator() {
        m_component->decorator();
    }

    virtual ~CDecorator() {
        if(NULL != m_component) {
            delete(m_component);
            m_component = NULL;
        }
    }
protected:
    CComponent *m_component;
private:
};

class CConcrateDecoratorA : public CDecorator {
public:
    CConcrateDecoratorA() {};

    virtual void decorator() {
        CDecorator::decorator();

        cout << "具体装饰A" << endl;
    }

protected:
private:
};

class CConcrateDecoratorB : public CDecorator {
public:
    CConcrateDecoratorB() {};

    virtual void decorator() {
        CDecorator::decorator();

        cout << "具体装饰B" << endl;
    }

protected:
private:
};
int main(void) {
    CConcrateDecoratorA *decA = new CConcrateDecoratorA;
    CConcrateDecoratorB *decB = new CConcrateDecoratorB;
    
    CConcrateComponent *com = new CConcrateComponent;

    decA->setDecorator(com);
    
    decB->setDecorator(decA);
    
    decB->decorator();
   
    delete(decB);
    decB = NULL;

    return 0;
}
