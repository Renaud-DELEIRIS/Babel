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




@enduml
