#include "Client.hpp"

Client::Client(void) {
	auth_ = false;
	sock_ = FT_INIT_CLIENT_FD;
	memset(&addr_, 0, sizeof(addr_));
	nick_ = "unknown_nick";
	user_ = "unknown_user";
}

/*
Client::Client(const Client& client) {
	*this = client;
}
*/

Client Client::operator = (const Client& client) {
	if (this == &client)
		return *this;

	auth_ = client.auth_;
	sock_ = client.sock_;
	nick_ = client.nick_;
	user_ = client.user_;
	addr_ = client.addr_;
	addr_size_ = client.addr_size_;
	password_ = client.password_;
	return *this;
}

int	Client::set_sock(int fd) {
	if (fd > 0)
		sock_ = fd;
	return sock_;
}

const int& Client::get_sock(void) {
	return sock_;
}

void Client::set_nick(const std::string& nick) {
	this->nick_ = nick;
}

const std::string& Client::get_nick(void) {
	return this->nick_;
}

bool Client::operator < (const Client& client) const {
	return (this->sock_ < client.sock_);
}

bool Client::operator > (const Client& client) const {
	return (this->sock_ > client.sock_);
}

bool Client::operator == (const Client& client) const {
	if ((this->nick_).compare(client.nick_) == 0)
		return true;
	return false;
}
