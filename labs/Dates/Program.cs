using System;
using System.Collections.Generic;

public class Program
{
    static Dictionary<(int, int, int), int> memo;

    static int Play(int player, int month, int day)
    {
        // Проверяем, не выиграл ли уже кто-то до этого
        if (memo.ContainsKey((player, month, day)))
        {
            return memo[(player, month, day)];
        }

        // Проверяем, не проиграл ли игрок, который делает ход
        if (month == 12 && day == 31)
        {
            memo[(player, month, day)] = 3 - player; // 3 - player даст номер противоположного игрока
            return 3 - player;
        }

        // Пробуем добавить 1 день или 1 месяц, и проверяем, останется ли корректной дата
        if (day + 1 <= DateTime.DaysInMonth(2020, month) && Play(3 - player, month, day + 1) == player ||
            month + 1 <= 12 && Play(3 - player, month + 1, 1) == player)
        {
            memo[(player, month, day)] = player;
            return player;
        }
        else
        {
            memo[(player, month, day)] = 3 - player;
            return 3 - player;
        }
    }

    public static void Main()
    {
        memo = new Dictionary<(int, int, int), int>();

        // Читаем количество тестовых случаев
        int n = int.Parse(Console.ReadLine());

        for (int i = 0; i < n; i++)
        {
            // Читаем месяц и день
            string[] tokens = Console.ReadLine().Split();
            int month = int.Parse(tokens[0]);
            int day = int.Parse(tokens[1]);

            // Играем и выводим номер выигравшего игрока
            Console.WriteLine(Play(1, month, day));
        }
    }
}