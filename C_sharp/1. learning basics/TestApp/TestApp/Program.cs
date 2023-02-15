// Program.cs
// Ryan Jensen
// 2018-06-11
//
// Test program just to get my fingers back into the groove of writing C#.

using System;
using System.Text;
using System.Linq;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using System.IO;

namespace TestApp
{

    //public enum Temperature
    //{
    //    Freeze,
    //    Low,
    //    Warm,
    //    Boil
    //}

    //struct Customer
    //{
    //    private string name;
    //    private double balance;
    //    private int id;

    //    public void createCust(string n, double b, int i)
    //    {
    //        name = n;
    //        balance = b;
    //        id = i;
    //    }

    //    public void showCust()
    //    {
    //        Console.WriteLine("Name     " + name);
    //        Console.WriteLine("Balance  {0:c}", balance);
    //        Console.WriteLine("ID       " + id);
    //    }
    //}

    //class Animal
    //{
    //    public double height { get; set; }
    //    public double weight { get; set; }
    //    public string sound  { get; set; }

    //    public string name;
    //    public string Name
    //    {
    //        get { return name; }
    //        set { name = value; }
    //    }

    //    public Animal()
    //    {
    //        this.height = 0;
    //        this.weight = 0;
    //        this.name = "no name";
    //        this.sound = "no sound";
    //        numOfAnimals++;
    //    }

    //    public Animal(double height, double weight, string name, string sound)
    //    {
    //        this.height = height;
    //        this.weight = weight;
    //        this.name = name;
    //        this.sound = sound;
    //        numOfAnimals++;
    //    }

    //    static int numOfAnimals = 0;

    //    public static int getNumOfAnimals()
    //    {
    //        return numOfAnimals;
    //    }

    //    public string ToString()
    //    {
    //        return String.Format("{0} is {1} inches tall, and weighs {2} lbs. It makes the sound, \"{3}\"",name, height, weight, sound);
    //    }

    //    public int getSum(int num1 = 1, int num2 = 1)
    //    {
    //        return num1 + num2;
    //    }

    //    public double getSum(double num1 = 1, double num2 = 1)
    //    {
    //        return num1 + num2;
    //    }

    //}



    //class Dog : Animal
    //{
    //    public string favFood { get; set; }

    //    public Dog() : base()
    //    {
    //        this.favFood = "No Favorite Food";
    //    }

    //    public Dog(double height, double weight, string name, string sound, string favFood) : base(height, weight, name, sound)
    //    {
    //        this.favFood = favFood;
    //    }

    //    new public string ToString()
    //    {
    //        return String.Format("{0} is {1} inches tall, and weighs {2} lbs. It makes the sound, \"{3}\". His favorite food is {4}", name, height, weight, sound, favFood);
    //    }

    //}

    //class Member
    //{
    //    private string name;
    //    private int memberID;
    //    private int memberSince;
    //    protected decimal annualFee;

    //    public override string ToString()
    //    {
    //        return
    //            "name: " + name +
    //            "\nmember ID: " + memberID +
    //            "\nmember since: " + memberSince +
    //            "\ntotal annual fee: " + annualFee;
    //    }

    //    public Member()
    //    {
    //        Console.WriteLine("Parent Constructor with 0 parameters");
    //    }

    //    public Member(string pName, int pMemberID, int pMemberSince)
    //    {
    //        Console.WriteLine("Parent Constructor with 3 parameters");
    //        name = pName;
    //        memberID = pMemberID;
    //        memberSince = pMemberSince;
    //    }

    //    public virtual void CalculateAnnualFee()
    //    {
    //        annualFee = 0;
    //    }
    //}

    
    //class MemberNormal : Member
    //{
    //    public MemberNormal(string pName, int pMemberID, int pMemberSince) : base(pName, pMemberID, pMemberSince)
    //    {
    //        Console.WriteLine("Child Constructor with 3 parameters");
    //    }

