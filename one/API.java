//开始做项目了
Math
        数学计算的工具类
//不需要创建对象，直接调用，因为是静态的
        abs 参数绝对值
        ceil 向上取整  floor向下取整
        round 四舍五入    max，min      pow(a,b)//结果是double 类型的，b可以是正负，但一般b是大于等于1的
        sqrt();//开根号的数  cbrt()//开立方根
        random();//[0.0,1.0)


//使用
        Math.abs();//一个细节，如果没有正数与之对应则会报错，-2147483648
        Math.absExact();

        Math.ceil(-12.68);  //-12
//本质上，向上取整，靠近数轴右边去取
        Math.floor();
//向数轴的负无穷方向

        System
//计算机的时间原点：1970 1/1  0:0:0  我国   8:0:0

//
        System.exit(0);//0正常停止，非0异常停止

        System.currentTimeMillis();
//当前时间的毫秒值形式
//应用：计算程序运行所需时间，两个变量：end-start

//数组复制，注意数组数据的基本数据类型必须保持一致
//需要考虑数组的长度，是否会产生越界的问题
//如果是引用数组类型，子类可以赋值给父类
        System.arrayCopy(源数组，起始索引，数组去向，第几个索引，拷贝几个);


  //运行环境：      Runtime
//获取Runtime对象
Runtime r1=Runtime.get
