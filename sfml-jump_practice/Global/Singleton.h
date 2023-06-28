#pragma once

template <typename T>
class Singleton
{
public:
    static T& Instance()
    {
        static T instance;
        return instance;
    }

    // 매개변수로 넘길때 생기는거 방지
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton() = default;
    virtual ~Singleton() = default;
};