    //    public override void CalculateAnnualFee()
    //    {
    //        annualFee = 100.00m + 12.00m * 30.00m;
    //    }
    //}


    //class MemberVIP : Member
    //{
    //    public MemberVIP(string pName, int pMemberID, int pMemberSince) : base(pName, pMemberID, pMemberSince)
    //    {
    //        Console.WriteLine("Child Constructor with 3 parameters");
    //    }

    //    public override void CalculateAnnualFee()
    //    {
    //        annualFee = 1200.00m;
    //    }
    //}


    //enum DaysOfWeek
    //{
    //    Mon, Tue, Wed, Thu, Fri, Sat, Sun
    //}
    
    class Program
    {
        

        static void DisplayMsgPeriodically()
        {
            while(true)
            {
                Console.WriteLine("Hi");
                Thread.Sleep(2000);
            }
        }


        static void Main(string[] args)
        {

            Thread t1 = new Thread(new ThreadStart(DisplayMsgPeriodically));
            Thread t2 = new Thread(new ThreadStart(DisplayMsgPeriodically));
            t1.Start();
            t2.Start();

            Thread.Sleep(5000);



            #region unused code

            //string filePath = "deleteme.txt";
            //if (File.Exists(filePath))
            //{
            //    using (StreamReader sr = new StreamReader(filePath))
            //    {
            //        while (sr.EndOfStream != true)
            //        {
            //            Console.WriteLine(sr.ReadLine());
            //        }
            //        sr.Close();
            //    }
            //}
            //else
            //{
            //    Console.WriteLine("File \"{0}\" does not exist.",filePath);
            //}

            //// open file to append text
            //using (StreamWriter sw = new StreamWriter(filePath, true))
            //{
            //    sw.WriteLine("It is easy to write to a file in C#");
            //    sw.Close();
            //}


            //DateTime timeReference = DateTime.Now;
            //TimeSpan timeDifference;
            //int delay_ms = 1;
            //for(int i=0; i<5; i++)
            //{
            //    Thread.Sleep(1000);
            //    timeDifference = (DateTime.Now - timeReference);
            //    Console.WriteLine(timeDifference.TotalMilliseconds/1000.0);
            //}



            //int[] numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 14, 14 };

            //var query =
            //    from n in numbers
            //    where (n % 2) == 0
            //    select n;

            //foreach(int n in query)
            //{
            //    Console.WriteLine(n);
            //}

            //Console.WriteLine(query.ToString());

            //Member[] mems = new Member[2];

            //mems[0] = new MemberVIP("Matt", 1, 1990);
            //mems[1] = new MemberNormal("Ryan", 2, 1995);

            //foreach(Member m in mems)
            //{
            //    m.CalculateAnnualFee();
            //    Console.WriteLine(m.ToString());
            //}

            //DaysOfWeek theDay = (DaysOfWeek)10;

            //Console.WriteLine((DaysOfWeek)theDay);




            //string[] custs = new string[] { "Tom", "Paul", "Greg" };

            //using (StreamWriter sw = new StreamWriter("custs.txt"))
            //{
            //    foreach (string cust in custs)
            //    {
            //        sw.WriteLine(cust);
            //    }
            //}

            //string custName = "";

            //using (StreamReader sr = new StreamReader("custs.txt"))
            //{
            //    while ((custName = sr.ReadLine()) != null)
            //    {
            //        Console.WriteLine(custName);
            //    }
            //}

            //List<int> numList = new List<int> { 5, 10, 15, 20, 25 };

            //List<int> oddNums = numList.Where(n => n % 2 == 1).ToList();

            //foreach(int num in oddNums)
            //{
            //    Console.WriteLine(num + ", ");
            //}

            //Func<int, int, int> getSum = (x, y) => x + y;

            //Console.WriteLine("5 + 3 = " + getSum.Invoke(5, 3));

            //Customer alex = new Customer();
            //alex.createCust("Alex", -314.15, 655321);

            //alex.showCust();

            //Temperature micTemp = Temperature.Low;

            //switch (micTemp)
            //{
            //    case Temperature.Freeze:
            //        Console.WriteLine("Temp = Freeze");
            //        break;

            //    case Temperature.Low:
            //        Console.WriteLine("Temp = Low");
            //        break;

            //    case Temperature.Warm:
            //        Console.WriteLine("Temp = Warm");
            //        break;

            //    case Temperature.Boil:
            //        Console.WriteLine("Temp = Boil");
            //        break;
            //}



            //Shape tri = new Triangle(10, 5);
            //Shape rekt = new Rectangle(10, 5);

            //Console.WriteLine("triangle area is " + tri.area());
            //Console.WriteLine("rectangle area is " + rekt.area());

            //Shape combRect = new Rectangle(5, 5) + (Rectangle)rekt;

            //Console.WriteLine("comb rect area is " + combRect.area());

            //KeyValue<string, string> thing1 = new KeyValue<string, string>("", "");

            //thing1.key = "bread";
            //thing1.value = "$3.50";

            //KeyValue<int, string> samsungTV = new KeyValue<int, string>(0, "");

            //samsungTV.key = 6;
            //samsungTV.value = "a 101\" TV! It's bigger!";

            //thing1.showData();
            //samsungTV.showData();


            //Animal james = new Animal(23, 14, "James", "Meow");
            //Console.WriteLine(james.ToString());

            //Console.WriteLine("sum = " + james.getSum(15, 20));
            //Console.WriteLine("sum_d = " + james.getSum(15.3, 60));
            //Console.WriteLine("sum_d = " + james.getSum(num2: 1, num1: 77));

            //Animal groovy = new Animal
            //{
            //    name = "Groovy",
            //    height = 16,
            //    weight = 5,
            //    sound = "bah da da da"
            //};

            //Dog zin = new Dog();
            //Console.WriteLine(zin.ToString());
            //zin = new Dog(20, 15, "Zin", "Wimper!", "dog food");
            //Console.WriteLine(zin.ToString());

            // Hello World test.
            //Console.writeline("what is your name?");
            //string name = console.readline();
            //console.writeLine("Hello " + name);

            //bool canVote = true;

            //char grade = 'A';

            //long.MaxValue
            //Console.WriteLine(decimal.MaxValue);

            //Console.WriteLine("5 + 3 = " + (5 + 3));
            //Console.WriteLine("5 - 3 = " + (5 - 3));
            //Console.WriteLine("5 * 3 = " + (5 * 3));
            //Console.WriteLine("5 / 3 = " + (5 / 3));
            //Console.WriteLine("5.2 % 3 = " + (5.2 % 3));

            //int i = 0;

            //Console.WriteLine("i++ = " + (i++));
            //Console.WriteLine("++i = " + (++i));
            //Console.WriteLine("i-- = " + (i--));
            //Console.WriteLine("--i = " + (--i));

            //Console.WriteLine("i += 3 = " + (i+=3));
            //Console.WriteLine("i -= 2 = " + (i -= 2));
            //Console.WriteLine("i *= 2 = " + (i *= 2));
            //Console.WriteLine("i /= 2 = " + (i /= 2));
            //Console.WriteLine("i %= 2 = " + (i %= 2));

            //double pi10 = 31.4;
            //int intPi10 = (int)pi10;

            //Console.WriteLine("pi10 = " + pi10 + ". intPi10 = " + intPi10);

            //double number1 = 10.5;
            //double number2 = 15;

            //Console.WriteLine("Math.Abs(number1) = " + Math.Abs(number1));
            //Console.WriteLine("Math.Ceiling(nubmer1) = " + Math.Ceiling(number1));
            //Console.WriteLine("Math.Floor(number1) = " + Math.Floor(number1));
            //Console.WriteLine("Math.Max(number1, number2) = " + Math.Max(number1, number2));
            //Console.WriteLine("Math.Min(number2, number2) = " + Math.Min(number2, number2));
            //Console.WriteLine("Math.Pow(number1, 2) = " + Math.Pow(number1, 2));
            //Console.WriteLine("Math.Round(number1) = " + Math.Round(number1));
            //Console.WriteLine("Math.Sqrt(number1) = " + Math.Sqrt(number1));

            //Random rand = new Random();

            //for (int i = 0; i < 100; i++)
            //    Console.WriteLine("Random Number between 1 and 10 = " + (rand.Next(1,11)));

            //double age = 5;

            //if ((age >= 5) && (age <= 7))
            //{
            //    Console.WriteLine("Go to elementary school");
            //}
            //else if((age > 7) && (age < 13))
            //{
            //    Console.WriteLine("Go to middle schoole");
            //}
            //else
            //{
            //    Console.WriteLine("Go to highschool!");
            //}

            //int age = 15;

            //bool canDrive = age >= 16 ? true : false;
            //Console.WriteLine("CanDrive = " + canDrive);

            //int age = 0;
            //switch (age)
            //{
            //    case 0:
            //        Console.WriteLine("Infant");
            //        break;
            //    case 1:
            //    case 2:
            //        Console.WriteLine("Toddler");
            //        break;
            //    default:
            //        Console.WriteLine("Other than 0,1,2");
            //        break;

            //}

            //string guess;

            //do
            //{
            //    Console.WriteLine("Guess a number");
            //    guess = Console.ReadLine();
            //}
            //while (!guess.Equals("12"));

            //string randStr = "Here are some random characters";

            //foreach(char c in randStr)
            //{
            //    Console.WriteLine(c);
            //}

            //string myStr = "And then I made the program say,\n\"Hello world!\"\nand it worked out pretty good.";
            //Console.WriteLine(myStr);

            //string sampString  = "more words1";
            //string sampString2 = "more words";

            //Console.WriteLine("Is empty = " + String.IsNullOrEmpty(sampString));
            //Console.WriteLine("Is null or white space = " + String.IsNullOrWhiteSpace(sampString));
            //Console.WriteLine("length = " + sampString.Length);

            //Console.WriteLine("Are String sampString and sampString2 equal? " + sampString.Equals(sampString2));

            //string sampString = "A bunch of random words";

            //sampString = sampString.Replace("words", "characters");

            //sampString = sampString.Remove(0, 2);

            //Console.WriteLine("sampString is = \"" + sampString + "\"");

            //string[] names = new string[3] { "Matt", "Joe", "Paul" };

            //Console.WriteLine("Name List = " + String.Join(", ", names));

            //string sampString = "A bunch of random words";

            //string fmtStr = String.Format("{2:c} {1:00.00} {2:#.00} {3:0,0}", 1.56, 15.567, .56, 1000);

            //Console.WriteLine(fmtStr);

            //StringBuilder sb = new StringBuilder();

            //sb.Append("This is the first sentence. ");
            //sb.AppendFormat("My name is {0} and I live in {1} ", "Ryan", "Oregon");
            //sb.Replace("I", "1");
            //sb.Remove(5, 7);

            //Console.WriteLine(sb.ToString());

            //int[] randNumArray;

            //int[] randArray = new int[5];

            //int[] randArray2 = { 1, 2, 3, 4, 5 };

            //Console.WriteLine("Array Length = " + randArray2.Length);

            //Console.WriteLine("Item 0 is " + randArray2[0]);

            //for (int i = 0; i < randArray2.Length; i++)
            //{
            //    Console.WriteLine("{0} : {1}", i, randArray2[i]);
            //}

            //foreach(int num in randArray2)
            //{
            //    Console.WriteLine("{0} : {1}", num-1, randArray2[num-1]);
            //}

            //Console.WriteLine("Where is 1?  " + Array.IndexOf(randArray2, 1));

            //string[] names = { "Tom", "Paul", "Sally", "Rakesh" };
            //string nameStr = string.Join(", ", names);

            //string[] namesArray = nameStr.Split(",");

            //Console.WriteLine("where is Sally?  " + Array.IndexOf(names, names[2]));

            //int[,] multArray = new int[5, 3];

            //int[,] multArray2 = { { 0, 1 }, { 2, 3 }, { 4, 5 } };

            //foreach(int num in multArray2)
            //{
            //    Console.WriteLine(num);
            //}

            //for(int x = 0; x < multArray2.GetLength(0); x++)
            //{
            //    for(int y = 0; y < multArray2.GetLength(1); y++)
            //    {
            //        Console.WriteLine("{0}|{1} : {2}", x, y, multArray2[x, y]);
            //    }
            //}

            //List<int> numList = new List<int>();

            //numList.Add(5);
            //numList.Add(15);
            //numList.Add(25);

            //int[] randArray = { 1, 2, 3, 4, 5 };
            //numList.AddRange(randArray);

            //List<int> numList2 = new List<int>(randArray);

            //List<int> numList3 = new List<int>(new int[] { 1, 2, 3, 4 });

            //for(int i=0; i< numList.Count; i++)
            //{
            //    Console.WriteLine(numList[i]);
            //}

            //Console.WriteLine("Where is 4?  " + numList3.IndexOf(3));

            //Console.WriteLine("is 5 in the list?  " + numList3.Contains(5));

            //List<string> strList = new List<string>(new string[] { "tom", "paul" });

            //Console.WriteLine("is \"Tom\" in the list? " + strList.Contains("tom",
            //    StringComparer.OrdinalIgnoreCase));



            //try
            //{
            //    Console.Write("Divide 10 by ");
            //    int num = int.Parse(Console.ReadLine());
            //    Console.WriteLine("10/{0} = {1}", num, (10 / num));
            //}
            //catch(DivideByZeroException ex)
            //{
            //    Console.WriteLine("Can't divide by zero");
            //    Console.WriteLine(ex.GetType().Name);
            //    Console.WriteLine(ex.Message);
            //    throw ex;
            //}
            //catch(Exception ex)
            //{
            //    Console.WriteLine(ex.GetType().Name);
            //    Console.WriteLine(ex.Message);
            //}



            #endregion
        }
    }

