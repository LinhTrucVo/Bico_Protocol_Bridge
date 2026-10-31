#include "bpbHalFake.h"

#include <fstream>

namespace
{
    std::string s_basePath;
    nlohmann::json s_expected = nlohmann::json::array();
    nlohmann::json s_actual = nlohmann::json::array();
    const nlohmann::json s_noEntry = nlohmann::json::object();

    std::string CurrentTestName()
    {
        const ::testing::TestInfo *info = ::testing::UnitTest::GetInstance()->current_test_info();
        std::string name = std::string(info->test_suite_name()) + "_" + info->name();
        for (char &c : name)
        {
            if (c == '/')
            {
                c = '_';
            }
        }
        return name;
    }
}

namespace BpbHalFake
{
    void Load(const std::string &dataDir)
    {
        s_basePath = dataDir + "/" + CurrentTestName();
        s_actual = nlohmann::json::array();
        s_expected = nlohmann::json::array();

        std::ifstream in(s_basePath + ".json");
        if (in.is_open())
        {
            s_expected = nlohmann::json::parse(in).value("calls", nlohmann::json::array());
        }
    }

    const nlohmann::json &Call(const std::string &function, const nlohmann::json &args)
    {
        const size_t index = s_actual.size();
        const nlohmann::json &entry = (index < s_expected.size()) ? s_expected[index] : s_noEntry;

        nlohmann::json record = {{"function", function}, {"args", args}};
        if (entry.contains("return"))
        {
            record["return"] = entry["return"];
        }
        s_actual.push_back(record);
        return entry;
    }

    void Save()
    {
        std::ofstream out(s_basePath + "_actual.json");
        out << nlohmann::json{{"calls", s_actual}}.dump(2) << "\n";
    }

    ::testing::AssertionResult Verify()
    {
        if (s_actual.size() != s_expected.size())
        {
            return ::testing::AssertionFailure() << "HAL call count: expected " << s_expected.size()
                                                 << ", actual " << s_actual.size() << " (" << s_basePath << "_actual.json)";
        }
        for (size_t i = 0; i < s_actual.size(); ++i)
        {
            if ((s_actual[i]["function"] != s_expected[i].value("function", "")) ||
                (s_actual[i]["args"] != s_expected[i].value("args", nlohmann::json::object())))
            {
                return ::testing::AssertionFailure() << "HAL call " << i << ": expected " << s_expected[i].dump()
                                                     << ", actual " << s_actual[i].dump();
            }
        }
        return ::testing::AssertionSuccess();
    }
}
