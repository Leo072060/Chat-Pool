#ifndef CHAT_POOL_H
#define CHAT_POOL_H

#include <string>

#include "message/message.h"

class ChatPool
{
  public:
    ChatPool(const std::string &dataBase_path,const std::string &command_ai);
    ~ChatPool();

    void storeMessage(const Message& message) const;
    std::vector<Message> readRecentMessages(const int index) const;
    void AI();

  private:
    std::string m_dataBase_path;
    std::string m_command_ai;
};

#endif //! CHAT_POOL_H