#include "MyDB.h"

MyDB::MyDB()
{
    mysql = mysql_init(NULL);
    if (mysql == NULL)
    {
        std::cout << "Error:" << mysql_error(mysql);
        exit(1);
    }
}

MyDB::~MyDB()
{
    if (mysql != NULL)
    {
        mysql_close(mysql);
    }
}

bool MyDB::initDB(std::string host, std::string user, std::string pwd, std::string db_name)
{
    // 函数mysql_real_connect建立一个数据库连接
    // 成功返回MYSQL*连接句柄 失败返回NULL
    mysql = mysql_real_connect(mysql, host.c_str(), user.c_str(), pwd.c_str(), db_name.c_str(), 0, NULL, 0);
    if (mysql == NULL)
    {
        std::cout << "Error: " << mysql_error(mysql);
        exit(1);
    }
    return true;
}

bool MyDB::exeSQL(std::string sql,std::string& getValue)
{
    // mysql_query()执行成功返回0 执行失败返回非0值
    if (mysql_query(mysql, sql.c_str()))
    {
        std::cout << "Query Error:" << mysql_error(mysql);
        return false;
    }
    else // 查询成功
    {
        result = mysql_store_result(mysql); // 获取结果集
        if (result)                         // 返回了结果集
        {
            int num_fields = mysql_num_fields(result); // 获取结果集总共的字段数 即列数
            int num_rows = mysql_num_rows(result);     // 获取结果中总共的行数
            // getValue = mysql_fetch_row(result)[0];
            for (int i = 0; i < num_rows; i++)         // 输出每一行
            {
                // 获取下一行数据
                row = mysql_fetch_row(result);  //mysql_fetch_row返回的是一个字符串数组 表示一行的数据
                if (row == NULL)
                    break;
                for (int j = 0; j < num_fields; j++) // 输出每一个字段
                {
                    std::cout << row[j] << "\t\t";
                }
                std::cout << std::endl;
            }
        }
        else // result == NULL
        {
            if (mysql_field_count(mysql) == 0) // 代表执行的是update insert delete类的非查询语句
            {
                int num_rows = mysql_affected_rows(mysql); // 返回update insert delete影响的行数
            }
            else // error
            {
                std::cout << "Get result error: " << mysql_error(mysql);
                return false;
            }
        }
    }
    return true;
}





// g++ -std=c++11 -o MyDB MyDB.cpp `mysql_config --cflags --libs`