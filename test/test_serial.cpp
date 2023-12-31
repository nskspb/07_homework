#include <iostream>
#include "serial_container.hpp"

#include <gtest/gtest.h>

struct SerialFixture : public testing::Test
{
    const size_t element_count = 10;
    serial_container<size_t> serial;

    static void SetUpTestSuite()
    {
        std::cout << "SetUpTestSuite Serial" << std::endl;
    }

    static void TearDownTestSuite()
    {
        std::cout << "TearDownTestSuite Serial" << std::endl;
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
    ASSERT_TRUE(vect.empty());
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

TEST_F(SerialFixture, CopyContainers)
{
    serial_container<size_t> vect1 = serial;
    serial_container<size_t> vect2;
    vect2 = serial;

    for (int i = 0; i < element_count; ++i)
    {
        ASSERT_EQ(vect1[i], vect2[i]);
    }

    ASSERT_EQ(vect1.size(), vect2.size());
    ASSERT_FALSE(vect1.empty());
}

TEST_F(SerialFixture, Destructor)
{
    ASSERT_EQ(1, 1);
}

TEST_F(SerialFixture, MoveContainers)
{
    serial_container<size_t> vect1 = std::move(serial);

    serial_container<size_t> vect2;
    vect2 = vect1;

    serial_container<size_t> vect3;
    vect3 = std::move(vect2);

    for (int i = 0; i < element_count; ++i)
    {
        ASSERT_EQ(vect3[i], vect1[i]);
    }

    ASSERT_EQ(vect3.size(), vect1.size());
    ASSERT_FALSE(vect3.empty());
    ASSERT_TRUE(serial.empty());
}
