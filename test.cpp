#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <math.h>
#include <string>
#include <sstream>

namespace List_Container_example
{
    template <typename T>
    class Node
    {
    public:
        Node *pNext;
        T data;

        Node(T data = T(), Node *pNext = nullptr)
        {
            this->data = data;
            this->pNext = pNext;
        }
    };

    template <typename T>
    class List
    {
    public:
        List();
        ~List();

        void push_back(const T &element);
        void push_front(const T &element);
        void erase(int position);
        void insert(int position, const T &element);
        int get_size() const;
        T &operator[](int position);
        void show();
        void pop_front();
        void pop_back();

        void clear();

    private:
        Node<T> *head;
        int size;
    };

    template <typename T>
    List<T>::List()
    {
        size = 0;
        head = nullptr;
    }

    template <typename T>
    List<T>::~List()
    {
        clear();
        std::cout << "ctor  " << std::endl;
    }

    template <typename T>
    void List<T>::push_back(const T &element)
    {
        if (head == nullptr)
        {
            head = new Node<T>(element);
        }
        else
        {
            Node<T> *tmp = head;

            while (tmp->pNext != nullptr)
            {
                tmp = tmp->pNext;
            }
            tmp->pNext = new Node<T>(element);
        }

        size++;
    }

    template <typename T>
    void List<T>::push_front(const T &element)
    {
        head = new Node<T>(element, head);
        size++;
    }

    template <typename T>
    void List<T>::erase(int position)
    {
        if (position == 0)
        {
            pop_front();
        }
        else
        {
            Node<T> *prev = head;

            for (int i = 0; i < position - 1; ++i)
            {
                prev = prev->pNext;
            }

            Node<T> *follow = prev->pNext;
            prev->pNext = follow->pNext;
            delete follow;
            size--;
        }
    }

    template <typename T>
    void List<T>::insert(int position, const T &element)
    {
        if (position == 0)
        {
            push_front(element);
        }
        else
        {
            Node<T> *prev = head;

            for (int i = 0; i < position - 1; ++i)
            {
                prev = prev->pNext;
            }

            Node<T> *follow = new Node<T>(element, prev->pNext);
            prev->pNext = follow;
        }
        size++;
    }

    template <typename T>
    int List<T>::get_size() const
    {
        std ::cout << "size = " << size << std::endl;
        return size;
    }

    template <typename T>
    T &List<T>::operator[](int position)
    {
        int count = 0;
        Node<T> *tmp = head;

        while (tmp != nullptr)
        {
            if (count == position)
            {
                return tmp->data;
            }
            tmp = tmp->pNext;
            count++;
        }
    }

    template <typename T>
    void List<T>::show()
    {
        Node<T> *tmp = head;
        for (int i = 0; i < size; ++i)
        {
            std::cout << tmp->data << " ";
            tmp = tmp->pNext;
        }
        std::cout << std::endl;
    }

    template <typename T>
    void List<T>::pop_front()
    {
        Node<T> *tmp = head;

        head = head->pNext;

        delete tmp;
        size--;
    }

    template <typename T>
    void List<T>::pop_back()
    {
        erase(size - 1);
    }

    template <typename T>
    void List<T>::clear()
    {
        while (size)
        {
            Node<T> *tmp = head;

            head = head->pNext;

            delete tmp;
            size--;
        }
    }

    void example()
    {
        std::cout << "-----------------List_Container example-------------------------" << std ::endl;
        List<int> listok;
        listok.push_back(5);
        listok.push_back(10);
        listok.push_back(15);
        listok.push_back(20);
        listok.push_back(25);

        listok.get_size();

        std::cout << listok[2] << std::endl;
        listok.show();

        listok.push_front(30);

        listok.pop_front();
        listok.show();

        listok.insert(4, 22);
        listok.show();

        listok.erase(5);
        listok.show();

        listok.pop_back();
        listok.show();
    }
}

namespace My_Container_Array
{
    template <typename T, size_t N>
    class Array_Container_fixed_size
    {
    public:
        Array_Container_fixed_size() : last{0} {}

        bool push_back(const T &v)
        {
            if (last >= N)
            {
                return false;
            }

            data[last] = v;
            last++;
            return true;
        }

        bool get(const size_t pos, T &out) const
        {
            if (pos >= last)
            {
                return false;
            }
            out = data[pos];
            return true;
        }

        bool erase(const size_t pos)
        {
            if (pos >= last)
            {
                return false;
            }
            for (size_t i = pos; i < last; ++i)
            {
                data[i] = data[i + 1];
            }
            last--;
            return true;
        }

        size_t count() const
        {
            return last;
        }

    private:
        T data[N];
        size_t last;
    };

    template <typename T, size_t N>
    void Container_vyvod(const Array_Container_fixed_size<T, N> &container)
    {

        for (size_t i = 0; i < container.count(); ++i)
        {
            T value;
            container.get(i, value);

            std ::cout << value << "  ";
        }
    }

