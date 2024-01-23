#include "Channel.hpp"

void	Channel::set_topic(const std::string& topic) {
	this->topic_ = topic;
}

void	Channel::set_password(const std::string& password) {
	this->password_ = password;
}

void	Channel::set_name(const std::string& name) {
	this->name_ = name;
}

bool	Channel::Kick(int sock) {
	std::set<int>::iterator	it = members_.find(sock);
	if (it != members_.end()) {
		members_.erase(it);
		return true;
	}
	return false;
}

void	Channel::Join(int sock) {
	members_.insert(sock);
}

void	Channel::PromoteMember(int sock) {
	operators_.insert(sock);
}

void	Channel::DegradeMember(int sock) {
	operators_.erase(sock);
}

bool	Channel::AuthPassword(const std::string& password) {
	if (password.compare(password_) == 0)
		return true;
	return false;
}

bool	Channel::IsMember(int sock) {
	std::set<int>::iterator	it = members_.find(sock);
	if (it != members_.end())
		return true;
	return false;
}

bool	Channel::IsOperator(int sock) {
	std::set<int>::iterator	it = operators_.find(sock);
	if (it != operators_.end())
		return true;
	return false;
}

/* return true when the mode has changed */
bool	Channel::set_mode(const int& flag, const bool& enable) {
	if ((mode_ & flag) && !enable) {
		mode_ &= !flag;
		return true;
	} else if (!(mode_ & flag) && enable) {
		mode_ |= flag;
		return true;
	}
	return false;
}

const char&	Channel::get_mode(void) {
	return mode_;
}

void	Channel::set_limit(const int& l) {
	this->limit_ = l;
}

void	Channel::unset_limit(void) {
	this->limit_ = CLIENT_LIMIT;
}

const std::set<int>&	Channel::get_members(void) {
	return members_;
};

const std::set<int>&	Channel::get_operators(void) {
	return operators_;
};

const std::set<int>&	Channel::get_ban_list(void) {
	return ban_list_;
};

size_t	Channel::get_size(void) {
	return this->members_.size();
}
