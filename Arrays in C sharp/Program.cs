//Program úkazující práci s poli v C#
//Vyzve uživatele k zadání velikosti pole, inicializuje toto pole hodnotami indexů a pokračuje dál.
//Program lze ukončit zadáním nesmyslného indexu

using System;

namespace Arrays_in_C_sharp
{
    class Program
    {
        static void Main(string[] args)
        {
            int boundary;
            bool success = true;
            while (success)
            {
                Console.WriteLine("Prosím vložte velikost pole. Vložením písmene program ukončíte.");
                success = int.TryParse(Console.ReadLine(), out boundary);
                if (!success) { Console.WriteLine("Nebylo zadáno číslo. Program se nyní ukončí."); Console.ReadLine(); return; };
                if (boundary < 1) { Console.WriteLine("Pole o této velikosti nelze inicializovat. Používám pole o velikosti 1."); boundary = 1; }
                int[] Pole = new int[boundary];
                foreach (var element in Pole)
                {
                    Pole[element] = element;
                    Console.WriteLine("Prvek vašeho pole na pozici {0} byl nastaven na {1}", element, Pole[element]);
                }
                Console.WriteLine();
            };
        }
    }
}
