#ifndef CHAT_POOL_H
#define CHAT_POOL_H

#include <string>

#include "message/message.h"

class ChatPool
{
  public:
    ChatPool(const std::string &dataBase_path);
    ~ChatPool();

    void storeMessage(const Message& message) const;
    std::vector<Message> readRecentMessages(const int index) const;

  private:
    std::string m_dataBase_path;
};

#endif //! CHAT_POOL_H