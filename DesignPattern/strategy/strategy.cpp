#include <iostream>

using namespace std;

class CStrategy {
public:
    CStrategy() {};

    virtual void operate() = 0;

protected:
private:
};

class CContext {
public:

    CContext(CStrategy* strategy) {
        m_strategy = strategy;
    };

    void operate() {
        if(NULL == m_strategy) return;
        m_strategy->operate();
    }
    
    ~CContext() {
        if(NULL != m_strategy) {
            delete m_strategy;
            m_strategy = NULL;
        }
    }
protected:
    

private:
    CStrategy* m_strategy;
};


class CConcrateStrategyA : public CStrategy{
public:
    CConcrateStrategyA() {};
 
    virtual void operate() {
        cout << "具体策略A" << endl;
    };
protected:
private:
};

class CConcrateStrategyB : public CStrategy{
public:
    CConcrateStrategyB() {};
    
    virtual void operate() {
        cout << "具体策略B" << endl;
    };
protected:
private:
};

int main(void) {
    CConcrateStrategyA *strategyA = new CConcrateStrategyA;

    CContext cxt(strategyA);
    
    cxt.operate();
    return 0;
}
