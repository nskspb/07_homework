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

TEST_F(SerialFixture, PushBack)
{
    SetUp();

    serial.push_back(11);

    std::cout << "size = " << serial.size() << std::endl;
    std::cout << "size = " << element_count << std::endl;

    ASSERT_EQ(serial.size(), element_count + 1);
    ASSERT_FALSE(serial.empty());
}
