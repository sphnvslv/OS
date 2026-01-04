#include "gtest/gtest.h"
#include "Database.h"
#include "Task.h"
#include <string>
using namespace std; // Студенческая работа

TEST(TaskTest, ToJson) {
    Task task(1, "Test", "Desc", "todo", "2024-01-01");
    string json = task.to_json();
    EXPECT_TRUE(json.find("\"id\":1") != string::npos);
    EXPECT_TRUE(json.find("\"title\":\"Test\"") != string::npos);
    EXPECT_TRUE(json.find("\"status\":\"todo\"") != string::npos);
}

TEST(TaskTest, DefaultConstructor) {
    Task task;
    EXPECT_EQ(task.id, 0);
    EXPECT_TRUE(task.title.empty());
    EXPECT_TRUE(task.description.empty());
    EXPECT_TRUE(task.status.empty());
    EXPECT_TRUE(task.created_at.empty());
}

TEST(DatabaseTest, OpenClose) {
    Database db;
    EXPECT_TRUE(db.open());
}

TEST(DatabaseTest, CreateAndGetTask) {
    Database db;
    ASSERT_TRUE(db.open());

    int id = db.createTask("Test Task", "Test Description", "todo");
    EXPECT_GT(id, 0);

    Task task = db.getTask(id);
    EXPECT_EQ(task.id, id);
    EXPECT_EQ(task.title, "Test Task");
    EXPECT_EQ(task.description, "Test Description");
    EXPECT_EQ(task.status, "todo");
}

TEST(DatabaseTest, GetAllTasks) {
    Database db;
    ASSERT_TRUE(db.open());

    auto tasks = db.getAllTasks();
    for (const auto& task : tasks) {
        db.deleteTask(task.id);
    }

    int id1 = db.createTask("Task 1", "Desc 1", "todo");
    int id2 = db.createTask("Task 2", "Desc 2", "in_progress");

    EXPECT_GT(id1, 0);
    EXPECT_GT(id2, 0);

    tasks = db.getAllTasks();
    EXPECT_EQ(tasks.size(), 2);

    bool found1 = false, found2 = false;
    for (const auto& task : tasks) {
        if (task.id == id1) {
            EXPECT_EQ(task.title, "Task 1");
            found1 = true;
        }
        if (task.id == id2) {
            EXPECT_EQ(task.title, "Task 2");
            found2 = true;
        }
    }
    EXPECT_TRUE(found1);
    EXPECT_TRUE(found2);
}

TEST(DatabaseTest, UpdateTask) {
    Database db;
    ASSERT_TRUE(db.open());

    int id = db.createTask("Old Title", "Old Desc", "todo");
    ASSERT_GT(id, 0);

    bool updated = db.updateTask(id, "New Title", "New Desc", "done");
    EXPECT_TRUE(updated);

    Task task = db.getTask(id);
    EXPECT_EQ(task.title, "New Title");
    EXPECT_EQ(task.description, "New Desc");
    EXPECT_EQ(task.status, "done");
}

TEST(DatabaseTest, DeleteTask) {
    Database db;
    ASSERT_TRUE(db.open());

    int id = db.createTask("To Delete", "Desc", "todo");
    ASSERT_GT(id, 0);

    Task task = db.getTask(id);
    EXPECT_EQ(task.id, id);

    bool deleted = db.deleteTask(id);
    EXPECT_TRUE(deleted);

    Task deletedTask = db.getTask(id);
    EXPECT_EQ(deletedTask.id, 0);
}

TEST(DatabaseTest, InvalidTaskId) {
    Database db;
    ASSERT_TRUE(db.open());

    Task task = db.getTask(99999);
    EXPECT_EQ(task.id, 0);

    bool updated = db.updateTask(99999, "Title", "Desc", "todo");
    EXPECT_FALSE(updated);

    bool deleted = db.deleteTask(99999);
    EXPECT_FALSE(deleted);
}

TEST(DatabaseTest, TaskStatusValidation) {
    Database db;
    ASSERT_TRUE(db.open());

    int id1 = db.createTask("Task 1", "Desc", "todo");
    int id2 = db.createTask("Task 2", "Desc", "in_progress");
    int id3 = db.createTask("Task 3", "Desc", "done");

    EXPECT_GT(id1, 0);
    EXPECT_GT(id2, 0);
    EXPECT_GT(id3, 0);

    EXPECT_EQ(db.getTask(id1).status, "todo");
    EXPECT_EQ(db.getTask(id2).status, "in_progress");
    EXPECT_EQ(db.getTask(id3).status, "done");

    db.updateTask(id1, "Task 1", "Desc", "in_progress");
    EXPECT_EQ(db.getTask(id1).status, "in_progress");
}

TEST(DatabaseTest, EmptyTitle) {
    Database db;
    ASSERT_TRUE(db.open());

    int id = db.createTask("", "Description", "todo");
    EXPECT_GT(id, 0);

    if (id > 0) {
        Task task = db.getTask(id);
        EXPECT_TRUE(task.title.empty());
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}