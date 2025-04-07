#include "../../includes/Channel.hpp"

// Construtor
Channel::Channel() : mode(""), name(""), key(""), topic(""), password(""), usersLimit(0), usersCount(0) {}

// Destrutor
Channel::~Channel() {}

// Adiciona um cliente ao canal
void Channel::addClient(Client *client) {
	clients[client->getNickname()] = client;
	usersCount++;
}

// Verifica se um cliente é membro do canal
bool Channel::isMember(Client *client) {
	return clients.find(client->getNickname()) != clients.end();
}

// Remove um cliente do canal
void Channel::removeClient(Client *client) {
	clients.erase(client->getNickname());
	usersCount--;
}

// Verifica se o canal está vazio
bool Channel::isEmpty() {
	return clients.empty();
}

// Envia uma mensagem para todos os membros do canal
void Channel::sendMessage(const std::string &source, const std::string &command, const std::string &args) {
	for (_mapclient::iterator it = clients.begin(); it != clients.end(); ++it) {
		// Enviar mensagem para cada cliente
		it->second->receiveMessage(source, command, args);
	}
}

// Envia uma mensagem privada a um usuário específico
void Channel::privateMessage(const std::string &source, const std::string &command, const std::string &args) {
	if (clients.find(source) != clients.end()) {
		clients[source]->receiveMessage(source, command, args);
	}
}

// Verifica se um cliente está na lista de convidados
bool Channel::isInvited(Client *client) {
	return invited.find(client->getNickname()) != invited.end();
}

// Adiciona um cliente à lista de convidados
void Channel::addInvited(Client *client) {
	invited[client->getNickname()] = client;
}

// Remove um cliente da lista de convidados
void Channel::delInvited(Client *client) {
	invited.erase(client->getNickname());
}

// Adiciona um modo ao canal
std::string Channel::addMode(const std::string &newMode) {
	mode += newMode;
	return mode;
}

// Remove um modo do canal
std::string Channel::delMode(const std::string &removeMode) {
	mode.erase(mode.find(removeMode), removeMode.length());
	return mode;
}

// Obtém o prefixo de um cliente (se é operador ou usuário comum)
std::string Channel::getPrefix(Client *client) const {
	if (isOperator(client))
		return "@";
	return "";
}

// Obtém o símbolo do canal
std::string Channel::getSymbol() const {
	return "#";
}

// Verifica se um cliente é operador
bool Channel::isOperator(Client *client) const {
	for (size_t i = 0; i < operators.size(); i++) {
		if (operators[i] == client)
			return true;
	}
	return false;
}

// Adiciona um operador ao canal
bool Channel::addOperator(Client* client) {
	if (!isOperator(client)) {
		operators.push_back(client);
		return true;
	}
	return false;
}

// Remove um operador do canal
bool Channel::removeOperator(Client* client) {
	for (std::vector<Client*>::iterator it = operators.begin(); it != operators.end(); ++it) {
		if (*it == client) {
			operators.erase(it);
			return true;
		}
	}
	return false;
}

// Define a senha do canal
void Channel::setPassword(const std::string& newPassword) {
	password = newPassword;
}

// Obtém a senha do canal
const std::string& Channel::getPassword() const {
	return password;
}

// Remove a senha do canal
void Channel::removePassword() {
	password = "";
}

// Obtém o nome do canal
const std::string& Channel::getName(void) const {
	return name;
}

// Define o nome do canal
void Channel::setName(const std::string &src) {
	name = src;
}

// Obtém a lista de clientes no canal
const Channel::_mapclient& Channel::getClients(void) const {
	return clients;
}

// Define a lista de clientes
void Channel::setClients(_mapclient &src) {
	clients = src;
}

// Obtém a chave do canal
const std::string& Channel::getKey(void) const {
	return key;
}

// Define a chave do canal
void Channel::setKey(std::string &src) {
	key = src;
}

// Obtém o tópico do canal
const std::string& Channel::getTopic(void) const {
	return topic;
}

// Define o tópico do canal
void Channel::setTopic(const std::string &src) {
	topic = src;
}

// Define a lista de convidados
void Channel::setInvited(_mapclient &src) {
	invited = src;
}

// Obtém a lista de convidados
const Channel::_mapclient& Channel::getInvited(void) const {
	return invited;
}

// Obtém o modo do canal
const std::string Channel::getMode(void) const {
	return mode;
}

// Obtém o limite de usuários do canal
int Channel::getUserLimit() const {
	return usersLimit;
}

// Define o limite de usuários
void Channel::setUserLimit(int limit) {
	usersLimit = limit;
}

// Remove o limite de usuários
void Channel::removeUserLimit() {
	usersLimit = 0;
}

// Obtém o número de usuários no canal
int Channel::getUserCount() const {
	return usersCount;
}

// Define o número de usuários
void Channel::setUserCount(int count) {
	usersCount = count;
}

