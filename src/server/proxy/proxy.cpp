/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** proxy.cpp
*/

#include <iostream>

class Subject
{
    public:
        virtual void Request() const = 0;
};

class RealSubject : public Subject
{
    public:
        void Request() const override {
            std::cout << "RealSubject: Handling request.\n";
        }
};

class Proxy : public Subject
{
    private:
        RealSubject *real_subject_;

        bool CheckAccess() const {
            // Some real checks should go here.
            std::cout << "Proxy: Checking access prior to firing a real request.\n";
            return true;
        }
        void LogAccess() const {
            std::cout << "Proxy: Logging the time of request.\n";
        }

    public:
    Proxy(RealSubject *real_subject) : real_subject_(new RealSubject(*real_subject))
    {
    }

    ~Proxy()
    {
        delete real_subject_;
    }

    void Request() const override
    {
        if (this->CheckAccess()) {
            this->real_subject_->Request();
            this->LogAccess();
        }
    }
};

void ClientCode(const Subject &subject)
{
    subject.Request();
}

int proxy_build(void)
{
    std::cout << "Client: Executing the client code with a real subject:\n";
    RealSubject *real_subject = new RealSubject;
    ClientCode(*real_subject);
    std::cout << "\n";
    std::cout << "Client: Executing the same client code with a proxy:\n";
    Proxy *proxy = new Proxy(real_subject);
    ClientCode(*proxy);

    delete real_subject;
    delete proxy;
    return 0;
}