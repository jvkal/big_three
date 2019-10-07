using System;
namespace Project
{
    class Class1
    {
        int i=5;//全局变量
        public void ListInt(params int[] ints) {
            //循环显示数据的代码
            //for (int x = 0; x < ints.Length; x++)
            //{
            //    Console.WriteLine(ints[i]);
            //}
            /*
             * 其实上面的语句也等价与
             */

            //特别要注意的是这里的中间里面的i,这里是i而不是ints[i],因为这里的ints[i]都已经赋值给了i了
            //所以这里只要写i就可以了
            foreach (int i in ints) {
                Console.WriteLine(i);
            }
        }
        public void Test1() {
            //输出全局的变量
            Console.WriteLine(i);
        }
        public static  void Main()
        {
            Console.WriteLine(1);
            /*
             * 读取一个标准的输入程序
             */
            //Console.ReadLine();
            /*
             * 读取一个键位的输入
             */
            //Console.ReadKey();
            int i = 13;
            int j = 14;
            /*
             * 正常显示使用借位符号
             */
            Console.WriteLine("i={0},j={1}",i,j);
            //不适用借位符完成
            Console.WriteLine(i);
            Console.WriteLine(j);
            //测试全局变量的输出

            //必须要实例化一个对象才可以使用，好像一个类中间就只能有一个static的对象,一般都是Main函数使用这个对象
            //所以这里使用了实例化对象的方法来完成
            Class1 cs1 = new Class1();
            cs1.Test1();
            int [] x = {1,2,3,3,1,2,3,1,3,1};
            cs1.ListInt(x);
            //cs1.ListInt(2);
        }
    }
}   
