class Program
{
    static void Main(string[] args)
    {
        StreamReader input = new StreamReader("input9.txt");

        List<string> substirngs = new List<string>();
        int count = int.Parse(input.ReadLine());

        string substring = "";
        char ch;

        for (int i = 0; i < count; i++)
        {
            ch = (char)input.Read();
            int symbolPos = substring.IndexOf(ch);

            if (substring.IndexOf(ch) != -1)
            {
                substirngs.Add(substring);
                if (symbolPos + 1 == substring.Length)
                {
                    substring = "";
                }
                else
                {
                    substring = substring.Substring(symbolPos + 1);
                }
            }

            substring += ch;
        }

        substirngs.Add(substring);

        substirngs.Sort((l, r) =>
        {
            if (l.Length != r.Length)
            {
                return l.Length > r.Length ? -1 : 1;
            }

            return l.CompareTo(r);
        });

        Console.WriteLine(substirngs[0]);

        input.Close();
    }
}