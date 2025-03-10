#ifndef MESSAGE_H
#define MESSAGE_H

#include <map>
#include <string>
#include <vector>

class Message
{
  public:
    void        insert(const std::string &key, const std::string &value);
    void        read(const std::string &str);
    bool        contain(const std::string &key) const;
    std::string get(const std::string &key) const;
    std::string to_str() const;
    void        print() const;

    static std::string assemble(const std::vector<Message> &messages);

  private:
    std::map<std::string, std::string> m_data;
};

#endif //! MESSAGE_H