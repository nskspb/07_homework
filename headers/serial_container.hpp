#pragma once

#include "IContainers.hpp"

template <typename T>
class serial_container : public IContainers<T>
{
public:
    serial_container() : c_size{}, capacity{}, data{nullptr} {}

    ~serial_container()
    {
        delete[] data;
    }

    void swap(const serial_container &first, const serial_container &second)
    {
        std::swap(first.c_size, second.c_size);
        std::swap(first.data, second.data);
    }

    serial_container(const serial_container &other)
    {
        c_size = other.c_size;
        data = new T[c_size];
        for (int i = 0; i < c_size; ++i)
        {
            data[i] = other.data[i];
        }
    }

    serial_container &operator=(const serial_container &other)
    {
        serial_container tmp{other};
        swap(*this, tmp);
        return *this;
    }

    serial_container(const serial_container &&other) noexcept
    {
        *this = std::move(other);
    }

    serial_container &operator=(const serial_container &&other) noexcept
    {
        swap(*this, other);
        other.c_size = 0;
        other.data = nullptr;
        return *this;
    }

    void push_back(const T &element) override
    {
        if (c_size >= capacity)
        {
            change_capacity();
        }
        data[c_size++] = element;
    }

    void erase(int position) override
    {
        for (int i = position + 1; i < c_size; ++i)
        {
            data[i - 1] = data[i];
        }
        c_size--;
    }

    void insert(int position, const T &element) override
    {
        if (c_size >= capacity)
        {
            change_capacity();
        }
        c_size++;
        for (int i = c_size; i > position; --i)
        {
            data[i] = data[i - 1];
        }
        data[position] = element;
    }

    T &operator[](int position) const override
    {
        return data[position];
    }

    void show() override
    {
        for (int i = 0; i < c_size; i++)
        {
            std::cout << data[i] << " ";
        }

        std::cout << std::endl;
    }

    int size() const override
    {
        return c_size;
    }

    const char *name() const override
    {
        return "serial_container";
    }

private:
    mutable int c_size;
    int capacity;
    mutable T *data;

    void change_capacity()
    {
        if (capacity == 0)
        {
            capacity++;
        }
        else
        {
            capacity = (capacity * 3 + 1) / 2;
        }
        T *tmp = new T[capacity];
        for (int i = 0; i < c_size; ++i)
        {
            tmp[i] = data[i];
        }
        delete[] data;
        data = tmp;
    }
};
