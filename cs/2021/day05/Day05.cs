using System.Reflection.Metadata;

namespace AdvantOfCode.day05;

public class Day05 : Solution
{
    private ((int, int), (int, int)) StringToCoordinates(string input)
    {
        string[] coordinatesString = input.Split(new[] {"->", " ", ","}, StringSplitOptions.RemoveEmptyEntries);
        (int, int) coordinateFrom = (Convert.ToInt32(coordinatesString[0]), Convert.ToInt32(coordinatesString[1]));
        (int, int) coordinateTo = (Convert.ToInt32(coordinatesString[2]), Convert.ToInt32(coordinatesString[3]));
        return (coordinateFrom, coordinateTo);
    }
    private void FillMapRow(Dictionary<(int, int), int> map, (int, int) coordinateFrom, (int, int) coordinateTo)
    {
        if (coordinateFrom.Item2 == coordinateTo.Item2)
        {
            if (coordinateFrom.Item1 > coordinateTo.Item1)
            {
                (coordinateFrom, coordinateTo) = (coordinateTo, coordinateFrom);
            }
            for (int i = coordinateFrom.Item1; i <= coordinateTo.Item1; ++i)
            {
                (int, int) coordinate = (i, coordinateFrom.Item2);
                if (!map.ContainsKey(coordinate))
                {
                    map.Add(coordinate, 1);
                }
                else
                {
                    map[coordinate] += 1;
                }
            }
        }
    }
    private void FillMapColumn(Dictionary<(int, int), int> map, (int, int) coordinateFrom, (int, int) coordinateTo)
    {
        if (coordinateFrom.Item1 == coordinateTo.Item1)
        {
            if (coordinateFrom.Item2 > coordinateTo.Item2)
            {
                (coordinateFrom, coordinateTo) = (coordinateTo, coordinateFrom);
            }
            for (int i = coordinateFrom.Item2; i <= coordinateTo.Item2; ++i)
            {
                (int, int) coordinate = (coordinateFrom.Item1, i);
                if (!map.ContainsKey(coordinate))
                {
                    map.Add(coordinate, 1);
                }
                else
                {
                    map[coordinate] += 1;
                }
            }
        }
    }

    private bool CheckIfStraightLine((int, int) coordinateFrom, (int, int) coordinateTo)
    {
        return coordinateFrom.Item1 == coordinateTo.Item1 || 
               coordinateFrom.Item2 == coordinateTo.Item2;
}

    private void FillDiagonal(Dictionary<(int, int), int> map, (int, int) from, (int, int) to)
    {
        
        if (from.Item1 > to.Item1 && from.Item2 > to.Item2)
        {
            (from, to) = (to, from);
        }

        if (from.Item1 > to.Item1)
        {
            (from, to) = (to, from);
        }

        bool up = (from.Item2 < to.Item2);

        for (int i = 0; i < to.Item1 - from.Item1; ++i)
        {
            (int, int) coordinate = up? (from.Item1 + i, from.Item2 + i) : (from.Item1 + i, from.Item2 - i);
            if (!map.ContainsKey(coordinate))
            {
                map.Add(coordinate, 1);
            }
            else
            {
                map[coordinate] += 1;
            }
        }
    }
    
    private void FillMapDiagonals(string[] input, Dictionary<(int, int), int> map)
    {
        foreach (string line in input)
        {
            ((int, int) coordinateFrom, (int, int) coordinateTo) = StringToCoordinates(line);
            if (!CheckIfStraightLine(coordinateFrom, coordinateTo))
            {
                FillDiagonal(map, coordinateFrom, coordinateTo);
            }
        }
    }
    
    private void FillMapStraightLines(string[] input, Dictionary<(int, int), int> map)
    {
        foreach (var line in input)
        {
            ((int,int) coordinateFrom, (int,int) coordinateTo) = StringToCoordinates(line);
            // Check for a Row
            FillMapRow(map, coordinateFrom, coordinateTo);
            FillMapColumn(map, coordinateFrom, coordinateTo);
        }
    }

    private int CountDangerousPoints(Dictionary<(int, int), int> map)
    {
        int count = 0;
        foreach (var coordinate in map)
        {
            if (coordinate.Value > 1)
            {
                ++count;
            }
        }

        return count;
    }
    public string SolvePartOne(string filePath)
    {
        string[] lines = Util.ParseInput(filePath);
        Dictionary<(int,int),int> map = new Dictionary<(int, int), int>();
        FillMapStraightLines(lines, map);
        // PrintMap(map);

        return CountDangerousPoints(map).ToString();
    }

    private void PrintMap(Dictionary<(int, int), int> map)
    {
        for (int i = 0; i <= 9; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                int num = map.ContainsKey((j, i)) ? map[(j, i)] : 0;
                if (num == 0)
                {
                    Console.Write('.');
                }
                else
                {
                    Console.Write(num);
                }
            }
            Console.Write('\n');
        }
    }
    public string SolvePartTwo(string filePath)
    {
        string[] lines = Util.ParseInput(filePath);
        Dictionary<(int,int),int> map = new Dictionary<(int, int), int>();
        FillMapStraightLines(lines, map);
        FillMapDiagonals(lines, map);

        PrintMap(map);
        return CountDangerousPoints(map).ToString();
    }
}