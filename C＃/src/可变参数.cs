using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Cshap14
{
    internal class Program
    {
        static void print<T>(params T[] list)
        {
            foreach(var item in list)
            {
                Console.Write("{0} ",item);
            }
            Console.WriteLine();
        }

        static void print(params char[] list)//如果传递的是数组则为按引用传递
        {
            for(int i = 0; i < list.Length; i++)
            {
                list[i] = '*';
            }
        }

        static void Main(string[] args)
        {
            print(1, 2, 3, 4, 5, 6);
            print("1", "2", "3", "4", "5", "6");
            char[] str = { '1', '2', '3', '4','5','6' };
            Console.WriteLine(str);
            print(str);
            Console.WriteLine(str);
        }
    }
}
