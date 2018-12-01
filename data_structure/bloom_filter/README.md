## bloomfilter

## bloomtest
通用测试类
- 通过宏定义完成测试单元（以类的形式）的编写

```
// TestBase 基类，其实可以没有
// TestBloom 测试类的名字
TEST(TestBase, TestBloom) {

}
```
- TEST不仅仅需要完成测试类的生成，还必须完成测试类的注册，为了方便所有测试类的调用，使用vector容器保存各个测试类（将容器设为全局static类型）
- runAllTest()直接遍历容器中的所有测试类，并调用测试类的方法Run() 