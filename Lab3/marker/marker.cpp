#include "marker.h"
using namespace std;

marker::marker(int id, arrPtr arrManager)
    : m_id(id),
    mArrayManager(arrManager),
    mCurrSignal(ThreadSignal::START),
    mSignalReceived(false),
    mBlocked(false),
    mMarkedCount(0),
    mLastFailedInd(-1),
    mRunning(false) {
}

marker::~marker() {
    if (mThread.joinable()) {
        mThread.join();
    }
}

void marker::Start() {
    mRunning = true;
    mThread = thread(&marker::Run, this);
}

void marker::Run() {
    srand(m_id);

    WaitForSignal();

    while (mRunning) {
        MarkElements();

        WaitForSignal();

        if (mCurrSignal == ThreadSignal::TERMINATE) {
            PrintMess("Thread " + to_string(m_id) + " received terminate signal");
            mArrayManager->ResetElByThread(m_id);
            break;
        }
    }

    mRunning = false;
    PrintMess("Thread " + to_string(m_id) + " finished");
}

void marker::MarkElements() {
    mMarkedCount = 0;
    mLastFailedInd = -1;
    mBlocked = false;

    cout << "Thread " << m_id << " started marking" << endl;

    while (mRunning) {
        int randomNum = rand();
        int index = randomNum % mArrayManager->GetSize();

        if (!mArrayManager->SetEl(index, m_id, m_id)) {
            mLastFailedInd = index;
            mBlocked = true;

            cout << "Thread " << m_id
                << " marked " << mMarkedCount
                << " elements, failed at index " << index << endl;

            break;
        }

        mMarkedCount++;
    }
}

void marker::Signal(ThreadSignal signal) {
    {
        lock_guard<mutex> lock(mMutex);
        mCurrSignal = signal;
        mSignalReceived = true;
    }
    m_cv.notify_one();
}

void marker::WaitForSignal() {
    unique_lock<mutex> lock(mMutex);
    m_cv.wait(lock, [this] { return mSignalReceived; });
    mSignalReceived = false;
}

bool marker::IsRunning() const {
    return mRunning;
}

void marker::Join() {
    if (mThread.joinable()) {
        mThread.join();
    }
}

bool marker::IsBlocked() const {
    return mBlocked;
}

void marker::SetBlocked(bool blocked) {
    mBlocked = blocked;
}