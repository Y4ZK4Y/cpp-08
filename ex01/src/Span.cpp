#include "Span.hpp"

#include <algorithm>
#include <limits>


Span::Span(unsigned int N): _cap(N), _numbers()
{
    _numbers.reserve(N); // avoid reallocs up to capacity
}

Span::Span(const Span& other): _cap(other._cap),
                                _numbers(other._numbers)
{

}

Span& Span::operator=(const Span& other)
{
    if (this != &other)
    {
        _cap = other._cap;
        _numbers = other._numbers;
    }
    return *this;
}

Span::~Span() = default;


// Exceptions

const char* Span::FullSpanException::what() const noexcept
{
    return "span is full.";
}

const char* Span::NoSpanException::what() const noexcept
{
    return "not enough numbers stored to compute a span.";
}

template <typename Input>
void Span::addNumber(Input first, Input last)
{
    std::size_t count = std::distance(first, last);

    if (_numbers.size() + count > _cap)
        throw FullSpanException();

    _numbers.insert(_numbers.end(), first, last);
}


void Span::addNumber(int value)
{
    if (_numbers.size() >= _cap)
        throw FullSpanException();
    _numbers.push_back(value);
}

int Span::shortestSpan() const
{
    if (_numbers.size() < 2)
        throw NoSpanException();
    // make a copy to work on
    std::vector<int> temp(_numbers);
    std::sort(temp.begin(), temp.end());

    int bestSpan = std::numeric_limits<int>::max();
    for (std::size_t i = 1; i < temp.size(); ++i)
    {
        const int diff = temp[i] - temp[i - 1];
        if (diff < bestSpan)
            bestSpan = diff;
        // cant do better than 0 eh
        if (bestSpan == 0)
            break;
    }
    return bestSpan;

}

int Span::longestSpan() const
{
    if (_numbers.size() < 2)
        throw NoSpanException();

    const std::pair<std::vector<int>::const_iterator,
            std::vector<int>::const_iterator> minmax =
            std::minmax_element(_numbers.begin(), _numbers.end());

    return *minmax.second - *minmax.first;
}

unsigned int Span::capacity() const
{
    return _cap;
}

std::size_t Span::size() const
{
    return _numbers.size();
}
