//Exception�������ڼ��쳣��д����д����
//RuntimeException:�������쳣
//Error:����

//�߼��������쳣������һ���쳣���󣬰������쳣�����ģ����ݣ�ԭ��λ�ã�
//������û�д����쳣���߼�(try catch),JVM�������������������(main)
//3,����������û�д����߼�����JVM����
//4��JVM�Ժ�ɫ�����ӡ�쳣����ֹ��ǰ����ִ�еĳ���
//

throw��ָ���ķ������׳�ָ�����쳣
throw new xxxException("�쳣�����Ľ��");
//1��д�ڷ����ڲ���
//2�����봦���쳣
//RuntimeException�������಻�ô����JVM����
//����ҪôthrowsҪôtry catch 
//3��������Exception����Exception������


��һ�ִ����쳣����JVM�����쳣���ڷ���������ʱ��ʹ��
public static void readName(����)throws AAAException,BBBException{
	throw new AAAException("");
    throw new BBBException("");
	
	//����д����
	System.out.println();
}
//�����쳣����throw,���Ӹ����ϵ��throw�Ļ�ֱ���������оͺ���
//���ڵ��õ�ʱ��ͬ��Ҫô��JVM����Ҫô�Լ�дtry catch
public static void main(String[] args)throws AAAException,BBBException{
	//�ڴ˴��Ļ������AAAException��BBBException�Ǹ��������Ĺ�ϵֱ���ø���ͺ���
	 readName(����);
	
}
//�׶ˣ������쳣�󣬺����Ĵ���Ͳ������ִ���ˣ���Ϊ��������жϳ���

�ڶ��ִ����쳣
//���÷���ʱ����ҪJVM�������д����쳣
try{
	//���ܲ����쳣�Ĵ���
	//eeee:�����Ĵ��룬�������ܲ�ִ����
}
catch(����һ���ճ��ı�������������try���׳����쳣����IOException e){
     //�׳�ʲô�쳣����catch�оͶ���ʲô�쳣������������
	 
	//�쳣������߼�
	System.out.println();
	
}
//1��try���׳�����쳣���󣬿��Զ��catch������һ��catchִ�оͲ����ж���һ��catch
//2���쳣��ִ��catch�еĴ����߼��󣬼���ִ��try catch֮��Ĵ���
System.out.println();
//�����Ƿ��������������붼��ִ��
finally{
	
	//�����Ƿ����Ҫ���еĳ���Ϊ��ִ��eeee ���Ĵ���
	//����catch�е�break,returnӰ��
	//System.exit(0)����ִ��
}
//�����tryһ��ʹ��
//һ��������Դ�ͷţ�
//���������return��䣬���ú���Զ����finally�еĽ��


//����쳣��
1�����try catch�ֱ���
2������쳣һ�β��񣬶�δ���
   //ע�����1�����Ӹ��࣬�������дǰ����򱨴���
               2,һ������ɹ�����������catch����ִ��


//���������
//������д���෽�����׳�������ͬ���쳣�����쳣�����࣬���߲��׳��쳣
//���಻�׳��쳣�����಻���׳��쳣����ֻ�ܲ���������




//�Զ����쳣
public class XXXException extends Exception/RuntimeException{
	public XXXException(){
		super();
	}
	//���쳣��Ϣ�Ĺ��췽��
	public XXXException(String message){
		super(message);
	}
}



Throwable���ж����������쳣����ķ���
1,String getMessage()  ���ش�throwable�ļ������
2,String toString()                     ��ϸ����Ϣ�ַ���
3,void printStackTrace()               JVM��ӡ�쳣����Ĭ�ϴ˷�������ӡ�쳣��ȫ��  //ʹ��
e.getMessage(); 