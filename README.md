# ScanLine

### 环境
ArchLinux  
Breeze Dark Theme [KDE]  
Qt Creator 4.7.1 based on Qt 5.11.2  

### 操作
* 左键单击按钮进行绘图，可查看已有的五角星，三角形，六芒星，箭头示例。  
* 在绘图区域移动鼠标滚轮，对图像进行放大或缩小。  
* 在绘图区域按下鼠标左键进行拖动，调整图像显示位置。  
* 在绘图区域按下鼠标右键，重置绘图区域。  

### 备注
* 绘图结果中红色方块表示多边形的内部，绿色方块表示多边形的顶点。  
* 扫描转换算法中，通过将ymax保存为ymax - 1来处理两条边相交出现顶点的情况，因此最终图形高度会比给出的顶点低一个像素。  
* 扫描转换算法中对于与X轴平行的边直接舍弃，防止扫描绘图过程中由于与x轴平行的边与扫描线有无数个交点而产生误差。  
* 随机生成策略中以clock()作为随机种子，避免两次绘图时间相差不足一秒时time()函数产生的随机种子相同。  
* 随机生成过程中，对于N边形，会将圆平均分成N份，每一份在其圆弧上随机确定一点，然后将N个点首尾相连形成多边形，使得生成结果易于查看。  

### 截图
![ScanLine.png](https://github.com/whoisnian/ScanLine/raw/master/ScanLine.png)  

### 演示
![ScanLine.gif](https://github.com/whoisnian/ScanLine/raw/master/ScanLine.gif)  
