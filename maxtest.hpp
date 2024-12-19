/*
 * Copyright 2024 Maxtek Consulting
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef MAXTEST_HPP
#define MAXTEST_HPP

#include <functional>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#ifndef __FUNCTION_NAME__
#ifdef WIN32 // WINDOWS
#define __FUNCTION_NAME__ __FUNCTION__
#else //*NIX
#define __FUNCTION_NAME__ __func__
#endif
#endif

namespace maxtest
{
    using test_map = std::unordered_map<std::string, std::function<void(const std::vector<std::string> &)>>;

    void assert_condition(
        bool condition,
        const std::string &file,
        const std::string &function,
        int line,
        const std::string &description)
    {
        std::stringstream error_stream;
        if (!condition)
        {
            error_stream << file << ":" << function << ":" << line << ":"
                         << " assertion failed: \"" << description << "\"";
            throw std::runtime_error(error_stream.str());
        }
    }

    void declare_tests(test_map &tests);

    std::pair<std::string, std::vector<std::string>> parse_args(int argc, const char **argv)
    {
        std::string name;
        std::vector<std::string> args;
        if (argc > 1)
        {
            name = argv[1];
            for (int i = 2; i < argc; i++)
            {
                args.push_back(argv[i]);
            }
        }
        return std::make_pair(name, args);
    }

    void execute_tests(const test_map &tests, const std::string &name, const std::vector<std::string> &args)
    {
        auto test = tests.find(name);
        if (test != tests.end())
        {
            test->second(args);
        }
        else
        {
            throw std::runtime_error("maxtest: test case not found");
        }
    }
}

#define MAXTEST_ASSERT(COND) maxtest::assert_condition((COND), __FILE__, __FUNCTION_NAME__, __LINE__, #COND)

#define MAXTEST_MAIN                                                       \
    int main(int argc, const char **argv)                                  \
    {                                                                      \
        maxtest::test_map tests;                                           \
        int result(0);                                                     \
        if (argc > 1)                                                      \
        {                                                                  \
            maxtest::declare_tests(tests);                                 \
            auto args = maxtest::parse_args(argc, argv);                   \
            try                                                            \
            {                                                              \
                maxtest::execute_tests(tests, args.first, args.second);    \
            }                                                              \
            catch (std::exception & e)                                     \
            {                                                              \
                std::cerr << e.what() << std::endl;                        \
                result = 1;                                                \
            }                                                              \
        }                                                                  \
        else                                                               \
        {                                                                  \
            std::cerr << "maxtest: please specify test case" << std::endl; \
            result = 1;                                                    \
        }                                                                  \
        return result;                                                     \
    }                                                                      \
    void maxtest::declare_tests(maxtest::test_map &tests)

#define MAXTEST_TEST_CASE(NAME) \
    tests[#NAME] = [](const std::vector<std::string> &args)

#endif