/*
 * Simple test framework with no dependencies.
 * Copyright (c) 2012, Mario 'rlyeh' Rodriguez

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.

 * @todo:
 * - Mockups
 * - Suites and chain tests.

 * - rlyeh
 */

#pragma once

#include <sstream>
#include <string>

namespace tests
{
    extern std::string &errors();
    extern size_t passed, failed, executed;

    extern void (*warning_cb)( const std::string &message );
    extern void (* report_cb)( const std::string &report  );
}

#   define test3(A,op,B) do { \
        std::string &errors = tests::errors(); \
        auto __a__ = (A); auto __b__ = (B); \
        if( __a__ op __b__ ) { \
            tests::executed++; \
            tests::passed++; \
        } else { \
            tests::executed++; \
            tests::failed++; \
            std::stringstream ss; \
            ss  << "Test #" << tests::executed << " failed at " << __FILE__ << ':' << __LINE__ << std::endl \
                << #A << " (" << __a__ << ") " << #op << ' ' << #B << " (" << __b__ << ") "; \
            if( tests::warning_cb ) (*tests::warning_cb)( ss.str() ); \
            errors += ss.str() + '\n'; \
    } } while(0)

#   define test1(A) do { \
        std::string &errors = tests::errors(); \
        auto __a__ = (A); decltype(__a__) __b__ = 0; \
        if( __a__ != __b__ ) { \
            tests::executed++; \
            tests::passed++; \
        } else { \
            tests::executed++; \
            tests::failed++; \
            std::stringstream ss; \
            ss  << "Test #" << tests::executed << " failed at " << __FILE__ << ':' << __LINE__ << std::endl \
                << #A << " (" << __a__ << ") not true "; \
            if( tests::warning_cb ) (*tests::warning_cb)( ss.str() ); \
            errors += ss.str() + '\n'; \
    } } while(0)
