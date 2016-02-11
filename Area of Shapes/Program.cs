using System;

namespace Area_of_Shapes
{
    class Shape
    {
        public const double PI = Math.PI;
        protected double x, y;

        public Shape(double x, double y)
        { this.x = x; this.y = y; }

        public virtual double Area()
        {
            return x * y;
        }

    }

    class Rectangle : Shape
    { 
        public double circumfence;

        public Rectangle(double x, double y) : base(x, y)
        { this.x = x; this.y = y; circumfence = 2 * (x + y); }
    }

    class Square : Shape
    {
        public double circumfence;

        public Square(double x) : base(x, x)
        { this.x = x; circumfence = 4 * x; }
    }

    class Circle : Shape
    {
        public double perimeter;

        public Circle(double x) : base(x, 0)
        { perimeter = x; }

        public override double Area()
        { return PI * perimeter * perimeter; }

    }

    class Triangle : Shape
    {
        private double s;
        public double[] sides = new double[3];

        public Triangle(double x, double y, double z) : base (x,y)
        { sides[0] = x; sides[1] = y; sides[2] = z; s = (x + y + z) / 2;}

        public override double Area()
        {
            return Math.Sqrt(s * (s - sides[0]) * (s - sides[1]) * (s - sides[2]));
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Circle Kolecko = new Circle(5);
            Triangle Pravouhly = new Triangle(3, 4, 5);
            Rectangle Cihla = new Rectangle(2, 4);
            Square Ctverec = new Square(5);

            Console.WriteLine("První objekt je kolečko a jeho typ je: {0}, jeho plocha {1} a jeho průměr {2}.", Kolecko.GetType(), Kolecko.Area(), Kolecko.perimeter);
            Console.WriteLine("Druhý objekt je trojhúhelník a jeho typ je: {0}, jeho plocha {1} a jeho strany: {2}, {3} a {4} jednotky.",
                Pravouhly.GetType(), Pravouhly.Area(), Pravouhly.sides[0], Pravouhly.sides[1], Pravouhly.sides[2]);
            Console.WriteLine("Třetí objekt je obdélník a jeho typ je: {0}, jeho plocha {1} a jeho obvod: {2}", Cihla.GetType(), Cihla.Area(), Cihla.circumfence);
            Console.WriteLine("Poslední objekt je čtverec a jeho typ je: {0}, jeho plocha {1} a jeho obvod {2}", Ctverec.GetType(), Ctverec.Area(), Ctverec.circumfence);
        }
    }
}
