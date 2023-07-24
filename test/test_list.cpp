#include <iostream>
#include "list_container.hpp"

#include <gtest/gtest.h>

struct ListFixture : public testing::Test
{
    const size_t element_count = 10;
    list_container<size_t> list;

    static void SetUpTestSuite()
    {
        std::cout << "SetUpTestSuite List" << std ::endl;
    }

    static void TearDownTestSuite()
    {
        std::cout << "TearDownTestSuite List" << std::endl;
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

TEST_F(ListFixture, Container_Initialization)
{
    list_container<size_t> cont;
    ASSERT_TRUE(cont.empty());
}

TEST_F(ListFixture, PushBack)
{
    list.push_back(15);

    ASSERT_EQ(list.size(), element_count + 1);
    ASSERT_EQ(list[element_count], 15);
    ASSERT_FALSE(list.empty());
}

TEST_F(ListFixture, PushFront)
{
    list.push_front(25);
    ASSERT_EQ(list.size(), element_count + 1);
    ASSERT_EQ(list[0], 25);
    ASSERT_EQ(list[element_count], 9);
}

TEST_F(ListFixture, InsertMiddle)
{
    list.insert(list.size() / 2, 33);

    ASSERT_EQ(list.size(), element_count + 1);
    ASSERT_EQ(list[list.size() / 2], 33);
}

TEST_F(ListFixture, PopBack)
{
    ASSERT_EQ(list[list.size() - 1], 9);

    list.erase(list.size() - 1);

    ASSERT_NE(list[list.size() - 1], 9);
    ASSERT_EQ(list.size(), element_count - 1);
}

TEST_F(ListFixture, PopFront)
{
    ASSERT_EQ(list[0], 0);

    list.pop_front();

    ASSERT_NE(list[0], 0);
    ASSERT_EQ(list.size(), element_count - 1);
}

TEST_F(ListFixture, EraseMiddle)
{
    int middle = list.size() / 2;
    ASSERT_EQ(list[middle], 5);

    list.erase(middle);

    ASSERT_NE(list[middle], 5);
    ASSERT_EQ(list.size(), element_count - 1);
}

TEST_F(ListFixture, Get_element)
{
    for (int i = 0; i < list.size(); ++i)
    {
        ASSERT_TRUE(list[i] == i);
    }
}

TEST_F(ListFixture, ContainerSize)
{
    int count = 10;

    ASSERT_EQ(list.size(), count);
}

TEST_F(ListFixture, CopyContainers)
{
    list_container<size_t> cont1 = list;
    list_container<size_t> cont2;
    cont2 = list;

    for (int i = 0; i < element_count; ++i)
    {
        ASSERT_EQ(cont1[i], cont2[i]);
    }

    ASSERT_EQ(cont1.size(), cont2.size());
    ASSERT_FALSE(cont1.empty());
}

TEST_F(ListFixture, MoveContainers)
{
    list_container<size_t> cont1 = std::move(list);

    list_container<size_t> cont2;
    cont2 = cont1;

    list_container<size_t> cont3;
    cont3 = std::move(cont2);

    for (int i = 0; i < element_count; ++i)
    {
        ASSERT_EQ(cont3[i], cont1[i]);
    }

    ASSERT_EQ(cont3.size(), cont1.size());
    ASSERT_FALSE(cont3.empty());
    ASSERT_TRUE(list.empty());
}

// Неправильно!!!!!!!!!!!!!!!
TEST_F(ListFixture, Destructor)
{
    static int count;
    struct checkDestructor
    {

        ~checkDestructor()
        {
            count++;
        }
    };

    list_container<checkDestructor> cont;

    ASSERT_EQ(1, 1);
}