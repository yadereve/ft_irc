#include "../../../includes/Client.hpp"

void Client::quit(std::ostringstream &oss)
{
    oss << CYAN << "├─ " << CYAN BOLT << "QUIT [<reason>]" << std::endl;
    oss << CYAN << "│"   << WHITE << "\tLeave the server" << std::endl;
}

int Client::quit()
{
    std::string reason;
    if (_arguments.size() < 1)
        reason = "";
    else
	{
		reason = _arguments[0];
		reason.insert(0, ":");
	}

    // TODO - send message to the channels with the (string) reason (CHANNEL)
    const std::vector<Channel>& channels = _server.getChannelList();
    for (size_t i = 0; i < channels.size(); ++i) {
        Channel* ch = const_cast<Channel*>(&channels[i]);
        if (ch->isMember(this)) {
			
			std::string quitMessage = ":" + this->getNickname() + "!" + _user + "@" + _hostname + " QUIT :" + reason + "\r\n";
            ch->broadcast(quitMessage);  // Envia a mensagem para o canal
            ch->removeClient(this);
			Client* remainingClient = ch->getOnlyClient();
			if (remainingClient  && !ch->isOperator(remainingClient))
				ch->addOperator(remainingClient);
        }
    }

    // print quit message to user (CLIENT)
	messageClient(":" + _nick + "!" + _user + " QUIT " + reason + "\r\n");


    // TODO - remove client form server (SERVER)
	DEBUG("_socket: " << _socket);
	_server.handleQuit(_socket);

    return 0;
}
