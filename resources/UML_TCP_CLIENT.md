@startuml





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



@enduml
