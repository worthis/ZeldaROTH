#include <string>
#include "utf8.h"

namespace utf8utils
{
    std::size_t getLength(const std::string &s)
    {
        return utf8::unchecked::distance(s.begin(), s.end());
    }

    std::string getChar(const std::string &s, std::size_t pos)
    {
        auto it = s.begin();
        utf8::unchecked::advance(it, pos);
        auto end = it;

        if (end < s.end())
        {
            utf8::unchecked::next(end);
        }

        return std::string(it, end);
    }

    void eraseFrom(std::string &s, unsigned int from)
    {
        auto it = s.begin();
        utf8::unchecked::advance(it, from);
        s.erase(it, s.end());
    }

    void removeChar(std::string &s, unsigned int pos)
    {
        auto it = s.begin();
        utf8::unchecked::advance(it, pos);
        auto itNext = it;

        if (itNext < s.end())
        {
            utf8::unchecked::next(itNext);
        }

        s.erase(it, itNext);
    }

    void insert(std::string &s, unsigned int pos, const std::string c)
    {
        auto it = s.begin();
        utf8::unchecked::advance(it, pos);
        s.insert(it, c.begin(), c.end());
    }

    std::string subStr(const std::string &s, unsigned int from)
    {
        auto it = s.begin();
        utf8::unchecked::advance(it, from);
        return std::string(it, s.end());
    }
}