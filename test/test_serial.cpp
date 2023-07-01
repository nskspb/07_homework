#include <iostream>
#include "serial_container.hpp"

#include <gtest/gtest.h>

TEST(Serial, PushBack)
{
    const size_t count = 10;
    serial_container<size_t> serial;

    for (size_t i = 0; i < count; ++i)
    {
        serial.push_back(i);
    }

    ASSERT_EQ(serial.size(), count);
    ASSERT_FALSE(serial.empty());
}
