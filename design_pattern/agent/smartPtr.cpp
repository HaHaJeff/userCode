#include <iostream>
using namespace std;

class CKRefCount {
public:
    CKRefCount() : m_count(0) {};

protected:
    /*这里是没有考虑线程安全的*/
    void addRef()  { m_nCount += 1; };
    void release() { m_nCount -= 1; };
    void reset()   { m_nCount = 0;  };
private:
    unsigned int m_nCount;
};

typename<class T>
class CSmartPtr {
public:
    CSmartPtr(void) : m_pData(NULL) {
        m_pRefCount = new CKRefCount();
        m_pRefCount->addRef();
    };

    CSmartPtr(T *pValue) : m_pData(pValue) {
        m_pRefCount = new CKRefCount();
        m_pRefCount->addRef();
    };

    ~CSmartPtr() {
        if( NULL != m_pRefCount ) {
            m_pRefCount->release();
            delete(m_pData);
            delete(m_pRefCount);
            m_pData     = NULL;
            m_pRefCount = NULL;
        }
    };
protected:

private:
    T *m_pData;
    CKRefCount *m_pRefCount;
};

int main(void)
{
    
    return 0;
}
