#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "format/text_format.h"
#include "format/config_macros.h"

class Channel
{
public:
	Channel(std::string);
	~Channel();

	// METHODS

	// GETTERS
	std::string getName() const;

private:
	Channel();

	// ATTRIBUTES
	const std::string _name;

	// METHODS
};

#endif
