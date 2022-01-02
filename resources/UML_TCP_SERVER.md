@startuml





/' Objects '/

class TcpServer {
	+TcpServer(boost::asio::io_service &, short)
	-voiceServer : UdpServer*
	-ios : boost::asio::io_service&
	-mtx : std::mutex
	-allSessions : std::vector<std::shared_ptr<TcpSession>>
	-acceptor : tcp::acceptor
	+handle_accept(std::shared_ptr<TcpSession>, const boost::system::error_code &) : void
}


class TcpSession {
	+TcpSession(boost::asio::io_service &, UdpServer* copy, std::mutex* copyMtx)
	-database : Asqlite3
	-recvCommands : Commands
	-recv : Protocol*
	+decode(std::string) : S_Protocol
	-voiceServer : UdpServer*
	+get_user() : UserApp
	+get_user(std::string) : UserApp
	+get_user_by_address(std::string) : UserApp
	-recvUser : UserApp
	+accept(std::string, struct UserApp) : bool
	+add(std::string, struct UserApp) : bool
	+call(std::string, struct UserApp) : bool
	+check_linked(std::string, struct UserApp) : bool
	+check_user(std::string, struct UserApp) : bool
	+close_server(std::string, struct UserApp) : bool
	+get_contacts(std::string, struct UserApp) : bool
	+get_users_in_call(std::string, struct UserApp) : bool
	+hangup(std::string, struct UserApp) : bool
	+join(std::string, struct UserApp) : bool
	+login(std::string, struct UserApp) : bool
	+logout(std::string, struct UserApp) : bool
	+ping(std::string, struct UserApp) : bool
	+refuse(std::string, struct UserApp) : bool
	+remove(std::string, struct UserApp) : bool
	+send(const char*) : bool
	-users : std::map<int, UserApp>
	-users_index : std::map<std::string, UserApp>
	-mtx : std::mutex*
	+usersincall : std::string
	+allSessions : std::vector<std::shared_ptr<TcpSession>>
	-socket : tcp::socket
	+getSocket() : tcp::socket&
	-close_socket() : void
	+display(UserApp) : void
	+handleRead(std::shared_ptr<TcpSession> &, const boost::system::error_code &, std::size_t) : void
	+start() : void
}





/' Inheritance relationships '/




/' Aggregation relationships '/

.TcpServer *-- .TcpSession


.TcpSession *-- .TcpSession






/' Nested objects '/



@enduml
