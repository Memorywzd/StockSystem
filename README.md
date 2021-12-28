# StockSystem
Course Design of Data Structure  
To design and implement a stock query and analysis system.

## 说明
项目使用qt5构建，使用vs2021开发。涉及到中文的部分，由于需要从excel表格读取数据，
因此项目使用多字节字符集以省去string、wstring或char、wchar的转换。
当需要向仅支持Unicode的qt界面输出由excel读出的GBK编码的汉字时，使用qt提供的text codec完成编码转换。
根据[微软官方的文档](https://docs.microsoft.com/zh-cn/cpp/text/support-for-multibyte-character-sets-mbcss)，“多字节字符集 (MBCS) 是一种支持无法用单字节表示的字符集（如日语和中文）的旧方法。 如果要进行新的开发，则应对所有文本字符串（最终用户不会看到的系统字符串也许可以除外）使用 Unicode。 MBCS 是旧技术，不建议用于新开发。”
运行项目需要正确配置qt5安装，且确保使用了合适的编码字符集。

## 开发日志
- 2021.12.20 下发任务，摸鱼
- 2021.12.21 摸鱼，创建工程
- 2021.12.22 完成文件读操作
- 2021.12.23 实现查询操作、直接排序操作（除ASL与写文件）
- 2021.12.24 完成除写入文件和ASL的全部查询、排序功能
- 2021.12.25 完成除二部图和Kruskal及历史遗留
- 2021.12.26 完成除写入文件和ASL的全部算法
- 2021.12.27 重构代码，使用qt写界面
- 2021.12.28 完成答辩，根据教师要求修正了若干个输出问题
被老师吐槽界面难看，~~能用不就行了~~放假再改（）
