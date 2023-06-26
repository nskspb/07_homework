#pragma once

#include "IContainers.hpp"

template <typename T>
class Node
{
public:
    Node *next;
    T data;

    Node(T data = T(), Node *next = nullptr)
    {
        this->data = data;
        this->next = next;
    }
};

template <typename T>
class list_container : public IContainers<T>
{
public:
    list_container() : head{nullptr}, c_size{} {}

    ~list_container()
    {
        clear();
    }

    void swap(const list_container &first, const list_container &second)
    {
        std::swap(first.c_size, second.c_size);
        std::swap(first.head, second.head);
    }

    list_container(const list_container &other) : c_size{}, head{nullptr}
    {
        for (int i = 0; i < other.c_size; ++i)
        {
            this->push_back(other[i]);
        }
    }

    list_container &operator=(const list_container &other)
    {
        list_container tmp{other};
        swap(*this, tmp);
        return *this;
    }

    list_container(const list_container &&other) noexcept
    {
        *this = std::move(other);
    }

    list_container &operator=(const list_container &&other) noexcept
    {
        swap(*this, other);

        other.c_size = 0;
        other.head = nullptr;
        return *this;
    }

    void push_back(const T &element) override
    {
        if (head == nullptr)
        {
            head = new Node<T>(element);
        }
        else
        {
            Node<T> *tmp = head;

            tmp = find_pos(c_size - 1, tmp);

            /*for (int i = 0; i < c_size - 1; ++i)
            {
                tmp = tmp->next;
            }*/

            tmp->next = new Node<T>(element);
        }

        c_size++;
    }

    void push_front(const T &element)
    {
        head = new Node<T>(element, head);
        c_size++;
    }

    void pop_front()
    {
        Node<T> *tmp = head;
        head = head->next;
        delete tmp;
        c_size--;
    }

    void insert(int position, const T &element) override
    {
        if (position == 0)
        {
            push_front(element);
        }
        else
        {
            Node<T> *previous = head;

            /*for (int i = 0; i < position - 1; ++i)
            {
                previous = previous->next;
            }*/

            previous = find_pos(position - 1, previous);

            Node<T> *follow = new Node<T>(element, previous->next);
            previous->next = follow;
            c_size++;
        }
    }

    void erase(int position) override
    {
        if (position == 0)
        {
            pop_front();
        }
        else
        {
            Node<T> *previous = head;

            /*for (int i = 0; i < position - 1; ++i)
            {
                previous = previous->next;
            }*/

            previous = find_pos(position - 1, previous);

            Node<T> *follow = previous->next;
            previous->next = follow->next;
            delete follow;
            c_size--;
        }
    }

    T &operator[](int position) const override
    {
        Node<T> *tmp = head;

        for (int i = 0; i < position; ++i)
        {
            tmp = tmp->next;
        }
        return tmp->data;
    }

    void show() override
    {
        Node<T> *tmp = head;
        for (int i = 0; i < c_size; ++i)
        {
            std::cout << tmp->data << " ";
            tmp = tmp->next;
        }
        std::cout << std::endl;
    }

    int size() const override
    {
        return c_size;
    }

    const char *name() const override
    {
        return "list_container";
    }

    void clear()
    {
        while (c_size)
        {
            Node<T> *tmp = head;

            head = head->next;

            delete tmp;
            c_size--;
        }
    }

private:
    mutable int c_size;
    mutable Node<T> *head;
    // Метод для нахождения нужного узла
    Node<T> *find_pos(int position, Node<T> *tmp)
    {
        for (int i = 0; i < position; ++i)
        {
            tmp = tmp->next;
        }
        return tmp;
    }
};