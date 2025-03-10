#include "message/message.h"

#include <iostream>
#include <sstream>

void Message::insert(const std::string &key, const std::string &value)
{
    m_data[key] = value;
}

void Message::read(const std::string &str)
{
    m_data.clear();

    size_t pos = 0;
    while (pos < str.size())
    {
        size_t keyStart = str.find('"', pos);
        if (keyStart == std::string::npos) break;
        size_t keyEnd = str.find('"', keyStart + 1);
        if (keyEnd == std::string::npos) break;
        std::string key = str.substr(keyStart + 1, keyEnd - keyStart - 1);

        size_t valueStart = str.find('"', keyEnd + 1);
        if (valueStart == std::string::npos) break;
        size_t valueEnd = str.find('"', valueStart + 1);
        if (valueEnd == std::string::npos) break;
        std::string value = str.substr(valueStart + 1, valueEnd - valueStart - 1);

        m_data[key] = value;

        pos = valueEnd + 1;
    }
}

bool Message::contain(const std::string &key) const
{
    return m_data.find(key) != m_data.end();
}

std::string Message::get(const std::string &key) const
{
    auto it = m_data.find(key);
    if (it != m_data.end())
    {
        return it->second;
    }
    return "";
}

std::string Message::to_str() const
{
    std::ostringstream oss;
    oss << "{";
    bool first = true;
    for (const auto &pair : m_data)
    {
        if (!first)
        {
            oss << ",";
        }
        oss << "\"" << pair.first << "\":\"" << pair.second << "\"";
        first = false;
    }
    oss << "}";
    return oss.str();
}

void Message::print() const
{
    std::cout << to_str() << std::endl;
}

std::string Message::assemble(const std::vector<Message> &messages)
{
    std::ostringstream oss;
    oss << "[";

    bool firstMessage = true;
    for (const auto &msg : messages)
    {
        if (!firstMessage)
        {
            oss << ",";
        }
        firstMessage = false;

        oss << "{";
        bool firstKey = true;
        for (const auto &[key, value] : msg.m_data)
        {
            if (!firstKey)
            {
                oss << ",";
            }
            firstKey = false;

            oss << "\"" << key << "\":\"" << value << "\"";
        }

        oss << "}";
    }

    oss << "]";
    return oss.str();
}