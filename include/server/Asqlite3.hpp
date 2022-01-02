/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** ASqlite3
*/

#include "sqlite3.h"
#include "common/standard.h"
#include "common/User.hpp"

#ifndef ASQLITE3_HPP_
#define ASQLITE3_HPP_

#define DB_DIR "../user.db"
#define SELECT_QUERY(x) static_cast<std::string>("SELECT ") + x
#define FROM_QUERY(x) static_cast<std::string>("FROM ") + x
#define WHERE_QUERY(x) static_cast<std::string>("WHERE ") + x
#define INNERJOIN_QUERY(x) static_cast<std::string>("INNER JOIN ") + x

class Asqlite3 {
    public:
        Asqlite3();
        ~Asqlite3();

        enum loginCode {SUCCESS, USER_NOT_EXIST, BAD_PASSWORD};
        bool uploadData(struct UserApp user);
        loginCode login(struct UserApp user);
        std::string getUser(std::string username);
        bool linkUser(std::string userfrom, std::string userto);
        bool unlinkUser(std::string userfrom, std::string userto);
        std::string getIdByUsername(std::string username);
        std::vector<struct UserApp> getLinkedUser(std::string username);
        bool checkUser(std::string username);

    protected:
    private:
        std::string _res;
        std::vector<struct UserApp> _linkedUser;

        static int callbackUserExist(void *, int argc, char** argv, char** azColName);
        static int callbackGetUser(void *, int argc, char** argv, char** azColName);
        static int callbackFillContact(void *, int argc, char** argv, char** azColName);
        static bool executeQuery(std::string sql, int (*callback)(void *, int, char **, char **), void *context);
};

#endif /* !ASQLITE3_HPP_ */
