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

TEST(Serial, push_back)
{
    const size_t count = 10;
    serial_container<size_t> serial;

    for (size_t i = 0; i < count; ++i)
        serial.push_back(i);

    serial.push_back(12);
    ASSERT_EQ(serial.size(), count + 1);
    ASSERT_FALSE(serial.empty());
}

TEST_F(SerialFixture, Container_Initialization)
{
    serial_container<size_t> vect;
    ASSERT_EQ(vect.size(), 0);
}

TEST_F(SerialFixture, PushBack)
{
    serial.push_back(11);

    ASSERT_EQ(serial.size(), element_count + 1);
    ASSERT_FALSE(serial.empty());
}

TEST_F(SerialFixture, Erase)
{
    ASSERT_EQ(serial[5], 5);

    serial.erase(5);

    ASSERT_NE(serial[5], 5);
}

TEST_F(SerialFixture, PopBack)
{
    ASSERT_EQ(serial[element_count - 1], 9);

    serial.erase(serial.size());

    ASSERT_NE(serial[element_count - 1], 5);
}