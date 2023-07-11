#include <iostream>
#include "list_container.hpp"

#include <gtest/gtest.h>

struct ListFixture : public testing::Test
{
    const size_t element_count = 10;
    list_container<size_t> list;

    static void SetUpTestSuite()
    {
        std::cout << "SetUpTestSuite" << std ::endl;
    }

    static void TearDownTestSuite()
    {
        std::cout << "TearDownTestSuite" << std::endl;
    }

    void SetUp() override
    {
        std::cout << "SetUp" << std::endl;

        for (size_t i = 0; i < element_count; ++i)
        {
            list.push_back(i);
        }
    }

    void TearDown() override
    {
        // list.clear();
        std::cout << "TearDown" << std::endl;
    }
};

TEST_F(ListFixture, PushBack)
{
    list.push_back(15);

    ASSERT_EQ(list.size(), element_count + 1);
    ASSERT_FALSE(list.empty());
}

TEST_F(ListFixture, Clear)
{
    list.clear();

    ASSERT_TRUE(list.empty());
}

TEST_F(ListFixture, PushFront)
{
    list.push_front(25);
    list.show();
    ASSERT_EQ(list.size(), element_count + 1);
    ASSERT_EQ(list[0], 25);
    ASSERT_EQ(list[element_count], 9);
}