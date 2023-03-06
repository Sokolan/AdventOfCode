using System.Runtime.InteropServices.JavaScript;

namespace AdvantOfCode.day03;

public class Day03 : Solution
{
    private void UpdateBinaryNumHist(int[] hist, string[] lines)
    {
        foreach (string line in lines)
        {
            for (int i = 0; i < line.Length; ++i)
            {
                if (line[i] == '0')
                {
                    --hist[i];
                }
                else if (line[i] == '1')
                {
                    ++hist[i];
                }
            }
        }
    }

    private static string HistToBinaryNum(int[] hist)
    {
        string binaryNum = "";
        foreach (int num in hist)
        {
            binaryNum += (num >= 0) ? '1' : '0';
        }

        return binaryNum;
    }

    private string BinaryToDecimal(string num)
    {
        int res = 0;
        for (int i = 0; i < num.Length; ++i)
        {
            res += num[^(i+1)] == '0' ? 0 : Convert.ToInt32(Math.Pow(2, i));
        }

        return res.ToString();
    }

    private string XOR(string binaryNum)
    {
        string XOR = "";
        foreach (char digit in binaryNum)
        {
            XOR += (digit == '1') ? '0' : '1';
        }

        return XOR;
    }
    public string SolvePartOne(string filePath)
    {
        // Parse the input
        string[] lines = Util.ParseInput(filePath);
        // Make hist of most common digits in each column
        int[] binaryNumHist = new int[lines[0].Length];
        Array.Fill(binaryNumHist, 0);
        // update hist from input lines
        UpdateBinaryNumHist(binaryNumHist, lines);
        // Create binary num from hist
        string binaryNum = HistToBinaryNum(binaryNumHist);
        
        int gamma = Convert.ToInt32(BinaryToDecimal(binaryNum));
        string binaryNumXOR = (XOR(binaryNum));
        int epsilone = Convert.ToInt32(BinaryToDecimal(binaryNumXOR));

        return (gamma * epsilone).ToString();
    }

    private string FilterByMostCommon(string[] lines, bool xor)
    {
        string[] res = new string[lines.Length];
        Array.Copy(lines, res, lines.Length);
        int elementsLeft = lines.Length;
        int numSize = res[0].Length;
        int digit = 0;

        while (elementsLeft > 1)
        {
            // Make hist of most common digits in each column
            int[] binaryNumHist = new int[numSize];
            Array.Fill(binaryNumHist, 0);
            // update hist from input lines
            UpdateBinaryNumHist(binaryNumHist, res);
            // Create binary num from hist
            string binaryNum = HistToBinaryNum(binaryNumHist);
            if (xor)
            {
                binaryNum = XOR(binaryNum);
            }

            for (int i = 0; i < res.Length; ++i)
            {
                if (res[i] != "removed" && binaryNum[digit] != res[i][digit])
                {
                    res[i] = "removed";
                    --elementsLeft;
                }
            }

            ++digit;
        }

        foreach (var num in res)
        {
            if (num != "removed")
            {
                return BinaryToDecimal(num);
            }
        }

        return "";
    }
    public string SolvePartTwo(string filePath)
    {
        // Parse the input
        string[] lines = Util.ParseInput(filePath);
        string oxygen = FilterByMostCommon(lines, false);
        string CO2 = FilterByMostCommon(lines, true);

        return (Convert.ToInt32(oxygen) * Convert.ToInt32(CO2)).ToString();
    }
}