#pragma once

#include "IContainers.hpp"

template <typename T>
class Node1
{
public:
    Node1 *next;
    Node1 *prev;
    T data;

    Node1(T data = T(), Node1 *next = nullptr, Node1 *prev = nullptr)
    {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};

template <typename T>
class doubly_list_container : public IContainers<T>
{
public:
    doubly_list_container() : head{nullptr}, tail{nullptr}, c_size{} {}

    ~doubly_list_container()
    {
        clear();
    }

    void swap(const doubly_list_container &first, const doubly_list_container &second)
    {
        std::swap(first.c_size, second.c_size);
        std::swap(first.head, second.head);
        std::swap(first.tail, second.tail);
    }

    doubly_list_container(const doubly_list_container &other) : c_size{}, head{nullptr}, tail{nullptr}
    {
        for (int i = 0; i < other.c_size; ++i)
        {
            this->push_back(other[i]);
        }
    }

    doubly_list_container &operator=(const doubly_list_container &other)
    {
        doubly_list_container tmp{other};
        swap(*this, tmp);
        return *this;
    }

    doubly_list_container(const doubly_list_container &&other) noexcept
    {
        *this = std::move(other);
    }

    doubly_list_container &operator=(const doubly_list_container &&other) noexcept
    {
        swap(*this, other);
        other.c_size = 0;
        other.head = nullptr;
        other.tail = nullptr;
        return *this;
    }

    void push_back(const T &element) override
    {
        if (head == nullptr)
        {
            head = tail = new Node1<T>(element);
            head->next = tail;
            tail->next = nullptr;
            head->prev = nullptr;
        }
        else
        {
            Node1<T> *tmp = new Node1<T>(element);
            tail->next = tmp;
            tmp->prev = tail;
            tail = tmp;
        }
        c_size++;
    }

    void push_front(const T &element)
    {
        if (head == nullptr)
        {
            head = tail = new Node1<T>(element);
            head->next = tail;
            tail->next = nullptr;
            head->prev = nullptr;
        }
        else
        {
            Node1<T> *tmp = new Node1<T>(element);
            head->prev = tmp;
            tmp->next = head;
            head = tmp;
        }
        c_size++;
    }

    void pop_front()
    {
        Node1<T> *tmp = head;
        head = head->next;
        delete tmp;
        c_size--;
    }

    void pop_back()
    {
        Node1<T> *tmp = tail;
        tail = tail->prev;
        delete tmp;
        c_size--;
    }

    void insert(int position, const T &element) override
    {
        if (position == 0)
        {
            push_front(element);
        }
        else if (position == c_size)
        {
            push_back(element);
        }
        else if (c_size / 2 - position >= 0)
        {
            Node1<T> *previous = head;

            previous = find_pos(position - 1, previous);
            /*for (int i = 0; i < position - 1; ++i)
            {
                previous = previous->next;
            }*/

            Node1<T> *follow = new Node1<T>(element, previous->next, previous);
            previous->next = follow;
            c_size++;
        }
        else
        {
            Node1<T> *follow = tail;
            follow = find_pos(position, follow);
            /*for (int i = c_size - 1; i >= position; --i)
            {
                follow = follow->prev;
            }*/
            follow->next = new Node1<T>(element, follow->next, follow);
            follow->next->next->prev = follow->next;
            c_size++;
        }
    }

    void erase(int position) override
    {
        if (position == 0)
        {
            pop_front();
        }
        else if (position == c_size - 1)
        {
            pop_back();
        }
        else if (c_size / 2 - position >= 0)
        {
            Node1<T> *previous = head;
            previous = find_pos(position - 1, previous);
            /*for (int i = 0; i < position - 1; ++i)
            {
                previous = previous->next;
            }*/

            Node1<T> *follow = previous->next;
            previous->next = follow->next;
            delete follow;
            c_size--;
        }
        else
        {
            Node1<T> *follow = tail;
            follow = find_pos(position + 1, follow);
            /*for (int i = c_size - 1; i > position + 1; --i)
            {
                follow = follow->prev;
            }*/
            Node1<T> *previous = follow->prev;
            follow->prev = previous->prev;
            previous->prev->next = follow;
            delete previous;
            c_size--;
        }
    }

    T &operator[](int position) const override
    {
        if (c_size / 2 - position >= 0)
        {
            Node1<T> *tmp = head;
            tmp = find_pos(position, tmp);
            /*for (int i = 0; i < position; ++i)
            {
                tmp = tmp->next;
            }*/
            return tmp->data;
        }
        else
        {
            Node1<T> *tmp = tail;
            tmp = find_pos(position + 1, tmp);
            /*for (int i = c_size - 1; i >= position + 1; --i)
            {
                tmp = tmp->prev;
            }*/
            return tmp->data;
        }
    }

    void show() override
    {
        Node1<T> *tmp = head;
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
        return "doubly_list_container";
    }

    void clear()
    {
        while (c_size)
        {
            Node1<T> *tmp = head;

            head = head->next;

            delete tmp;
            c_size--;
        }
    }

private:
    mutable int c_size;
    mutable Node1<T> *head;
    mutable Node1<T> *tail;
    // Метод для нахождения нужного узла
    Node1<T> *find_pos(int position, Node1<T> *tmp) const
    {
        if (c_size / 2 - position >= 0)
        {
            for (int i = 0; i < position; ++i)
            {
                tmp = tmp->next;
            }
        }
        else
        {
            for (int i = c_size - 1; i >= position; --i)
            {
                tmp = tmp->prev;
            }
        }
        return tmp;
    }
};