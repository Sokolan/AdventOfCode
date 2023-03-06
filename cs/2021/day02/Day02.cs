namespace AdvantOfCode.day02;

public class Day02 : Solution
{
    private class DirectionVector
    {
        public string Direction { get; set; }
        public int Velocity { get; set; }

        public DirectionVector(string line)
        {
            Direction = line.Split(" ")[0];
            Velocity = int.Parse(line.Split(" ")[1]);
        }
    }
    private string[] ParseInput(string filePath)
    {
        string lines = File.ReadAllText(filePath);
        string[] directions = lines.Split(new[] { "\r\n", "\r", "\n" }, StringSplitOptions.RemoveEmptyEntries);
        return directions;
    }

    private (int, int) CalculatePosition(string[] directions)
    {
        int depth = 0;
        int horizontal = 0;
        foreach(string direction in directions)
        {
            DirectionVector directionVector = new DirectionVector(direction);
            if (directionVector.Direction == "up")
            {
                depth -= directionVector.Velocity;
            }
            else if (directionVector.Direction == "down")
            {
                depth += directionVector.Velocity;
            }
            else if (directionVector.Direction == "forward")
            {
                horizontal += directionVector.Velocity;
            }
        }

        return (depth, horizontal);
    }
    
    private (int, int) CalculatePositionWithAim(string[] directions)
    {
        int depth = 0;
        int aim = 0;
        int horizontal = 0;
        foreach(string direction in directions)
        {
            DirectionVector directionVector = new DirectionVector(direction);
            if (directionVector.Direction == "up")
            {
                aim -= directionVector.Velocity;
            }
            else if (directionVector.Direction == "down")
            {
                aim += directionVector.Velocity;
            }
            else if (directionVector.Direction == "forward")
            {
                horizontal += directionVector.Velocity;
                depth += directionVector.Velocity * aim;
            }
        }

        return (depth, horizontal);
    }

    public string SolvePartOne(string filePath)
    {
        string[] directions = ParseInput(filePath);
        var (depth, horizontal) = CalculatePosition(directions);
        return (depth * horizontal).ToString();
    }

    public string SolvePartTwo(string filePath)
    {
        string[] directions = ParseInput(filePath);
        var (depth, horizontal) = CalculatePosition(directions);
        return (depth * horizontal).ToString();
    }
}