#include "EmployeeRepository.h"
#include <gtest/gtest.h>
#include <windows.h> 

using namespace std;

bool deleteFile(const string& filename) {
    return DeleteFileA(filename.c_str()) != 0;
}

TEST(EmployeeRepositoryTest, AddAndFindEmployee) {
    string testFile = "test_employees.bin";

    deleteFile(testFile);

    EmployeeRepository repo(testFile);

    Employee emp1(1, "Test User", 40.0);
    repo.addEmployee(emp1);

    Employee* found = repo.findEmployeeById(1);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getId(), 1);
    EXPECT_EQ(found->getName(), "Test User");
    EXPECT_EQ(found->getHours(), 40.0);

    Employee* notFound = repo.findEmployeeById(999);
    EXPECT_EQ(notFound, nullptr);

    deleteFile(testFile);
}

TEST(EmployeeRepositoryTest, UpdateEmployee) {
    string testFile = "test_update.bin";

    deleteFile(testFile);

    EmployeeRepository repo(testFile);

    Employee emp1(1, "Old Name", 10.0);
    repo.addEmployee(emp1);

    Employee updated(1, "New Name", 20.0);
    repo.updateEmployee(1, updated);

    Employee* found = repo.findEmployeeById(1);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getName(), "New Name");
    EXPECT_EQ(found->getHours(), 20.0);

    deleteFile(testFile);
}

TEST(EmployeeRepositoryTest, GetAllEmployees) {
    string testFile = "test_getall.bin";

    deleteFile(testFile);

    EmployeeRepository repo(testFile);

    Employee emp1(1, "First", 10.0);
    Employee emp2(2, "Second", 20.0);

    repo.addEmployee(emp1);
    repo.addEmployee(emp2);

    vector<Employee> all = repo.getAllEmployees();
    EXPECT_EQ(all.size(), 2);

    deleteFile(testFile);
}

TEST(EmployeeRepositoryTest, SimpleConstructor) {
    EmployeeRepository repo("dummy.bin");
    SUCCEED(); 
}