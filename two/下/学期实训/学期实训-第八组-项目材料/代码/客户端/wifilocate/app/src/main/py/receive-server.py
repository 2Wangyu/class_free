import random
import pandas as pd
import pymysql
from sklearn.metrics.pairwise import cosine_similarity
from flask import Flask, request, jsonify
from collections import Counter
import pymysql
from flask import Flask, request, session, jsonify
from flask_cors import CORS
from os import urandom
from wsgiref.simple_server import make_server

from flask import current_app
from flask import g

# 数据库连接
db = pymysql.connect(host="127.0.0.1", user="root", password="cgl103122", database="wifi_locator")
cursor = db.cursor()

# 后端服务启动
app = Flask(__name__)
app.secret_key = urandom(24)
CORS(app, resources=r'/*')

ctx = app.app_context()
ctx.push()





@app.route('/test', methods=['POST'])
def hellow():
    if request.method == "POST":
        print(request.headers)
        if "count" not in session:
            print("session created")
            session['count'] = 0
        session['count'] += 1
        print(session['count'])
        return "Hello World!"


# 定义 2xx 是登录界面错误: 201:用户名不存在, 202: 用户密码错误
# 注册账号
@app.route('/login/register', methods=['POST'])
def login_register():
    if request.method == "POST":
        username = request.form.get('username')
        password = request.form.get('password')
        role = request.form.get('role')
        try:
            cursor.execute(
                "insert into login(username,password) values(\"" + str(username) + "\",\"" + str(password) + "\")")
            db.commit()
            return "101"
        except pymysql.Error as e:
            # print(e)
            db.rollback()
            # print(e.args[0])
            if e.args[0] == 1062:
                return str(e.args[0])


@app.route('/is_login_in', methods=['GET'])
def is_login_in():
    if request.method == "GET":
        # print(session)
        if "username" in session:
            print("is_lofin_in:true")
            return "100"
        else:
            print("is_lofin_in:false")
            return "205"


@app.route('/login/logout', methods=['POST'])
def logout():
    if request.method == "POST":
        session.clear()
        return "1"


@app.route('/login/login', methods=['POST'])
def login_login():
    if request.method == "POST":
        username = request.form.get('username')
        password = request.form.get('password')
        try:
            cursor.execute("select username,password,uid from login where username=\""
                           + str(username) + "\"")
            data = cursor.fetchall()
            # print(data)
            if len(data) != 0:
                if data[0][1] == password:
                    print(session)
                    if "username" in session:
                        # 重登录
                        return "204"
                    session["username"] = username
                    session["uid"] = data[0][2]
                    # 登录成功
                    return str(100)
                else:
                    # 登陆失败：密码错误
                    return str(202)
            else:
                # 登陆失败账号不存在
                return str(201)
        except pymysql.Error as e:
            print(e)
            # 登陆失败：数据库错误
            return str(203)



# @app.route('/upload_user_ic', methods=['POST'])
# def upload_user_ic():
#     if request.method == "POST":
#         if request.files is None:
@app.route('/comment', methods=['POST'])
def comment():
    if request.method == "POST":
        sid = request.form.get('sid')
        stars = request.form.get('stars')
        comment = request.form.get('comment')
        if sid not in session:
            uid = "1"
        else:
            uid = session.get('uid')

        try:
            cursor.execute(
                "insert into user_comment(uid,sid,stars,comment) values(" + str(uid) + "," + str(sid) + "," + str(
                    stars) + ",\"" + comment + "\")");
            db.commit()
            return "100"
        except pymysql.Error as e:
            # print(e)
            db.rollback()
            print(e)
            return "206"


@app.route('/get_comment', methods=['POST'])
def get_comment():
    if request.method == "POST":
        sid = request.form.get('sid')
        cursor.execute("select name,comment,stars from login,user_comment where login.uid=user_comment.uid and sid="+str(sid)+";")
        data = cursor.fetchall()
        temp = {}
        result = []
        if (data != None):
            for i in data:
                temp["name"] = i[0]
                temp["comment"] = i[1]
                temp["stars"] = i[2]
                result.append(temp.copy())
            print("result:", len(data))
        print(result)
    return jsonify(result)







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

    "403": (0.33, 0.29, 403),
    "403.1": (0.4, 0.38, 403.1),
    "403.2": (0.4, 0.21, 403.2),
    "403.3": (0.26, 0.38, 403.3),
    "403.4": (0.26, 0.21, 403.3),

    "413": (0.68, 0.29, 413),
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


if __name__ == '__main__':
    train_host = 'localhost'
    train_user = 'root'
    train_password = 'cgl103122'
    train_database = 'wifi'
    table = 'data'
    app.run(host='0.0.0.0', port=8080, debug=True) 
    db.close()
    

# 运行前先查看一下当前的本机地址，然后修改下面的地址
# if __name__ == "__main__":
#     # httpd = make_server('127.0.0.1', 8080, app)
#     # httpd.serve_forever()
#     app.run("192.168.149.68", port=8080)
#     ctx.pop()
#     db.close()
