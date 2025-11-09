#include "Core.h"
#include "arr/arr.h"
#include "threads/threads.h"
using namespace std;

int main() {
    PrintMess("=== Parallel Marker ===");

    try {
        auto arrManager = make_shared<arr>();
        int arrSize = GetValidatedInput("Enter array size: ");

        if (!arrManager->InitializeArr(arrSize)) {
            PrintError("Failed to initialize array");
            return 1;
        }

        auto threadManager = make_unique<threads>(arrManager);

        int threadCount = GetValidatedInput("Enter number of marker threads: ");

        if (!threadManager->CreateThreads(threadCount)) {
            PrintError("Failed to create threads");
            return 1;
        }

        threadManager->StartAllThreads();
        PrintMess("All threads are running");

        while (threadManager->GetActiveThreadCount() > 0) {
            threadManager->WaitAllThreadsBlocked();

            arrManager->PrintArr();

            int threadToTerminate;
            do {
                threadToTerminate = GetValidatedInput(
                    "Enter thread number to terminate (1-" + to_string(threadCount) + "): ", 1);

                if (!threadManager->IsThreadExists(threadToTerminate)) {
                    PrintError("Thread " + to_string(threadToTerminate) + " does not exist");
                }
            } while (!threadManager->IsThreadExists(threadToTerminate));

            threadManager->TerminateThread(threadToTerminate);
            threadManager->WaitForThreadTermination(threadToTerminate);
            arrManager->PrintArr();

            if (threadManager->GetActiveThreadCount() > 0) {
                threadManager->ContinueAllThreads();
            }

            PrintMess("Active threads remaining: " + to_string(threadManager->GetActiveThreadCount()));
        }

        PrintMess("All threads have finished. Program completed");

    }
    catch (const exception& e) {
        PrintError("Exception occurred: " + string(e.what()));
        return 1;
    }
    catch (...) {
        PrintError("Unknown exception occurred");
        return 1;
    }

    return 0;
}