#include <iostream>

#include "mysql.h"
//#include "code/Maples.h"

//g++ -g -c MaplesMySQL.cpp -I/usr/local/mysql/include/
//g++ -o mysqlhandle MaplesMySQL.o -L/usr/local/mysql/lib -lmysqlclient
namespace Maples {
    struct DBInfo {
        const char* host;
        const char* username;
        const char* password;
        const char* database;
    };

    class MySQL {
    public:
        MySQL();
        ~MySQL();
        bool init(DBInfo& info);
        bool execute(const char* sql);
        bool setCharacter(const char* charset);
        std::string query(const char* sql);

    private:
        MYSQL* connection;
        MYSQL_RES* result;
        MYSQL_ROW row;
    };
}

Maples::MySQL::MySQL() {
    if ((this->connection = mysql_init(NULL)) == NULL) {
        std::cerr << "Error" << mysql_error(connection) << std::endl;
        exit(1);
    }
}

Maples::MySQL::~MySQL() {
    if (this->connection != NULL) {
        mysql_close(this->connection);
    }
}

bool Maples::MySQL::init(DBInfo& info) {
    mysql_real_connect (this->connection,
                        info.host,
                        info.username,
                        info.password,
                        info.database,
                        0, NULL, 0);
    if (this->connection == NULL) {
        std::cerr << "Error:" << mysql_error(connection) << std::endl;
        exit(1);
    }
    return true;
}

bool Maples::MySQL::execute(const char* sql) {
    if (mysql_query(this->connection, sql)) {
        std::cerr << "Execute Error:" << mysql_error(connection) << std::endl;
        exit(1);
    }
    return true;
}

bool Maples::MySQL::setCharacter(const char* charset) {
    if(mysql_set_character_set(this->connection, charset) != 0) {
        std::cerr << "Charset Error:" << mysql_error(connection) << std::endl;
        exit(1);
    }
    return true;
}

std::string Maples::MySQL::query(const char* sql) {
    std::string resultStr;

    if (mysql_query(this->connection, sql)) {
        std::cerr << "Execute Error:" << mysql_error(connection) << std::endl;
        exit(1);
    } else {
        //this->result = mysql_use_result(this->connection);
        this->result = mysql_store_result(this->connection);
        unsigned int resultSize = mysql_num_rows(this->result);
        for (int i = 0; i < resultSize; ++i) {
            if ((row = mysql_fetch_row(this->result)) < 0) {
                break;
            }
            unsigned int rowSize = mysql_num_fields(this->result);
            for (int j = 0; j < rowSize; ++j) {
                resultStr.append(row[j]);
                resultStr.append("\t");
            }
            resultStr.append("\n");
        }

        mysql_free_result(this->result);
    }

    return resultStr;
}


int main(int argc, char* argv[]) {
    Maples::MySQL handle;
    Maples::DBInfo info;
    info.host = "localhost";
    info.username = "root";
    info.password = "216106";
    info.database = "homework";
    handle.init(info);
    handle.setCharacter("utf8");
    //handle2
    
    char a[1024];
    while (true) {
        std::cin.getline(a, sizeof(a));
        std::cout << a << std::endl;
        handle.execute(a);
        std::cout << handle.query("select * from test;") << std::endl;
    }

    //handle.execute("insert into test values('1', 'aa', '11');");
    //std::cout << handle.query("select * from test;") << std::endl;

}
