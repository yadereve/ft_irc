#include "../../includes/Channel.hpp"

Channel::Channel()
{
}

Channel::Channel(std::string name) : _name(name)
{
}

Channel::~Channel()
{
}

/* getters */
std::string Channel::getName() const { return _name; }