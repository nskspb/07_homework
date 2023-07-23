#include <iostream>
#include "serial_container.hpp"

#include <gtest/gtest.h>

struct SerialFixture : public testing::Test
{
    const size_t element_count = 10;
    serial_container<size_t> serial;

    static void SetUpTestSuite()
    {
        std::cout << "SetUpTestSuite" << std::endl;
    }

    static void TearDownTestSuite()
    {
        std::cout << "TearDownTestSuite" << std::endl;
    }

    void SetUp() override
    {
        std::cout << "SetUp" << std::endl;

        for (size_t i = 0; i < element_count; ++i)
            serial.push_back(i);
    }

    void TearDown() override
    {
        // serial.clear();
        std::cout << "TearDown" << std::endl;
    }
};

TEST_F(SerialFixture, Container_Initialization)
{
    serial_container<size_t> vect;
    ASSERT_FALSE(serial.empty());
}

TEST_F(SerialFixture, PushBack)
{
    serial.push_back(11);

    ASSERT_EQ(serial.size(), element_count + 1);
    ASSERT_EQ(serial[element_count], 11);
    ASSERT_FALSE(serial.empty());
}

TEST_F(SerialFixture, InsertFront)
{
    serial.insert(0, 225);

    ASSERT_EQ(serial.size(), element_count + 1);
    ASSERT_EQ(serial[0], 225);
}

TEST_F(SerialFixture, InsertMiddle)
{
    serial.insert(serial.size() / 2, 33);

    ASSERT_EQ(serial.size(), element_count + 1);
    ASSERT_EQ(serial[serial.size() / 2], 33);
}

TEST_F(SerialFixture, PopBack)
{
    ASSERT_EQ(serial[serial.size() - 1], 9);

    serial.erase(serial.size() - 1);

    ASSERT_NE(serial[serial.size() - 1], 9);
    ASSERT_EQ(serial.size(), element_count - 1);
}

TEST_F(SerialFixture, EraseFront)
{
    ASSERT_EQ(serial[0], 0);

    serial.erase(0);

    ASSERT_NE(serial[0], 0);
    ASSERT_EQ(serial.size(), element_count - 1);
}

TEST_F(SerialFixture, EraseMiddle)
{
    int middle = serial.size() / 2;
    ASSERT_EQ(serial[middle], 5);

    serial.erase(middle);

    ASSERT_NE(serial[middle], 5);
    ASSERT_EQ(serial.size(), element_count - 1);
}

TEST_F(SerialFixture, Get_element)
{
    for (int i = 0; i < serial.size(); ++i)
    {
        ASSERT_TRUE(serial[i] == i);
    }
}

TEST_F(SerialFixture, ContainerSize)
{
    int count = 10;

    ASSERT_EQ(serial.size(), count);
}