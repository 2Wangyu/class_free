package WordTest;

import freemarker.template.Configuration;
import freemarker.template.Template;
import org.apache.poi.ooxml.POIXMLDocument;
import org.apache.poi.xwpf.usermodel.XWPFDocument;
import org.apache.poi.xwpf.usermodel.XWPFParagraph;
import org.apache.poi.xwpf.usermodel.XWPFRun;

import java.io.*;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

public class Testword {
    public static void genWord(){
        try {
            Map<String,String> dataMap1 = new HashMap<>();
            dataMap1.put("Name", "张三");
            Map<String,String> dataMap2 = new HashMap<>();
            dataMap2.put("Password", "张三");
            Map<String,String> dataMap3 = new HashMap<>();
            dataMap2.put("happybean", "1000");
            Configuration configuration = new Configuration();
            configuration.setDefaultEncoding("utf-8");
            //.xml 模板文件所在目录
            configuration.setDirectoryForTemplateLoading(new File("D:\\桌面\\斗地主word\\template"));
            // 输出文档路径及名称
            File outFile = new File("D:\\桌面\\斗地主word\\斗地主.docx");
            //以utf-8的编码读取模板文件
            Writer out = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outFile), "utf-8"),10240);
            Template t1 =  configuration.getTemplate("斗地主个人信息.xml","utf-8");
            t1.process(dataMap1, out);
            Template t2 =  configuration.getTemplate("斗地主个人信息.xml","utf-8");
            t2.process(dataMap2, out);
            Template t3 =  configuration.getTemplate("斗地主个人信息.xml","utf-8");
            t3.process(dataMap3, out);
            out.close();
            System.out.println("生成成功");
        }catch (Exception e){
            e.printStackTrace();
            System.out.println("生成失败");
        }
    }

    public static void main(String[] args) {
        genWord();
    }
}
