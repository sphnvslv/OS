#pragma once
#include "../Core.h"
#include "../arr/arr.h"

using namespace std;

class marker {
public:
    marker(int id, arrPtr arrayManager);
    ~marker();

    void Start();
    void Signal(ThreadSignal signal);
    void WaitForSignal();
    bool IsRunning() const;
    void Join();
    bool IsBlocked() const;
    void SetBlocked(bool blocked);

    int GetId() const { return m_id; }
    int GetMarkedCount() const { return mMarkedCount; }
    int GetLastFailedIndex() const { return mLastFailedInd; }

private:
    void Run();
    void MarkElements();

    int m_id;
    arrPtr mArrayManager;
    thread mThread;

    mutex mMutex;
    condition_variable m_cv;
    ThreadSignal mCurrSignal;
    bool mSignalReceived;
    bool mBlocked;

    atomic<int> mMarkedCount;
    atomic<int> mLastFailedInd;
    atomic<bool> mRunning;
};

using markerPtr = shared_ptr<marker>;