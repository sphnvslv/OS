#include "threads.h"

using namespace std;

threads::threads(arrPtr arrManager)
    : mArrManager(arrManager) {
}

threads::~threads() {
    for (auto& thread : mThreads) {
        if (thread && thread->IsRunning()) {
            thread->Signal(ThreadSignal::TERMINATE);
        }
    }

    for (auto& thread : mThreads) {
        if (thread) {
            thread->Join();
        }
    }
}

bool threads::CreateThreads(int threadCount) {
    if (threadCount <= 0) {
        PrintError("Wrong thread count: " + to_string(threadCount));
        return false;
    }

    mThreads.clear();

    for (int i = 0; i < threadCount; ++i) {
        int threadId = i + 1;
        auto thread = make_shared<marker>(threadId, mArrManager);
        mThreads.push_back(thread);
    }

    return true;
}

void threads::StartAllThreads() {
    for (auto& thread : mThreads) {
        if (thread) {
            thread->Start();
        }
    }

    SleepFor(100);
    for (auto& thread : mThreads) {
        if (thread) {
            thread->Signal(ThreadSignal::START);
        }
    }

    PrintMess("All threads started");
}

void threads::WaitAllThreadsBlocked() {
    bool allBlocked = false;

    while (!allBlocked) {
        allBlocked = true;
        SleepFor(100);

        for (auto& thread : mThreads) {
            if (thread && thread->IsRunning() && !thread->IsBlocked()) {
                allBlocked = false;
                break;
            }
        }
    }

    PrintMess("All threads are blocked");
}

void threads::ContinueAllThreads() {
    for (auto& thread : mThreads) {
        if (thread && thread->IsRunning()) {
            thread->Signal(ThreadSignal::CONTINUE);
        }
    }
}

void threads::TerminateThread(int threadId) {
    for (auto& thread : mThreads) {
        if (thread && thread->GetId() == threadId && thread->IsRunning()) {
            thread->Signal(ThreadSignal::TERMINATE);
            PrintMess("Sent TERMINATE signal to thread " + to_string(threadId));
            return;
        }
    }
    PrintError("Thread not found or not active: " + to_string(threadId));
}

void threads::WaitForThreadTermination(int threadId) {
    for (auto& thread : mThreads) {
        if (thread && thread->GetId() == threadId) {
            thread->Join();
            break;
        }
    }
    PrintMess("Thread " + to_string(threadId) + " termination completed");
}

bool threads::IsThreadExists(int threadId) const {
    for (auto& thread : mThreads) {
        if (thread && thread->GetId() == threadId) {
            return true;
        }
    }
    return false;
}

int threads::GetActiveThreadCount() const {
    int count = 0;
    for (const auto& thread : mThreads) {
        if (thread && thread->IsRunning()) {
            count++;
        }
    }
    return count;
}