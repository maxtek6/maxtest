#include <maxtest.hpp>

MAXTEST_MAIN
{
    MAXTEST_TEST_CASE(assert_condition)
    {
        MAXTEST_ASSERT(true);
        bool has_error(false);
        try
        {
            MAXTEST_ASSERT(false);
        }
        catch (const std::exception &e)
        {
            has_error = (e.what() != nullptr);
        }
        MAXTEST_ASSERT(has_error);
    };

    MAXTEST_TEST_CASE(parse_args)
    {
        const char * name_only[] = { "test" };
        const char * name_and_args[] = { "test", "arg1", "arg2" };
        auto parsed = parse_args(0, NULL);
        MAXTEST_ASSERT(parsed.first.empty());
        MAXTEST_ASSERT(parsed.second.empty());
        parsed = parse_args(sizeof(name_only) /sizeof(name_only[0]), name_only);
        MAXTEST_ASSERT(!parsed.first.empty());
        MAXTEST_ASSERT(parsed.second.empty());
        parsed = parse_args(sizeof(name_and_args) /sizeof(name_and_args[0]), name_and_args);
        MAXTEST_ASSERT(!parsed.first.empty());
        MAXTEST_ASSERT(!parsed.second.empty());
    };
}
