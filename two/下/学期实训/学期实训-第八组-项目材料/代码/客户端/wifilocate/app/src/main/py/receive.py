import pandas as pd
import pymysql
from sklearn.metrics.pairwise import cosine_similarity
from flask import Flask, request, jsonify
from collections import Counter

app = Flask(__name__)


direction_to_coordinates = {
    
    "1.1": (0.5, 0.97, 1.1),
    # "1.2": (0.5, 0.92, 1.2),
    "1.3": (0.5, 0.87, 1.3),
    "1.4": (0.5, 0.79, 1.4),
    "1.5": (0.5, 0.71, 1.5),
    #"1.6": (0.5, 0.68, 1.6),
    "1.7": (0.5, 0.63, 1.7),
    "1.8": (0.5, 0.54, 1.8),
    "1.9": (0.5, 0.45, 1.9),
    "1.11": (0.5, 0.38, 1.11),
    "1.12": (0.5, 0.30, 1.12),
    "1.13": (0.5, 0.22, 1.13),
    "1.14": (0.5, 0.14, 1.14),
    "1.15": (0.5, 0.06, 1.15),
    

    "401.1": (0.26, 0.96, 401.1),
    "401.2": (0.26, 0.82, 401.2),
    "401.3": (0.4, 0.96, 401.3),
    "401.4": (0.4, 0.82, 401.4),
    
    
    "402.1": (0.4, 0.55, 402.1),
    "402.2": (0.4, 0.45, 402.2),
    "402.3": (0.26, 0.55, 402.3),
    "402.4": (0.26, 0.45, 402.4),

    "403.1": (0.4, 0.38, 403.1),
    "403.2": (0.4, 0.21, 403.2),
    "403.3": (0.26, 0.38, 403.3),
    "403.4": (0.26, 0.21, 403.3),

    
    "413.1": (0.6, 0.37, 413.1),
    "413.2": (0.6, 0.21, 413.2),
    "413.3": (0.76, 0.37, 413.3),
    "413.4": (0.76, 0.21, 413.4),

    
    "414.1": (0.60, 0.61, 414.1),
    "414.2": (0.60, 0.44, 414.2),
    "414.3": (0.76, 0.61, 414.3),
    "414.4": (0.76, 0.44, 414.4),
    

    "415": (0.68, 0.88, 415),
    
    "415.1": (0.6, 0.96, 415.1),
    "415.2": (0.68, 0.89, 415.2),
    "415.3": (0.76, 0.96, 415.3),
    "415.4": (0.76, 0.81, 415.4),        

    

}

def connect_to_mysql(host, user, password, database):
    """
    连接到 MySQL 数据库。
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
    """
    try:
        cursor = connection.cursor()
        query = "SELECT Time, Position, BSSID, RSSI FROM data"
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

def find_most_similar_direction(train_host, train_user, train_password, train_database, input_data):
    """
    从数据库中读取训练数据和测试数据，计算测试数据与训练数据中各点位的余弦相似度，返回最相似的点位和相似度分数。
    """
    connection = connect_to_mysql(train_host, train_user, train_password, train_database)
    if not connection:
        return None, None

    try:
        training_data = fetch_training_data(connection)
        if not training_data:
            return None, None

        df = pd.DataFrame(training_data)
        df = df[df['Position'] != 'Position']

        grouped = df.groupby(['Time', 'Position'])
        
        # 打印分组后的数据
        # for name, group in grouped:
        #     print(f'Group name: {name}')
        #     print(group)

        direction_vectors = {}
        for (time, direction), group in grouped:
            vector = group.set_index('BSSID')['RSSI'].to_dict()
            direction_vectors[(time, direction)] = vector

        input_vector = pd.Series({item['BSSID']: item['RSSI'] for item in input_data})

        similarities = {}
        for (time, direction), vector in direction_vectors.items():
            group_vector = pd.Series(vector)
            aligned_vectors = group_vector.align(input_vector, join='outer', fill_value=0)

            if isinstance(aligned_vectors[0], pd.Series) and isinstance(aligned_vectors[1], pd.Series):
                sim = cosine_similarity([aligned_vectors[0].values], [aligned_vectors[1].values])[0][0]
                similarities[(time, direction)] = sim
                #print(f'Similarity for {time}, {Position}: {sim}')

        # 选择相似度最高的5个方向
        top_k_directions = sorted(similarities.items(), key=lambda item: item[1], reverse=True)[:3]

        # 简单投票
        direction_counts = Counter([direction for (time, direction), _ in top_k_directions])
        most_common_direction = direction_counts.most_common(1)[0][0]

        print(f'The most similar Position is: {most_common_direction}')
        #print(f'Similarity scores: {similarities}')

        return most_common_direction

    except pymysql.MySQLError as e:
        print(f"Error: {e}")
        return None

    finally:
        if connection:
            connection.close()

@app.route('/locator', methods=['POST'])
def receive_data():
    try:
        data = request.get_json()
        #print("Received data:", data)

        most_similar_direction = find_most_similar_direction(
            train_host, train_user, train_password, train_database, data
        )

        
        
        coordinates = direction_to_coordinates.get(most_similar_direction)
        print(coordinates)
        print(most_similar_direction)

        return jsonify({
            "status": "success",
            "most_similar_direction": most_similar_direction,
            "coordinates":coordinates
        }), 200
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 400

@app.route('/')
def index():
    return "WiFi Positioning System Backend is Running"

if __name__ == '__main__':
    train_host = 'localhost'
    train_user = 'root'
    train_password = 'cfy1007'
    train_database = 'shixun'
    table = 'data'
    app.run(host='0.0.0.0', port=5000, debug=True) 
    
    
