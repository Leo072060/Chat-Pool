#include "transaction/chatPool/chatPool.h"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iostream>

ChatPool::ChatPool(const std::string &dataBase_path,const std::string &command_ai)
    : m_dataBase_path(dataBase_path),m_command_ai(command_ai)
{
    std::ofstream testFile(m_dataBase_path, std::ios::app);
    if (!testFile)
    {
        throw std::runtime_error("Failed to create or access database file: " + m_dataBase_path);
    }
    testFile.close();
}

ChatPool::~ChatPool() {}

void ChatPool::storeMessage(const Message &message) const
{
    std::ofstream file(m_dataBase_path, std::ios::app);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open database file: " + m_dataBase_path);
    }
    file << message.to_str() << "\n";
    if (file.fail())
    {
        throw std::runtime_error("Failed to write message to database file.");
    }
    file.close();
}

std::vector<Message> ChatPool::readRecentMessages(const int index) const
{
    std::vector<Message> messages;

    std::ifstream file(m_dataBase_path, std::ios::ate); 
    if (!file)
    {
        throw std::runtime_error("Failed to access database file: " + m_dataBase_path);
    }

    std::streampos fileSize = file.tellg();

    std::vector<std::string> lines;
    std::string              line;
    int                      linesRead = 0;

    for (std::streampos pos = fileSize - std::streampos(1); pos >= std::streampos(0); pos -= 1)
    {
        file.seekg(pos);
        char ch;
        file.get(ch);

        if (ch == '\n')
        {
            if (!line.empty())
            {
                std::reverse(line.begin(), line.end()); 
                lines.push_back(line);
                line.clear();
                linesRead++;

                if (linesRead >= index)
                {
                    break;
                }
            }
        }
        else
        {
            line += ch;
        }

        if (pos == 0 && !line.empty())
        {
            std::reverse(line.begin(), line.end());
            lines.push_back(line);
            linesRead++;
        }
    }

    file.close();

    std::reverse(lines.begin(), lines.end());

    for (const auto &line : lines)
    {
        Message message;
        message.read(line);
        messages.push_back(message);
    }

    return messages;
}

void ChatPool::AI()
{
    std::string command = m_command_ai;

    int result = std::system(command.c_str());

    if (result != 0) {
        std::cerr << "Failed to call AI script. Error code: " << result << std::endl;
    } else {
        std::cout << "AI script executed successfully." << std::endl;
    }
}