#include "Employee.h"
#include <gtest/gtest.h>

using namespace std;

TEST(EmployeeTest, ConstructorAndGetters) {
    Employee emp(123, "Sonia", 40.5);

    EXPECT_EQ(emp.getId(), 123);
    EXPECT_EQ(emp.getName(), "Sonia");
    EXPECT_EQ(emp.getHours(), 40.5);
}

TEST(EmployeeTest, SetName) {
    Employee emp(1, "Old Name", 10.0);
    emp.setName("New Name");

    EXPECT_EQ(emp.getName(), "New Name");
}

TEST(EmployeeTest, SetHours) {
    Employee emp(1, "Test", 10.0);
    emp.setHours(20.5);

    EXPECT_EQ(emp.getHours(), 20.5);
}

TEST(EmployeeTest, SerializeDeserialize) {
    Employee emp1(100, "Alice", 35.5);

    char buffer[Employee::getSerializedSize()];
    emp1.serialize(buffer);

    Employee emp2;
    emp2.deserialize(buffer);

    EXPECT_EQ(emp1.getId(), emp2.getId());
    EXPECT_EQ(emp1.getName(), emp2.getName());
    EXPECT_EQ(emp1.getHours(), emp2.getHours());
}

TEST(EmployeeTest, GetSerializedSize) {
    size_t size = Employee::getSerializedSize();
    EXPECT_GT(size, 0);
}