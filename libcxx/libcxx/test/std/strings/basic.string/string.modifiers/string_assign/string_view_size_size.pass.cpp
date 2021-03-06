//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// XFAIL: libcpp-no-exceptions
// <string>

// basic_string<charT,traits,Allocator>&
//   assign(basic_string_view<charT,traits> sv, size_type pos, size_type n=npos);
// the =npos was added for C++14

#include <string>
#include <stdexcept>
#include <cassert>

#include "test_macros.h"
#include "min_allocator.h"

template <class S, class SV>
void
test(S s, SV sv, typename S::size_type pos, typename S::size_type n, S expected)
{
    try
    {
        s.assign(sv, pos, n);
        LIBCPP_ASSERT(s.__invariants());
        assert(pos <= sv.size());
        assert(s == expected);
    }
    catch (std::out_of_range&)
    {
        assert(pos > sv.size());
    }
}

template <class S, class SV>
void
test_npos(S s, SV sv, typename S::size_type pos, S expected)
{
    try
    {
        s.assign(sv, pos);
        LIBCPP_ASSERT(s.__invariants());
        assert(pos <= sv.size());
        assert(s == expected);
    }
    catch (std::out_of_range&)
    {
        assert(pos > sv.size());
    }
}

int main()
{
    {
    typedef std::string S;
    typedef std::string_view SV;
    test(S(), SV(), 0, 0, S());
    test(S(), SV(), 1, 0, S());
    test(S(), SV("12345"), 0, 3, S("123"));
    test(S(), SV("12345"), 1, 4, S("2345"));
    test(S(), SV("12345"), 3, 15, S("45"));
    test(S(), SV("12345"), 5, 15, S(""));
    test(S(), SV("12345"), 6, 15, S("not happening"));
    test(S(), SV("12345678901234567890"), 0, 0, S());
    test(S(), SV("12345678901234567890"), 1, 1, S("2"));
    test(S(), SV("12345678901234567890"), 2, 3, S("345"));
    test(S(), SV("12345678901234567890"), 12, 13, S("34567890"));
    test(S(), SV("12345678901234567890"), 21, 13, S("not happening"));

    test(S("12345"), SV(), 0, 0, S());
    test(S("12345"), SV("12345"), 2, 2, S("34"));
    test(S("12345"), SV("1234567890"), 0, 100, S("1234567890"));

    test(S("12345678901234567890"), SV(), 0, 0, S());
    test(S("12345678901234567890"), SV("12345"), 1, 3, S("234"));
    test(S("12345678901234567890"), SV("12345678901234567890"), 5, 10,
         S("6789012345"));
    }
#if TEST_STD_VER >= 11
    {
    typedef std::basic_string     <char, std::char_traits<char>, min_allocator<char>> S;
    typedef std::basic_string_view<char, std::char_traits<char> > SV;
    test(S(), SV(), 0, 0, S());
    test(S(), SV(), 1, 0, S());
    test(S(), SV("12345"), 0, 3, S("123"));
    test(S(), SV("12345"), 1, 4, S("2345"));
    test(S(), SV("12345"), 3, 15, S("45"));
    test(S(), SV("12345"), 5, 15, S(""));
    test(S(), SV("12345"), 6, 15, S("not happening"));
    test(S(), SV("12345678901234567890"), 0, 0, S());
    test(S(), SV("12345678901234567890"), 1, 1, S("2"));
    test(S(), SV("12345678901234567890"), 2, 3, S("345"));
    test(S(), SV("12345678901234567890"), 12, 13, S("34567890"));
    test(S(), SV("12345678901234567890"), 21, 13, S("not happening"));

    test(S("12345"), SV(), 0, 0, S());
    test(S("12345"), SV("12345"), 2, 2, S("34"));
    test(S("12345"), SV("1234567890"), 0, 100, S("1234567890"));

    test(S("12345678901234567890"), SV(), 0, 0, S());
    test(S("12345678901234567890"), SV("12345"), 1, 3, S("234"));
    test(S("12345678901234567890"), SV("12345678901234567890"), 5, 10,
         S("6789012345"));
    }
#endif
    {
    typedef std::string S;
    typedef std::string_view SV;
    test_npos(S(), SV(), 0, S());
    test_npos(S(), SV(), 1, S());
    test_npos(S(), SV("12345"), 0, S("12345"));
    test_npos(S(), SV("12345"), 1, S("2345"));
    test_npos(S(), SV("12345"), 3, S("45"));
    test_npos(S(), SV("12345"), 5, S(""));
    test_npos(S(), SV("12345"), 6, S("not happening"));
    }
}
