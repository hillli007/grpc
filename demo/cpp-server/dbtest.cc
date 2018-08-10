#include<iostream>

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/exception.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>

using namespace std;
using namespace sql;

void RunConnectMySQL() {
    Driver *driver;
    Connection *con;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "");
    Statement* state = con->createStatement();
    state->execute("use warehouse");

    // 查询
    ResultSet* result = state->executeQuery("select user_name from user");

    // 输出查询
    while (result->next()) {
        try {
            string user = result->getString("user_name");
            cout << user << endl;
        } catch (sql::SQLException& e) {
            std::cout << e.what() << std::endl;
        }
    }
    delete con;
}

int main(void) {
    RunConnectMySQL();
    return 0;
}
