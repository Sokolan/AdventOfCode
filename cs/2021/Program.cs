using AdvantOfCode;

int dayNumber = 5; 
int partToRun = 2;
string expectedSolPartOne = "5";
string expectedSolPartTwo = "12";

// Construct the name of the class using string interpolation
string className = $"AdvantOfCode.day{dayNumber:D2}.Day{dayNumber:D2}";

// Get the Type object for the class
var classType = Type.GetType(className);

// Create an instance of the class using reflection
var solution = (Solution)Activator.CreateInstance(classType);

Util util = new Util(dayNumber);
if (partToRun == 1)
{
    util.RunPart(solution, partToRun, expectedSolPartOne);
}
else
{
    util.RunPart(solution, partToRun, expectedSolPartTwo);
}