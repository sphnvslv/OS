#pragma once
#include "../Core.h"
#include "../marker/marker.h"
#include "../arr/arr.h"
#include <vector>
#include <memory>

using namespace std;

class threads {
public:
    threads(arrPtr arrayManager);
    ~threads();

    bool CreateThreads(int threadCount);
    void StartAllThreads();
    void WaitAllThreadsBlocked();
    void ContinueAllThreads();
    void TerminateThread(int threadId);
    void WaitForThreadTermination(int threadId);
    bool IsThreadExists(int threadId) const;
    int GetActiveThreadCount() const;
    const vector<markerPtr>& GetThreads() const { return mThreads; }

private:
    vector<markerPtr> mThreads;
    arrPtr mArrManager;
};