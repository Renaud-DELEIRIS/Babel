@startuml





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
