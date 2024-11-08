import pandas as pd
import pymysql
from sklearn.metrics.pairwise import cosine_similarity

def connect_to_mysql(host, user, password, database):
    """
    连接到 MySQL 数据库。

    :param host: MySQL 服务器地址
    :param user: MySQL 用户名
    :param password: MySQL 密码
    :param database: MySQL 数据库名称
    :return: 数据库连接对象
    """
    try:
        connection = pymysql.connect(host=host,
                                     user=user,
                                     password=password,
                                     database=database,
                                     cursorclass=pymysql.cursors.DictCursor)
        return connection
    except pymysql.MySQLError as e:
        print(f"Error: Could not connect to MySQL. {e}")
        return None

def fetch_training_data(connection):
    """
    从数据库中逐行读取训练数据。

    :param connection: 数据库连接对象
    :return: 读取的训练数据
    """
    try:
        cursor = connection.cursor()

        # 执行查询
        query = "SELECT Direction, BSSID, RSSI FROM "+ table
        cursor.execute(query)

        training_data = []
        for row in cursor:
            training_data.append(row)

        return training_data

    except pymysql.MySQLError as e:
        print(f"Error fetching training data: {e}")
        return None

    finally:
        if cursor:
            cursor.close()

def find_most_similar_direction(train_host, train_user, train_password, train_database, test_file):
    """
    从数据库中读取训练数据和测试数据，计算测试数据与训练数据中各方向的余弦相似度，返回最相似的方向和相似度分数。

    :param train_host: 训练数据所在的MySQL服务器地址
    :param train_user: 训练数据MySQL用户
    :param train_password: 训练数据MySQL密码
    :param train_database: 训练数据MySQL数据库名称
    :param test_file: 测试数据文件路径 (CSV 格式)
    :return: 最相似的方向和相似度分数
    """

    # 连接到 MySQL 数据库获取训练数据
    connection = connect_to_mysql(train_host, train_user, train_password, train_database)
    if not connection:
        return None, None

    try:
        # 逐行获取训练数据
        training_data = fetch_training_data(connection)
        if not training_data:
            return None, None

        # 转换为 DataFrame
        df = pd.DataFrame(training_data)

        # 删除列名行
        df = df[df['Direction'] != 'Direction']

        # 分组数据为方向向量
        grouped = df.groupby('Direction')
        direction_vectors = {}
        for direction, group in grouped:
            vector = group.set_index('BSSID')['RSSI'].to_dict()
            direction_vectors[direction] = vector

        # 读取测试数据
        input_df = pd.read_csv(test_file, encoding='utf-8')
        print("Input Data:")
        print(input_df.head())

        input_vector = pd.Series(input_df.set_index('BSSID')['RSSI'].to_dict())

        # 计算余弦相似度
        similarities = {}
        for direction, vector in direction_vectors.items():
            group_vector = pd.Series(vector)
            aligned_vectors = group_vector.align(input_vector, join='outer', fill_value=0)

            # 检查 aligned_vectors 中是否包含数值数据
            if isinstance(aligned_vectors[0], pd.Series) and isinstance(aligned_vectors[1], pd.Series):
                sim = cosine_similarity([aligned_vectors[0].values], [aligned_vectors[1].values])[0][0]
                similarities[direction] = sim

        most_similar_direction = max(similarities, key=similarities.get)

        print(f'The most similar direction is: {most_similar_direction}')
        print(f'Similarity scores: {similarities}')

        return most_similar_direction, similarities

    except pymysql.MySQLError as e:
        print(f"Error: {e}")
        return None, None

    finally:
        if connection:
            connection.close()

# 示例用法
train_host = 'localhost'
train_user = 'root'
train_password = 'cfy1007'
train_database = 'shixun'
table = 'data'
test_file = 'test22.csv'

most_similar_direction, similarities = find_most_similar_direction(train_host, train_user, train_password, train_database, test_file)
