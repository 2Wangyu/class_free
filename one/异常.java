//Exception：编译期间异常，写代码写错了
//RuntimeException:运行期异常
//Error:错误

//逻辑：出现异常，常见一个异常对象，包含了异常产生的（内容，原因，位置）
//方法中没有处理异常的逻辑(try catch),JVM会给方法调用者来处理(main)
//3,方法调用者没有处理逻辑，给JVM处理
//4，JVM以红色字体打印异常，终止当前正在执行的程序
//

throw在指定的方法中抛出指定的异常
throw new xxxException("异常产生的结果");
//1，写在方法内部，
//2，必须处理异常
//RuntimeException或者子类不用处理给JVM即可
//其余要么throws要么try catch 
//3，必须是Exception或者Exception的子类


第一种处理异常：给JVM处理异常，在方法声明的时候使用
public static void readName(参数)throws AAAException,BBBException{
	throw new AAAException("");
    throw new BBBException("");
	
	//继续写内容
	System.out.println();
}
//几个异常几个throw,有子父类关系的throw的话直接声明附列就好了
//而在调用的时候同样要么给JVM处理要么自己写try catch
public static void main(String[] args)throws AAAException,BBBException{
	//在此处的话，如果AAAException和BBBException是父类和子类的关系直接用父类就好了
	 readName(参数);
	
}
//弊端：出现异常后，后续的代码就不会继续执行了，因为虚拟机会中断程序

第二种处理异常
//调用方法时，不要JVM处理，自行处理异常
try{
	//可能产生异常的代码
	//eeee:后续的代码，出错后可能不执行了
}
catch(定义一个日常的变量，用来接受try中抛出的异常对象：IOException e){
     //抛出什么异常对象，catch中就定义什么异常变量用来接受
	 
	//异常处理的逻辑
	System.out.println();
	
}
//1，try中抛出多个异常对象，可以多个catch，但有一个catch执行就不会判断下一个catch
//2，异常后执行catch中的处理逻辑后，继续执行try catch之后的代码
System.out.println();
//不论是否正常，后续代码都会执行
finally{
	
	//不管是否出错都要运行的程序，为了执行eeee 处的代码
	//不受catch中的break,return影响
	//System.exit(0)不会执行
}
//必须和try一起使用
//一般用于资源释放，
//如果其中有return语句，调用后永远返回finally中的结果


//多个异常，
1，多个try catch分别处理
2，多个异常一次捕获，多次处理
   //注意事项：1，有子父类，子类必须写前面否则报错了
               2,一旦上面成功被处理，下面catch不再执行


//父类和子类
//子类重写父类方法，抛出父类相同的异常或者异常的子类，或者不抛出异常
//父类不抛出异常，子类不可抛出异常或者只能捕获不能声明




//自定义异常
public class XXXException extends Exception/RuntimeException{
	public XXXException(){
		super();
	}
	//带异常信息的构造方法
	public XXXException(String message){
		super(message);
	}
}



Throwable类中定义了三个异常处理的方法
1,String getMessage()  返回此throwable的简短描述
2,String toString()                     详细的消息字符串
3,void printStackTrace()               JVM打印异常对象，默认此方法，打印异常最全面  //使用
e.getMessage(); 