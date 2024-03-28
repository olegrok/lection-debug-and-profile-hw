#include "gtest/gtest.h"
#include <cstddef>
#include "stack.h"

class StackTest : public testing::Test {
protected:
    void SetUp() override {
        initStack(&stack);
    }

    void TearDown() override {
        destroyStack(&stack);
    }

    Stack stack;
};

TEST_F(StackTest, IsEmptyTest) {
    EXPECT_TRUE(isEmpty(&stack));

    push(&stack, 100);
    EXPECT_FALSE(isEmpty(&stack));

    pop(&stack);
    EXPECT_TRUE(isEmpty(&stack));
}

TEST_F(StackTest, PushPopTest) {
    EXPECT_EQ(getTop(&stack), nullptr);
    EXPECT_EQ(pop(&stack), false);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    EXPECT_EQ(getTop(&stack)->data, 30);
    EXPECT_EQ(pop(&stack), true);

    EXPECT_EQ(getTop(&stack)->data, 20);
    EXPECT_EQ(pop(&stack), true);

    EXPECT_EQ(getTop(&stack)->data, 10);
    EXPECT_EQ(pop(&stack), true);

    EXPECT_EQ(getTop(&stack), nullptr);
    EXPECT_EQ(pop(&stack), false);
}

TEST_F(StackTest, searchByValue) {
    EXPECT_EQ(searchByValue(&stack, 10), nullptr);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    EXPECT_EQ(searchByValue(&stack, 100), nullptr);

    EXPECT_EQ(searchByValue(&stack, 10)->data, 10);
    EXPECT_EQ(searchByValue(&stack, 20)->data, 20);
    EXPECT_EQ(searchByValue(&stack, 30)->data, 30);

    EXPECT_EQ(pop(&stack), true);

    EXPECT_EQ(searchByValue(&stack, 10)->data, 10);
    EXPECT_EQ(searchByValue(&stack, 20)->data, 20);
    EXPECT_EQ(searchByValue(&stack, 30), nullptr);
}

TEST_F(StackTest, searchByIndex) {
    EXPECT_EQ(searchByIndex(&stack, -10), nullptr);
    EXPECT_EQ(searchByIndex(&stack, 0), nullptr);
    EXPECT_EQ(searchByIndex(&stack, 10), nullptr);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    EXPECT_EQ(searchByIndex(&stack, 0)->data, 30);
    EXPECT_EQ(searchByIndex(&stack, 1)->data, 20);
    EXPECT_EQ(searchByIndex(&stack, 2)->data, 10);
    EXPECT_EQ(searchByIndex(&stack, 3), nullptr);
}

TEST_F(StackTest, getTop) {
    EXPECT_EQ(getTop(&stack), nullptr);

    push(&stack, 10);
    EXPECT_EQ(getTop(&stack)->data, 10);

    push(&stack, 20);
    EXPECT_EQ(getTop(&stack)->data, 20);

    EXPECT_EQ(pop(&stack), true);
    EXPECT_EQ(getTop(&stack)->data, 10);

    EXPECT_EQ(pop(&stack), true);
    EXPECT_EQ(getTop(&stack), nullptr);
}

TEST_F(StackTest, traverseStack) {
    traverseStack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    traverseStack(&stack);

    EXPECT_EQ(pop(&stack), true);
    EXPECT_EQ(pop(&stack), true);
    EXPECT_EQ(pop(&stack), true);

    traverseStack(&stack);
}

TEST_F(StackTest, isEmpty) {
    EXPECT_EQ(isEmpty(&stack), true);

    push(&stack, 10);

    EXPECT_EQ(isEmpty(&stack), false);

    EXPECT_EQ(pop(&stack), true);

    EXPECT_EQ(isEmpty(&stack), true);
}
