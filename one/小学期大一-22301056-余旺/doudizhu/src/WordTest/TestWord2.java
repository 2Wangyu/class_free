package WordTest;

import org.apache.poi.ooxml.POIXMLDocument;
import org.apache.poi.xwpf.usermodel.XWPFDocument;
import org.apache.poi.xwpf.usermodel.XWPFParagraph;
import org.apache.poi.xwpf.usermodel.XWPFRun;

import java.io.FileOutputStream;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

public class TestWord2 {

    public static void main(String[] args) throws Exception {
        Map<String, String> map = new HashMap<>();
        map.put("Name", "yuwang");
        map.put("Password", "1234");
        map.put("Happybean", "1000");
        XWPFDocument document = new XWPFDocument(POIXMLDocument.openPackage("D:\\桌面\\斗地主word\\斗地主个人信息.docx"));
        Iterator<XWPFParagraph> itPara = document.getParagraphsIterator();
        while (itPara.hasNext()) {
            XWPFParagraph paragraph = (XWPFParagraph) itPara.next();
            List<XWPFRun> runs = paragraph.getRuns();
            for (int i = 0; i < runs.size(); i++) {
                String oneparaString = runs.get(i).getText(runs.get(i).getTextPosition()).trim();
                for (Map.Entry<String, String> entry : map.entrySet()) {
                    if (oneparaString.equals(entry.getKey())) {
                        oneparaString = oneparaString.replace(entry.getKey(), entry.getValue());
                    }
                }
                runs.get(i).setText(oneparaString, 0);
            }
        }
        FileOutputStream outStream = null;
        outStream = new FileOutputStream("D:\\桌面\\斗地主word\\斗地主.docx");
        document.write(outStream);
        outStream.close();
    }


}
