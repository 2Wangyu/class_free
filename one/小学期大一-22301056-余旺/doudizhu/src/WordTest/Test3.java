package WordTest;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;
import freemarker.template.Version;

import java.io.*;
import java.text.SimpleDateFormat;
import java.util.HashMap;
import java.util.Map;

//实现写出word文档保存用户的信息
public class Test3 {
    //三个参数
    private String name;
    private String password;
    private int happybean;
    //初始化
    public Test3(String name,String password,int happybean){
        this.name=name;
        this.happybean=happybean;
        this.password=password;

    }
    public  void test() {
        Map<String, Object> dataMap = new HashMap<String, Object>();
        try {
            //姓名
            dataMap.put("Name", name);
            //欢乐豆
            dataMap.put("Happybean", happybean);
            //密码
            dataMap.put("Password", password);

            //Configuration 用于读取ftl文件
            Configuration configuration = new Configuration(new Version("2.3.0"));
            configuration.setDefaultEncoding("utf-8");

             // 以下是指定ftl文件所在目录路径的方
            //指定路径的方式，我的路径是
            configuration.setDirectoryForTemplateLoading(new File("D:\\桌面\\斗地主word\\template"));

            //输出文档路径及名称
            File outFile = new File("D:\\桌面\\斗地主word\\"+name+"'s msg"+".doc");

            //以utf-8的编码读取ftl文件
            Template template = configuration.getTemplate("斗地主个人信息.ftl", "utf-8");
            Writer out = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outFile), "utf-8"), 10240);
            template.process(dataMap, out);
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
//    public static void main(String[] args) {
//      Test3 test3=new Test3("yu","456",10000);
//      test3.test();
//
//    }
    }
