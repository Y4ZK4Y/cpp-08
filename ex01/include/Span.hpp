#pragma once

#include <exception>
#include <vector>
#include <cstddef>

class Span {

private:
    unsigned int        _cap;
    std::vector<int>    _numbers;

public:
    explicit Span(unsigned int N);
    Span(const Span& other);
    Span& operator=(const Span& other);
    ~Span();

    // Exceptions
    class FullSpanException : public std::exception {
    public:
        const char* what() const noexcept override;
    };

    class NoSpanException : public std::exception {
    public:
        const char* what() const noexcept override;
    };

    void            addNumber(int value);

    // add multiple numbers using an iterator range
    template <typename Input>
    void            addNumber(Input first, Input last);

    int             shortestSpan() const;
    int             longestSpan() const;

    // herlpers
    unsigned int    capacity() const;
    std::size_t     size() const;

};
