#include <iostream>

using namespace std;

class CSubject {
public:
    CSubject() {};

    virtual void request() = 0;

protected:
private:
};

class CRealSubject : public CSubject {
public:
    CRealSubject() {};

    virtual void request() {
        cout << "request of CRealSubject" << endl;
    };

protected:
private:
};


class CProxy : public CSubject {
public:
    CProxy(CSubject *subject) {
        m_pSubject = subject;
    };

    virtual void request() {
        if(NULL == m_pSubject){
            return;
        }
        m_pSubject->request();
    };

    ~CProxy() {
        if(NULL != m_pSubject) {
            delete(m_pSubject);
            m_pSubject = NULL;
        }
    }

protected:
private:
    CSubject *m_pSubject;
};

int main(void)
{
    CSubject *sub = new CRealSubject;
    CProxy proxy(sub);
    proxy.request();
    return 0;
}
