import pickle
import random
import uuid

import pandas as pd
import pymysql
from sklearn.metrics.pairwise import cosine_similarity
from flask import Flask, request, jsonify, send_file
from collections import Counter
import pymysql
from flask import Flask, request, session, jsonify
from flask_cors import CORS
from os import urandom
from wsgiref.simple_server import make_server
from Comment_record import CommentRecord
from Cut_The_Image import Get_User_Ic as save_ic
from datetime import datetime, timedelta
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
        return "hellow world"


# 定义 2xx 是登录界面错误: 201:用户名不存在, 202: 用户密码错误
# 注册账号
@app.route('/login/register', methods=['POST'])
def login_register():
    if request.method == "POST":
        username = request.form.get('username')
        password = request.form.get('password')
        role = request.form.get('role')
        try:
            values = (username, password)
            cursor.execute("insert into login(username,password) values(%s,%s)", values)
            db.commit()
            return "101"
        except pymysql.Error as e:
            print(e)
            db.rollback()
            # print(e.args[0])
            if e.args[0] == 1062:
                return str(e.args[0])


@app.route('/is_login_in', methods=['GET'])
def is_login_in():
    if request.method == "GET":
        # print(session)
        if "username" in session:
            # print("is_login_in:true")
            return "100"
        else:
            # print("is_login_in:false")
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
            cursor.execute("select username,password,uid from login where username= %s", (username,))

            data = cursor.fetchall()
            # print(data)
            if len(data) != 0:
                if data[0][1] == password:
                    # print(session)
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


@app.route('/user/upload_ic', methods=['POST'])
def upload_ic():
    if request.method == "POST":
        data = request.files
        uid = session.get("uid")
        path = str(uid) + ".jpg"
        try:
            cursor.execute(
                "INSERT INTO uic_path (uid, user_ic_path)VALUES (" + str(
                    uid) + ",\"" + path + "\")ON DUPLICATE KEY UPDATE user_ic_path = \"" + path + "\";")
            db.commit()
        except pymysql.Error as e:
            print(e)
            return "204"
        file = data['file']
        save_ic(file, path)
        return "100"


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

        if "uid" not in session:
            return "206"
        else:
            uid = session.get("uid")

        if "comment_record" not in session:
            session["comment_record"] = pickle.dumps(CommentRecord())
        comment_record: CommentRecord = pickle.loads(session.get('comment_record'))
        if not comment_record.add():
            return "204"
        session["comment_record"] = pickle.dumps(comment_record)
        try:
            sql = "INSERT INTO user_comment (uid, sid, stars, comment) VALUES (%s, %s, %s,%s )"
            values = (uid, sid, stars, comment)
            cursor.execute(sql, values)
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
        # print("店铺：" + sid)
        try:
            sql = "select name,comment,stars,login.uid from login,user_comment where login.uid=user_comment.uid and sid=%s"
            values = (sid,)
            cursor.execute(sql, values)
            data = cursor.fetchall()
            temp = {}
            result = []
            if (data != None):
                for i in data:
                    temp["name"] = i[0]
                    temp["comment"] = i[1]
                    temp["stars"] = i[2]
                    temp["uid"] = i[3]
                    result.append(temp.copy())
            return jsonify(result)

        except pymysql.Error as e:
            print(e)
            return "error"


@app.route("/user/get_uic", methods=['POST'])
def get_image():
    if request.method == "POST":
        uid = request.get_json()[0]
        if uid == -1:
            if "uid" not in session:
                return send_file("user_ic/default.png", mimetype="image/png")
            else:
                print("uid" + str(session.get("uid")))
                path = "user_ic/" + str(session.get("uid")) + ".jpg"
                return send_file(path, mimetype="image/jpg")
        else:
            try:
                path = "user_ic/" + str(uid) + ".jpg"
                return send_file(path, mimetype="image/jpg")
            except FileNotFoundError:
                print("not found")
                return send_file("user_ic/default.png", mimetype="image/png")

@app.route("/user/get_name", methods=['GET'])
def get_name():
    if request.method == "GET":
        uid = ""
        if "uid" not in session:
            return "204"
        else:
            uid = session.get("uid")
        sql = "SELECT name FROM login WHERE uid=%s;"
        values = (uid,)
        cursor.execute(sql, values)
        data = cursor.fetchone()
        return data[0]
@app.route("/user/update_name", methods=['POST'])
def update_name():
    if request.method == "POST":
        uid = ""
        name = request.form.get('name')
        if "uid" not in session:
            return "204"
        else:
            uid = session.get("uid")
        sql = "UPDATE login SET name = %s  WHERE uid = %s;"
        values = (name, uid)
        try:
            cursor.execute(sql, values)
            db.commit()
            return "100"
        except pymysql.Error as e:
            return str(e)




direction_to_coordinates = {
       "1.1": (0.5, 0.97, 1.1),
    #"1.2": (0.4, 0.72, 1.2),
    "1.3": (0.5, 0.87, 1.3),
    "1.4": (0.5, 0.79, 1.4),
    "1.5": (0.5, 0.71, 1.5),
    #"1.6": (0.4, 0.63, 1.6),
    "1.7": (0.5, 0.63, 1.7),
    "1.8": (0.5, 0.54, 1.8),
    "1.9": (0.5, 0.45, 1.9),
    "1.11": (0.5, 0.38, 1.11),
    "1.12": (0.5, 0.30, 1.12),
    "1.13": (0.5, 0.22, 1.13),
    "1.14": (0.5, 0.14, 1.14),
    "1.15": (0.5, 0.06, 1.15),
    
    "401": (0.4, 0.89, 401),
    "402": (0.4, 0.45, 402),
    "403": (0.4, 0.38, 403),
    "413": (0.6, 0.21, 413),
    "414": (0.68, 0.52, 414),
    "415": (0.68, 0.88, 415),
}

