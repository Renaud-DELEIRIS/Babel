/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Asqlite3
*/

#include "server/Asqlite3.hpp"
#include <iostream>

Asqlite3::Asqlite3()
{
	std::string sql = "CREATE TABLE IF NOT EXISTS user("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"pseudo TEXT NOT NULL UNIQUE, "
		"password TEXT NOT NULL, "
		"address	TEXT NOT NULL);"
		"CREATE TABLE IF NOT EXISTS contact("
		"idfrom INTEGER, "
		"idto INTEGER, "
		"FOREIGN KEY(idfrom) REFERENCES user(id), "
		"FOREIGN KEY(idto) REFERENCES user(id));";
	if (!executeQuery(sql, NULL, 0))
		std::cerr << "Error in createTable function." << std::endl;
}

Asqlite3::~Asqlite3()
{
}

bool Asqlite3::uploadData(UserApp user)
{
	std::string sql("INSERT INTO user (pseudo, password, address)"
	"VALUES('" + user.username + "', '" + user.password + "', '" + user.address + "');");
	if (!executeQuery(sql, NULL, 0)) {
		return false;
	}
	return true;
}

int Asqlite3::callbackUserExist(void *context, int argc, char** argv, char** azColName)
{
	Asqlite3 *db = static_cast<Asqlite3 *>(context);
	for (int i = 0; i < argc; i++) {
		db->_res = argv[i];
	}
	return 0;
}

int Asqlite3::callbackGetUser(void *context, int argc, char** argv, char** azColName)
{
	Asqlite3 *db = static_cast<Asqlite3 *>(context);
	for (int i = 0; i < argc; i++) {
		db->_res += argv[i];
		db->_res += "\n";
	}
	return 0;
}

Asqlite3::loginCode Asqlite3::login(UserApp user)
{
	std::string sql = SELECT_QUERY("pseudo ") + FROM_QUERY("user ") + WHERE_QUERY("pseudo = '" + user.username + "';");
	this->_res.clear();
	if (!executeQuery(sql, callbackUserExist, this))
		std::cerr << "Error in login function.1" << std::endl;
	if (user.username != this->_res)
		return USER_NOT_EXIST;
	this->_res.clear();
	sql = SELECT_QUERY("pseudo ") +
	FROM_QUERY("user ") +
	WHERE_QUERY("pseudo = '" + user.username + "' AND password = '" + user.password + "';");
	if (!executeQuery(sql, callbackUserExist, this))
		std::cerr << "Error in login function.2" << std::endl;
	if (user.username != this->_res)
		return BAD_PASSWORD;
	this->_res.clear();
	return SUCCESS;
}

std::string Asqlite3::getUser(std::string name)
{
	std::string sql = SELECT_QUERY("pseudo ") +
	FROM_QUERY("user ") +
	WHERE_QUERY("pseudo LIKE '" + name + "%';");
	this->_res.clear();
	if (!executeQuery(sql, callbackGetUser, this)) {
		std::cerr << "Error in getUser function." << std::endl;
	}
	return this->_res;
}

bool Asqlite3::linkUser(std::string from, std::string to)
{
	std::string idfrom = getIdByUsername(from);
	if (idfrom.empty()) {
		std::cerr << "Not valid user 1" << std::endl;
		return false;
	}
	std::string idto = getIdByUsername(to);
	if (idto.empty()) {
		std::cerr << "Not valid user 2" << std::endl;
		return false;
	}
	this->getLinkedUser(from);
	for (auto user : this->_linkedUser) {
		if (from == user.username)
			return false;
	}
	std::string sql = "INSERT INTO contact(idfrom, idto) VALUES(" + idfrom + ", " + idto + ");";
	if (!executeQuery(sql, NULL, 0)) {
		std::cerr << "Error in linkUser function." << std::endl;
		return false;
	}
	return true;
}

bool Asqlite3::unlinkUser(std::string from, std::string to)
{
	std::string idfrom = getIdByUsername(from);
	if (idfrom.empty()) {
		std::cerr << "Not valid user 1" << std::endl;
		return false;
	}
	std::string idto = getIdByUsername(to);
	if (idto.empty()) {
		std::cerr << "Not valid user 2" << std::endl;
		return false;
	}
	std::string sql = "DELETE FROM contact WHERE (idfrom = " + idfrom + " AND idto = " + idto + ") OR (idto = " + idfrom + " AND idfrom = " + idto + ");";
	if (!executeQuery(sql, NULL, 0)) {
		std::cerr << "Error in linkUser function." << std::endl;
		return false;
	}
	return true;
}

std::string Asqlite3::getIdByUsername(std::string username)
{
	std::string sql = SELECT_QUERY("id ") +
		FROM_QUERY("user ") +
		WHERE_QUERY("pseudo='" + username + "';");

	this->_res.clear();
	if (!executeQuery(sql, callbackUserExist, this))
		std::cerr << "Error in getid function." << std::endl;
	if (this->_res.empty())
		return "";
	return (this->_res);
}

int Asqlite3::callbackFillContact(void *context, int argc, char** argv, char** azColName)
{
	Asqlite3 *db = static_cast<Asqlite3 *>(context);
	std::string username, address;

	for (int i = 0; i < argc; i = i + 3) {
		db->_linkedUser.push_back(UserApp(argv[i], argv[i + 1], "", std::atoi(argv[i + 2])));
	}
	return 0;
}

std::vector<UserApp> Asqlite3::getLinkedUser(std::string username)
{
	std::string id = getIdByUsername(username);
	std::string sql = SELECT_QUERY("pseudo, address, id ") +
		FROM_QUERY("contact ") +
		INNERJOIN_QUERY("user ON user.id=contact.idfrom OR user.id=contact.idto ") +
		WHERE_QUERY("user.id != "+id+" AND (contact.idfrom = "+id+" OR contact.idto = "+id+")");
	this->_linkedUser.clear();
	if (!executeQuery(sql, callbackFillContact, this))
		std::cerr << "Error in getlinkeduser function." << std::endl;
	return this->_linkedUser;
}

bool Asqlite3::checkUser(std::string username)
{
	std::string sql = SELECT_QUERY("pseudo ") +
		FROM_QUERY("user ") +
		WHERE_QUERY("pseudo = '" + username + "'");
	this->_res.clear();
	if (!executeQuery(sql, callbackUserExist, this))
		std::cerr << "Error in getlinkeduser function." << std::endl;
	if (this->_res.empty())
		return false;
	return true;
}

bool Asqlite3::executeQuery(std::string sql, int (*callback)(void *, int, char **, char **), void *context)
{
	sqlite3* DB;
	char* messageError;
	int exit = sqlite3_open(DB_DIR, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), callback, context, &messageError);
	if (exit != SQLITE_OK) {
		std::cout << messageError << std::endl;
		sqlite3_free(messageError);
		return false;
	}
	return true;
}
