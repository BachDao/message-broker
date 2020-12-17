#pragma once
#include <string>
#include <memory>
#include <vector>

namespace MessageBroker{
  class Connection;
  class Channel{
    std::string name_;
    std::vector<std::weak_ptr<Connection>> connections_;
  public:
    std::string Name() const;
    bool AddConnection(std::weak_ptr<Connection> ptrConnection);
  };
}