def connect_to_mysql(host, user, password, database):
    try:
        connection = pymysql.connect(
            host=host,
            user=user,
            password=password,
            database=database,
            cursorclass=pymysql.cursors.DictCursor
        )
        return connection
    except pymysql.MySQLError as e:
        print(f"Error: Could not connect to MySQL. {e}")
        return None

def fetch_training_data(connection):
    try:
        with connection.cursor() as cursor:
            query = "SELECT Time, Position, BSSID, RSSI FROM data"
            cursor.execute(query)
            training_data = cursor.fetchall()
        return training_data
    except pymysql.MySQLError as e:
        print(f"Error fetching training data: {e}")
        return None

def fetch_userPosition(connection):
    try:
        with connection.cursor() as cursor:
            current_time = datetime.now()
            time_threshold = current_time - timedelta(seconds=10)
            
            query = """
                SELECT username, position FROM userdata
                WHERE ABS(TIMESTAMPDIFF(SECOND, time, %s)) <= 15
                """
            cursor.execute(query, (current_time,))
            user_data = cursor.fetchall()
            
            user_position_dict = {record['username']: record['position'] for record in user_data}
            
            return user_position_dict
    except pymysql.MySQLError as e:
        print(f"Error fetching user data: {e}")
        return None

def find_most_similar_position(connection, input_data, username):
    try:
        training_data = fetch_training_data(connection)
        if not training_data:
            return None

        df = pd.DataFrame(training_data)
        df = df[df['Position'] != 'Position']

        grouped = df.groupby(['Time', 'Position'])

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

        top_k_directions = sorted(similarities.items(), key=lambda item: item[1], reverse=True)[:3]

        direction_counts = Counter([direction for (time, direction), _ in top_k_directions])
        most_common_direction = direction_counts.most_common(1)[0][0]
        print("most_common_direction", most_common_direction)

        return most_common_direction
    except pymysql.MySQLError as e:
        print(f"Error: {e}")
        return None

@app.route('/')
def index():
    return "WiFi Positioning System Backend is Running"

def insert_or_update_userPosition(connection, username, position, time_column):
    try:
        with connection.cursor() as cursor:
            check_query = "SELECT COUNT(*) as count FROM userdata WHERE username = %s"
            cursor.execute(check_query, (username,))
            result = cursor.fetchone()
            
            if result['count'] >=1:
                print("1")
                update_query = """
                    UPDATE userdata
                    SET position = %s, time = %s
                    WHERE username = %s
                    """
                cursor.execute(update_query, (position, time_column, username))
                print("Data updated successfully",username,time_column)
            else:
                print("2")
                insert_query = """
                    INSERT INTO userdata (username, position, time)
                    VALUES (%s, %s, %s)
                    """
                cursor.execute(insert_query, (username, position, time_column))
                print("Data inserted successfully",username,time_column)
             
            connection.commit()
            print("Data inserted/updated successfully")
    except pymysql.MySQLError as e:
        print(f"Error111: {e}")

@app.route('/locator', methods=['POST'])
def receive_data():
    connection = None  # 确保 connection 被初始化
    try:
        data = request.get_json()
        if not data or not isinstance(data, dict):
            app.logger.error('Invalid JSON data: Expected a dictionary')
            return jsonify({'status': 'error', 'message': 'Invalid JSON data: Expected a dictionary'}), 400

        username = data.get('username')
        if not username:
            return jsonify({'status': 'error', 'message': 'Username is required'}), 400

        results = data.get('results')
        if not results:
            return jsonify({'status': 'error', 'message': 'Results are required'}), 400

        connection = connect_to_mysql(train_host, train_user, train_password, train_database)
        if not connection:
            return jsonify({'status': 'error', 'message': 'Database connection failed'}), 500

        most_similar_position = find_most_similar_position(connection, results, username)
        if not most_similar_position:
            return jsonify({'status': 'error', 'message': 'Could not find similar position'}), 500
        
        user_positions = fetch_userPosition(connection)
        print("userposition", user_positions)
        coordinates = direction_to_coordinates.get(most_similar_position)
        
        insert_or_update_userPosition(connection, username, most_similar_position, datetime.now())
        return jsonify({
            "status": "success",
            "most_similar_direction": most_similar_position,
            "coordinates": coordinates,
            "user_positions": user_positions  
        }), 200
    except Exception as e:
        app.logger.error(f"Exception: {str(e)}")
        return jsonify({"status": "error", "message": str(e)}), 400
    finally:
        if connection and connection.open:
            connection.close()




if __name__ == '__main__':
    train_host = 'localhost'
    train_user = 'root'
    train_password = 'cgl103122'
    train_database = 'wifi'
    table = 'data'
    # app.run(host='192.168.35.68', port=8080)
    httpd = make_server('0.0.0.0', 8080, app)
    httpd.serve_forever()
    db.close()

# 运行前先查看一下当前的本机地址，然后修改下面的地址
# if __name__ == "__main__":
#     # httpd = make_server('127.0.0.1', 8080, app)
#     # httpd.serve_forever()
#     app.run("192.168.149.68", port=8080)
#     ctx.pop()
#     db.close()