    //abstract class Shape
    //{
    //    public abstract double area();

    //    public void sayHi()
    //    {
    //        Console.WriteLine("Hello");
    //    }
    //}


    //public interface ShapeItem
    //{
    //    double area();
    //}

    //class Rectangle : Shape
    //{
    //    private double length;
    //    private double width;

    //    public Rectangle(double L, double W)
    //    {
    //        length = L;
    //        width = W;
    //    }

    //    public static Rectangle operator+ (Rectangle rect1, Rectangle rect2)
    //    {
    //        double rectLength = rect1.length + rect2.length;
    //        double rectWidth = rect1.width + rect2.width;
    //        return new Rectangle(rectLength, rectWidth);
    //    }

    //    public override double area()
    //    {
    //        return length * width;
    //    }
    //}

    //class Triangle : Shape
    //{
    //    private double tri_base;
    //    private double tri_height;

    //    public Triangle(double B, double H)
    //    {
    //        tri_base = B;
    //        tri_height = H;
    //    }

    //    public override double area()
    //    {
    //        return 0.5 * tri_base * tri_height;
    //    }
    //}

    //class KeyValue<TKey, TValue>
    //{
    //    public TKey key { get; set; }
    //    public TValue value { get; set; }

    //    public KeyValue(TKey k, TValue v)
    //    {
    //        key = k;
    //        value = v;
    //    }

    //    public void showData()
    //    {
    //        Console.WriteLine("{0} is {1} ", this.key, this.value);
    //    }
        

    //}
}
