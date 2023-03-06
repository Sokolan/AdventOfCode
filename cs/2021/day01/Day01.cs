using System.Diagnostics;

namespace AdvantOfCode.day1;

public class Day01 : Solution
{
    private static int[] ParseInputToArray(string inputFile)
    {
        string input = File.ReadAllText(inputFile);
        string[] lines = input.Split(new[] { "\r\n", "\r", "\n" }, StringSplitOptions.RemoveEmptyEntries);
        int[] depths = Array.ConvertAll(lines, int.Parse);
        return depths;
    }

    private static int getNumOfIncrements(int[] depths)
    {
        int count = 0;
        for (int i = 1; i < depths.Length; ++i)
        {
            if (depths[i] > depths[i - 1])
            {
                ++count;
            }
        }

        return count;
    }
    public string SolvePartOne(string filePath)
    {
        int[] depths = ParseInputToArray(filePath);
        return getNumOfIncrements(depths).ToString();
    }

    public string SolvePartTwo(string filePath)
    {
        int[] depths = ParseInputToArray(filePath);
        List<int> depthsAccurateList = new List<int>();
        for (int i = 0; i < (depths.Length - 2); ++i)
        {
            depthsAccurateList.Add(depths[i] + depths[i+1] + depths[i+2]);
        }

        int[] depthsAccurate = depthsAccurateList.ToArray();
        return getNumOfIncrements(depthsAccurate).ToString();
    }
    
}