using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Threading.Tasks;

class Program
{
    static Dictionary<char, int> BuildWordMap(string word)
    {
        Dictionary<char, int> result = new Dictionary<char, int>();
        foreach (char ch in word)
        {
            if (result.ContainsKey(ch))
            {
                result[ch]++;
            }
            else
            {
                result.Add(ch, 1);
            }
        }
        return result;
    }

    static bool IsSynchronisedWord(Dictionary<char, int> initChars, string word)
    {
        Dictionary<char, int> characters = new Dictionary<char, int>(initChars);
        foreach (char ch in word)
        {
            if (characters.ContainsKey(ch) && characters[ch] > 0)
            {
                characters[ch]--;
            }
            else
            {
                return false;
            }
        }

        return true;
    }

    static void SortWords(List<string> words)
    {
        words.Sort((s1, s2) =>
        {
            if (s1.Length != s2.Length)
            {
                return s2.Length.CompareTo(s1.Length);
            }

            return s1.CompareTo(s2);
        });
    }
    static void Main()
    {
        string initial = Console.ReadLine();    

        List<string> words = new List<string>();

        string part;
        while ((part = Console.ReadLine()) != null)
        {
            words.Add(part);
        }
       
        Dictionary<char, int> initChars = BuildWordMap(initial);

        List<string> result = new List<string>();
        int score = 0;
        foreach (string word in words)
        {
            if (IsSynchronisedWord(initChars, word))
            {
                score += word.Length;
                result.Add(word);
            }
        }

        SortWords(result);

        Console.WriteLine(score);
        foreach (string word in result)
        {
          Console.WriteLine(word);
        }
    }
}