const runner = require("../../utils/runner");
const parseInput = require("../../utils/parseInput");

function inBoundaries(matrix, x, y) {
  return x >= 0 && y >= 0 && y < matrix.length && x < matrix[y].length;
}

const moves = [
  [1, 0],
  [0, 1],
  [-1, 0],
  [0, -1],
];

function calculateFencePrice(gardenPlots, y, x, visitedPlots) {
  visitedPlots[y][x] = true;
  let diameter = 4;
  let area = 1;
  moves.forEach((move) => {
    const [newY, newX] = [y + move[0], x + move[1]];
    if (
      !inBoundaries(gardenPlots, newY, newX) ||
      gardenPlots[y][x] !== gardenPlots[newY][newX]
    ) {
      return;
    }
    diameter -= 1;
    if (visitedPlots[newY][newX]) return;
    const [subArea, subDiameter] = calculateFencePrice(
      gardenPlots,
      newY,
      newX,
      visitedPlots
    );
    area += subArea;
    diameter += subDiameter;
  });
  return [area, diameter];
}

function calculateFencesPrice(gardenPlots) {
  let price = 0;
  const visited = gardenPlots.map((_) => _.map((_) => false));
  for (let row = 0; row < visited.length; row += 1) {
    for (let column = 0; column < visited[row].length; column += 1) {
      if (visited[row][column]) continue;
      const [area, diameter] = calculateFencePrice(
        gardenPlots,
        row,
        column,
        visited
      );
      price += area * diameter;
    }
  }
  return price;
}

function solvePartOne(inputPath) {
  const input = parseInput(inputPath).map((_) => _[0].split(""));
  const price = calculateFencesPrice(input);
  return String(price);
}

function solvePartTwo(inputPath) {
  // return String();
}

const inputPath = __dirname;

const partOneExpected = "1930";
const partTwoExpected = "";

runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
