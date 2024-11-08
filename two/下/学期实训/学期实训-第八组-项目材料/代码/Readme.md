# 客户端：

frontend:为前段设计recycleView的核心代码，通过动态和静态的嵌套设计实现。

wifi_locate:

Internet存储了一些跟网络请求有关的配置属性和工具类，包括请求发送的目标地址，Cookie的管理类。
avtivity：相关的界面

MyException：错误处理

其他为一些导航相关的类



# 服务器：

共三个python文件

Comment_record.py

Cut_The_Image.py

receive-server.py

和一个文件夹

user_ic

receive-server.py

flask后端主要文件，包括全部的接口，和数据库，服务器容器的调用信息。

Comment_record.py

一个工具类，创建了一个循环链表，永远记录用户的近三次评论的发起时间，用于防止用户恶意刷屏。

Cut_The_Image.py

定义了一个函数，用于处理用户前端发来的图片，将其裁剪为正方形并将尺寸调整至256*256

 

user_ic目录下存储了全部的用户头像。

# 数据库：

login:用于登录

user_comment:评论

uic_path：存储图片路径

userdata:用户定位及使用时间数据

data：wifi信号

# 可执行文件：

​                      收集.apk：用来收集数据的内部使用软件

​                      EGo.apk:开发的软件