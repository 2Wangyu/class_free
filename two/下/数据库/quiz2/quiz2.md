Suppose there are the following tables. 

s (sno, sname, sex, birthday, classno , 6 567 totalCredit ); initial totalCredit=0 

class (classno, className, classsMajor, school, studentNumber)班级人数 

c ( cno, cname, credit);

 sc (sno, cno, grade ); 

teacher (tno , tname, sex, birthday, title ); 

teaching ( tno, cno, Llanguage, year ); 



![屏幕截图 2024-04-18 185045](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185045.png)

2分：





![屏幕截图 2024-04-18 185059](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185059.png)





CREATE VIEW View_80 AS
SELECT sno, cno, grade       请问老师写成这样是被扣了0.5分吗？我按照题目要求来了
FROM SC
WHERE grade > 80
WITH CHECK OPTION;

2分





![屏幕截图 2024-04-18 185113](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185113.png)

这里写成count(*)被扣分了吗？还是join不能用吗，如果是join，老师，mysql是能用的

1.5





![屏幕截图 2024-04-18 185434](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185434.png)

2







![屏幕截图 2024-04-18 185440](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185440.png)



2分 ,join扣分？

SELECT s.sno, s.sname, sc.cno, c.cname
FROM s
JOIN sc ON s.sno = sc.sno
LEFT JOIN c ON sc.cno = c.cno
WHERE sc.grade IS NULL;



![屏幕截图 2024-04-18 185447](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185447.png)



2分







![屏幕截图 2024-04-18 185500](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185500.png)![屏幕截图 2024-04-18 185511](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185505.png)

<img src="C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185600.png" alt="屏幕截图 2024-04-18 185600" style="zoom:200%;" />

![屏幕截图 2024-04-18 185511](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185511.png)

SELECT sno, AVG(grade) AS avgscore
FROM sc
GROUP BY sno
ORDER BY avgscore DESC
LIMIT 1;







![屏幕截图 2024-04-18 185717](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185717.png)

![屏幕截图 2024-04-18 185733](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185733.png)











![屏幕截图 2024-04-18 185740](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185740.png)

![屏幕截图 2024-04-18 185748](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185748.png)



2分





![屏幕截图 2024-04-18 185755](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185755.png)

![](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185908.png)

![屏幕截图 2024-04-18 185921](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185913.png)



![屏幕截图 2024-04-18 185921](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185921.png)













![屏幕截图 2024-04-18 185935](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185935.png)



1.5









![屏幕截图 2024-04-18 185941](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185941.png)



0







![屏幕截图 2024-04-18 185945](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185945.png)

![屏幕截图 2024-04-18 185953](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 185953.png)

![屏幕截图 2024-04-18 190001](C:\Users\29741\Pictures\Screenshots\小测\屏幕截图 2024-04-18 190001.png)