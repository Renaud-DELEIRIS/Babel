@startuml





/' Objects '/

class Asqlite3 {
	+Asqlite3()
	+~Asqlite3()
	+checkUser(std::string username) : bool
	-{static} executeQuery(std::string sql, int (* ) ( void*, int, char**, char** ) callback, void* context) : bool
	+linkUser(std::string userfrom, std::string userto) : bool
	+unlinkUser(std::string userfrom, std::string userto) : bool
	+uploadData(struct UserApp user) : bool
	-{static} callbackFillContact(void*, int argc, char** argv, char** azColName) : int
	-{static} callbackGetUser(void*, int argc, char** argv, char** azColName) : int
	-{static} callbackUserExist(void*, int argc, char** argv, char** azColName) : int
	+login(struct UserApp user) : int
	-_res : std::string
	+getIdByUsername(std::string username) : std::string
	+getUser(std::string username) : std::string
	-_linkedUser : std::vector<struct UserApp>
	+getLinkedUser(std::string username) : std::vector<struct UserApp>
}


enum Asqlite3::loginCode {
	BAD_PASSWORD
	SUCCESS
	USER_NOT_EXIST
}





/' Inheritance relationships '/




/' Aggregation relationships '/





/' Nested objects '/

.Asqlite3 +-- .Asqlite3::loginCode




/' Objects '/

class TCP {
	+TCP(App* appcopy)
	+~TCP()
	-copy : App*
	-_connected : bool
	+isConnected() : bool
	-io_context : boost::asio::io_context
	-strand : boost::asio::io_service::strand
	-socket : boost::asio::ip::tcp::socket*
	+sendCommand(std::string command) : std::string
	+async_read() : void
	+doConnect() : void
	+read(const boost::system::error_code& error, size_t bytes_recvd) : void
}





/' Inheritance relationships '/




/' Aggregation relationships '/





/' Nested objects '/

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

/' Objects '/

class Group {
	+Group()
	+Group(shared_session session)
	+Group(std::vector<shared_session> sessions)
	+~Group()
	+addSession(const std::string address, int id, std::vector<shared_session> allSessions) : int
	+sessions : std::vector<shared_session>
	+addSession(const shared_session& session) : void
	+addSession(const std::vector<shared_session> sessions) : void
}


class UdpServer {
	+UdpServer(boost::asio::io_service& io_service)
	+removeFromGroup(int groupId, shared_session sessionToRemove) : bool
	-strand : boost::asio::io_service::strand
	-UdpSession : friend struct
	+addToGroup(int groupId, shared_session sessionToAdd) : int
	+createGroup(shared_session session) : int
	-id : int
	+join(std::string addressPort, int id) : int
	+join(std::string addressPort, int id, int idUser) : int
	+getAllGroups() : std::map<int , Group>
	-groups : std::map<int, Group>
	-allSessions : std::vector<shared_session>
	-get_related(const shared_session session) : std::vector<shared_session> {query}
	-socket : udp::socket
	-handle_receive(const shared_session session, const boost::system::error_code& ec, std::size_t) : void
	-receive_session() : void
}


class UdpSession {
	+UdpSession(UdpServer* server)
	+Server : UdpServer*
	+operator==(const UdpSession& other) : bool {query}
	+recvBuffer : boost::array<unsigned char, 120>
	+id : int
	+message : std::string
	+remoteEndpoint : udp::endpoint
	+handle_sent(const boost::system::error_code& ec, std::size_t) : void
}





/' Inheritance relationships '/




/' Aggregation relationships '/

.UdpServer *-- .Group


.UdpSession o-- .UdpServer






/' Nested objects '/

@enduml