    void container_test()
    {
        Array_Container_fixed_size<double, 10> container;

        container.push_back(1.5);
        container.push_back(2.3);
        container.push_back(5.7);
        container.push_back(6.8);
        container.push_back(8.5);
        container.push_back(9.5);

        Container_vyvod(container);
        std ::cout << std ::endl;

        container.erase(2);
        container.erase(3);

        Container_vyvod(container);
        std ::cout << std ::endl;
    }
}

namespace sort_vectors
{

    void example()
    {

        std ::vector<double> vect;

        vect.push_back(10);
        vect.push_back(9);
        vect.push_back(8);
        vect.push_back(7);
        vect.push_back(6);
        vect.push_back(5);
        vect.push_back(4);
        vect.push_back(3);
        vect.push_back(2);
        vect.push_back(1);

        for (int i = 0; i < vect.size(); ++i)
        {
            std ::cout << vect[i] << "  ";
        }

        std ::cout << std ::endl;

        /*std::sort(vect.begin(), vect.end(),
                  [](const double a, const double b)
                  {
                      return a < b;
                  });*/

        size_t num = 3;

        std ::cout << "num = " << num << std ::endl;
        std ::nth_element(vect.begin(), vect.begin() + num, vect.end(),
                          [](const double a, const double b)
                          {
                              return a < b;
                          });

        for (int i = 0; i < vect.size(); ++i)
        {
            std ::cout << vect[i] << "  ";
        }

        std ::cout << std ::endl;
    }
}
namespace vectors
{

    void example()
    {

        std ::vector<std ::string> ivector = {"hi", ", i'm ", "Ruslan"};

        std ::vector<std ::string> ivector2 = {"hi", ", i'm ", "Ruslan"};

        std ::cout << "razmer = " << ivector.size() << std ::endl;
        ivector.resize(3);
        ivector.push_back(" Albertovich");

        ivector.push_back(ivector.back());
        std ::cout << "razmer = " << ivector.size() << std ::endl;
        std ::vector<std ::vector<int>> vec;
        // vec.resize(10);  // десять векторов
        vec.push_back(std ::vector<int>());

        // ivector.push_back(ivector2);

        for (int i = 0; i < ivector.size(); ++i)
        {
            std ::cout << ivector[i];
        }

        // ivector.pop_back();

        ivector2.insert(ivector2.end(), " Albertovich");
        ivector2.push_back(" Albertovich");
        if (ivector2 == ivector)
        {
            std ::cout << ivector.at(1);
        }

        std ::cout << std ::endl;

        double a = 5.66556456;

        float b;
        b = static_cast<float>(a);
        std ::cout << b << std ::endl;
    }

}

namespace ssylka
{
    void Foo1(int a)
    {
        a = 1;
    }

    void Foo2(int &a)
    {
        a = 2;
    }

    void Foo3(int *a)
    {
        *a = 3;
    }

    void example()
    {
        /**/ int p = 5;
        int &r = p;
        r++;
        std ::cout << "p = " << p << std ::endl;

        Foo1(p);
        std ::cout << "value1 = " << p << std ::endl;

        Foo2(p);
        std ::cout << "value1 = " << p << std ::endl;

        Foo3(&p);
        std ::cout << "value1 = " << p << std ::endl;
    }
}

namespace chrono_
{

    void example()
    {
        auto startTime = std::chrono::system_clock::now(); // текущее время
        for (int i = 0; i < 100; ++i)
        {
            vectors::example();
        }                                                // запуск алгоритма
        auto endTime = std::chrono::system_clock::now(); // текущее время
        auto milliseconds = std::chrono::duration_cast<
            std::chrono::milliseconds>(
            endTime - startTime); // получаем значение разницы в миллисекундах

        std ::cout << "Vremya =  " << milliseconds.count() << std ::endl;
    }

}

namespace stringstream_stream
{

    void example()
    {
        std::stringstream ss;
        ss << "22";
        int k = 0;
        ss >> k;
        std::cout << k << std::endl;
    }
}

namespace acm_timus
{
    void example()
    {
        int n, k;
        std ::cout << "vvod: ";
        std::cin >> n >> k;
        int del;
        if (n < k)
        {
            del = 1;
        }
        else
        {
            del = n / k;
        }

        std ::cout << 2 * del << std::endl;
    }
}

namespace acm_timus_2
{

    void example()
    {
        int a, b;

        std::cin >> a >> b;
        std ::cout << a + b;
    }

}

namespace l_r_value
{
    int globalvar = 20;

    int &foo()
    {
        return globalvar;
        std::cout << "fdfdsfdsf" << globalvar;
    }
    void example()
    {
        foo() = 10;
        foo();
        std::cout << "looool" << std::endl;
    }
}

int main()
{
    My_Container_Array ::container_test();

    // std ::string s = "hello";
    vectors::example();

    // chrono_::example();

    // int k = std ::string::npos;
    // ssylka::example();
    std::cout << std::numeric_limits<double>::max() << std ::endl;
    std::cout << std::numeric_limits<double>::min() << std ::endl;
    std::cout << std::numeric_limits<double>::lowest() << std ::endl;

    sort_vectors ::example();

    stringstream_stream ::example();

    List_Container_example ::example();

    // acm_timus_2 ::example();

    l_r_value::example();
    return 0;
}