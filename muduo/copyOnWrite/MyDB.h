/*
相关数据结构：
    MYSQL结构体
        此结构表示一个数据库连接的处理程序。它几乎用于所有MySQL功能。
    MYSQL_RES结构体
        存储查询结果数据。
    MYSQL_ROW结构体
        存储一行数据的结构。

相关函数的介绍：
1.mysql_init（）
    分配或初始化MYSQL适合的对象 mysql_real_connect()。如果 mysql是NULL指针，则该函数分配，初始化并返回一个新对象
    否则，对象被初始化并返回对象的地址。如果 mysql_init()分配一个新的对象，当mysql_close()被调用来关闭该连接时它被释放
    如果没有足够的内存分配一个新对象,则返回NULL
2. mysql_query（）
    执行指定为“以Null终结的字符串”的SQL查询。查询成功返回0，失败返回非0值
3.mysql_field_count（）
    返回连接上最近查询的列数
    这个函数的正常使用是 mysql_store_result()返回 NULL（因此你没有结果集指针）
    在这种情况下，可以调用 mysql_field_count()确定是否 mysql_store_result()应该产生非空结果
    这使得客户端程序能够在不知道查询是SELECT（或 类似SELECT））语句的情况下采取适当的操作

基本步骤就是：
    使用mysql_init()初始化连接
    使用mysql_real_connect()建立一个到mysql数据库的连接
    使用mysql_query()执行查询语句
    result = mysql_store_result(mysql)获取结果集
    mysql_num_fields(result)获取查询的列数，mysql_num_rows(result)获取结果集的行数
    通过mysql_fetch_row(result)不断获取下一行，然后循环输出
    释放结果集所占内存mysql_free_result(result)
    mysql_close(conn)关闭连接

*/

#ifndef _MYDB_H
#define _MYDB_H
#include <iostream>
#include <string>
#include <mysql/mysql.h>

class MyDB
{
public:
    MyDB();
    ~MyDB();
    // 连接mysql
    bool initDB(std::string host, std::string user, std::string pwd, std::string db_name);
    bool exeSQL(std::string sql, std::string& getValue); // 执行sql语句
private:
    MYSQL *mysql;      // 连接mysql句柄指针
    MYSQL_RES *result; // 指向查询结果的指针
    MYSQL_ROW row;     // 按行返回的查询信息
};

#endif