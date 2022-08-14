#include<iostream>
#include<Windows.h>
class CWinLock {
public:
    CWinLock(CRITICAL_SECTION* pCritmp)
    {
        my_winsec = pCritmp;
        EnterCriticalSection(my_winsec);
    }
    ~CWinLock()
    {
        LeaveCriticalSection(my_winsec);
    }
private:
    CRITICAL_SECTION* my_winsec;
};
//Windows版本，不过逻辑是这样，智能指针或者std::lock_guard都是这个原理