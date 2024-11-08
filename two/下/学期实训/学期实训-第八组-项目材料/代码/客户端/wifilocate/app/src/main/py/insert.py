import pandas as pd
import pymysql


# host = '119.3.163.32'
# user = 'root'
# password = 'cgl103122'
# database = 'wifi'
# table = 'data'
# csv_file = '0709-37.csv'

host = 'localhost'
user = 'root'
password = 'cfy1007'
database = 'shixun'
table = 'data'
csv_file = '0709-2.csv'


def insert_csv_to_mysql(host, user, password, database, table, csv_file):
    """
    连接到 MySQL 数据库，读取 CSV 文件并将其插入到指定的数据库表中。

    :param host: MySQL 服务器地址
    :param user: MySQL 用户名
    :param password: MySQL 密码
    :param database: MySQL 数据库名称
    :param table: 目标表名称
    :param csv_file: CSV 文件路径
    """
    try:
        # 连接到 MySQL 数据库
        connection = pymysql.connect(
            host=host,
            user=user,
            password=password,
            database=database
        )

        # 读取 CSV 文件
        df = pd.read_csv(csv_file, encoding='utf-8')
        print("CSV Data:")
        print(df.head())

        # 获取列名
        columns = df.columns.tolist()

        # 创建插入语句
        insert_query = f"INSERT INTO {table} ({', '.join(columns)}) VALUES ({', '.join(['%s'] * len(columns))})"

        # 打开 cursor
        with connection.cursor() as cursor:
            # 插入数据
            for i, row in df.iterrows():
                cursor.execute(insert_query, tuple(row))

            # 提交事务
            connection.commit()
            print(f"Data from {csv_file} has been inserted into {database}.{table} successfully.")

    except pymysql.MySQLError as e:
        print(f"Error: {e}")
        if connection.open:
            connection.rollback()

    finally:
        if connection.open:
            connection.close()



insert_csv_to_mysql(host, user, password, database, table, csv_file)
