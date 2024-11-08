import pandas as pd
from sklearn.metrics.pairwise import cosine_similarity

def find_most_similar_direction(train_file, test_file):
    """
    读取训练数据和测试数据，计算测试数据与训练数据中各方向的余弦相似度，返回最相似的方向和相似度分数。

    :param train_file: 训练数据文件路径 (CSV 格式)
    :param test_file: 测试数据文件路径 (CSV 格式)
    :return: 最相似的方向和相似度分数
    """
    df = pd.read_csv(train_file, encoding='utf-8')
    
    grouped = df.groupby('Direction')
    direction_vectors = {}
    for direction, group in grouped:
        vector = group.set_index('BSSID')['RSSI'].to_dict()
        direction_vectors[direction] = vector

    input_df = pd.read_csv(test_file, encoding='utf-8')
    input_vector = pd.Series(input_df.set_index('BSSID')['RSSI'].to_dict())

    # 计算余弦相似度
    similarities = {}
    for direction, vector in direction_vectors.items():
        group_vector = pd.Series(vector).fillna(0)
        input_vector_filled = input_vector.reindex(group_vector.index).fillna(0)
        sim = cosine_similarity([group_vector], [input_vector_filled])[0][0]
        similarities[direction] = sim

    most_similar_direction = max(similarities, key=similarities.get)

    return most_similar_direction, similarities

train_file = '0703-1.csv'
test_file = 'test22.csv'
most_similar_direction, similarities = find_most_similar_direction(train_file, test_file)


print(f'The most similar direction is: {most_similar_direction}')
print(f'Similarity scores: {similarities}')

