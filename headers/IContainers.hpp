#pragma once

template <typename T>
class IContainers
{
public:
    virtual ~IContainers() {}

    virtual void push_back(const T &element) = 0;
    virtual void insert(int position, const T &element) = 0;
    virtual void erase(int position) = 0;
    virtual int size() const = 0;
    virtual T &operator[](int position) const = 0;
    virtual void show() = 0;
    virtual const char *name() const = 0;
};