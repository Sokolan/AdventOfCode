namespace AdvantOfCode;

public class Util
{
    private readonly int _day;
    private string _expectedSol;
    

    public Util(int day)
    {
        _day = day;
    }

    public static string[] ParseInput(string inputFile)
    {
        string input = File.ReadAllText(inputFile);
        string[] lines = input.Split(new[] { "\r\n", "\r", "\n" }, StringSplitOptions.RemoveEmptyEntries);
        return lines;
    }

    private string GetDayLocation()
    {
        return new string($"../../../day{_day:D2}");
    }

    private bool RunExample(Solution solution, int part)
    {
        string partOneSol;
        if (part == 1)
        {
            partOneSol = solution.SolvePartOne(GetDayLocation() + $"/example.txt");
        }
        else
        {
            partOneSol = solution.SolvePartTwo(GetDayLocation() + $"/example.txt");
        }

        string message = (_expectedSol != partOneSol)
            ? $"Got:    {partOneSol} \nWas expecting:   {_expectedSol}"
            : "Test passed";
        Console.WriteLine(message);
        return (_expectedSol == partOneSol);
    }
    

    public void RunPart(Solution solution, int part, string expectedExampleSol)
    {
        _expectedSol = expectedExampleSol;
        
        if (!RunExample(solution, part))
        {
            Console.WriteLine("Test Failed.");
            return;
        }

        string result =  (part == 1)
            ? solution.SolvePartOne(GetDayLocation() + $"/input.txt")
            : solution.SolvePartTwo(GetDayLocation() + $"/input.txt");
        Console.WriteLine($"Part {part} result is:   {result}");
    }

    
}