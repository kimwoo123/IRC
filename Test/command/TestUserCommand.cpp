#include "TestUserCommand.hpp"

TestUserCommand::TestUserCommand(Server *s, Client *c): TestCommand(s, c) {
	std::cout << "====== USERCOMMAND ======\n";

	this->SetUp();
	this->RunTest();
	this->TearDown();
}

void	TestUserCommand::SetUp(void) {
	;
}

void	TestUserCommand::RunTest(void) {
	this->dummy_server_->AddClient(this->dummy_client_);
	
	this->token_list_.push_back("USER");
	UserCommand	com_no_param(this->token_list_, this->dummy_server_, this->dummy_client_);
	IsEqual("461 USER :Not enough parameters", com_no_param.RunAndReturnRespInTest());

	this->token_list_.push_back("white space");
	UserCommand	com_less_param(this->token_list_, this->dummy_server_, this->dummy_client_);
	IsEqual("461 USER :Not enough parameters", com_less_param.RunAndReturnRespInTest());

	this->token_list_.push_back("hostname");
	UserCommand	com_less_param2(this->token_list_, this->dummy_server_, this->dummy_client_);
	IsEqual("461 USER :Not enough parameters", com_less_param2.RunAndReturnRespInTest());

	this->token_list_.push_back("servername");
	UserCommand	com_less_param3(this->token_list_, this->dummy_server_, this->dummy_client_);
	IsEqual("461 USER :Not enough parameters", com_less_param3.RunAndReturnRespInTest());

	this->token_list_.push_back("real name");
	UserCommand	com_white_space(this->token_list_, this->dummy_server_, this->dummy_client_);
	IsEqual("400 :username must not has whitespace", \
			com_white_space.RunAndReturnRespInTest());

	this->dummy_server_->DeleteClient(this->dummy_client_->get_sock());
	this->token_list_.clear();
	this->dummy_client_->SetAuthFlag(FT_AUTH);
	this->token_list_.push_back("USER");
	this->token_list_.push_back("test");
	this->token_list_.push_back("test");
	this->token_list_.push_back("test");
	this->token_list_.push_back("test test test");
	this->dummy_server_->AddClient(this->dummy_client_);

	UserCommand	com(this->token_list_, this->dummy_server_, this->dummy_client_);
	IsEqual("462 USER :already registered", com.RunAndReturnRespInTest());
	this->dummy_server_->DeleteClient(this->dummy_client_->get_sock());

	this->dummy_client_->UnsetAuthFlagInTest();
	this->dummy_server_->AddClient(this->dummy_client_);
	UserCommand	com2(this->token_list_, this->dummy_server_, this->dummy_client_);
	IsEqual("", com2.RunAndReturnRespInTest());
	this->dummy_server_->DeleteClient(this->dummy_client_->get_sock());
}

void	TestUserCommand::TearDown(void) {
}
