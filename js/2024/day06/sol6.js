const runner = require("../../utils/runner");
const parseInput = require("../../utils/parseInput");

function findGuard(matrix) {
  for (let y = 0; y < matrix.length; y += 1) {
    for (let x = 0; x < matrix[y].length; x += 1) {
      if (matrix[y][x] === "^") {
        return [y, x];
      }
    }
  }
  return [-1, -1];
}

function inBoundaries(matrix, y, x) {
  return x >= 0 && y >= 0 && y < matrix.length && x < matrix[y].length;
}

function getNewDirection(direction) {
  switch (direction) {
    case "u":
      return "r";
    case "r":
      return "d";
    case "d":
      return "l";
    case "l":
      return "u";
    default:
      return "ERROR";
  }
}

function getNextLocation(matrix, guardLocation, direction) {
  let [y, x] = guardLocation;
  let [yUpdate, xUpdate] = [y, x];
  switch (direction) {
    case "u":
      yUpdate = y - 1;
      break;
    case "d":
      yUpdate = y + 1;
      break;
    case "r":
      xUpdate = x + 1;
      break;
    case "l":
      xUpdate = x - 1;
      break;
    default:
      console.log("DIRECTION ERROR");
  }
  if (!inBoundaries(matrix, yUpdate, xUpdate))
    return [yUpdate, xUpdate, direction];
  if (matrix[yUpdate][xUpdate] === "." || matrix[yUpdate][xUpdate] === "X")
    return [yUpdate, xUpdate, direction];
  if (matrix[yUpdate][xUpdate] === "#")
    return [y, x, getNewDirection(direction)];

  return [-1, -1, "ERROR"];
}

function updateMatrix(matrix, guardLocation) {
  const [y, x] = guardLocation;
  if (matrix[y][x] === ".") matrix[y][x] = "X";
}

function countVisits(matrix, mark) {
  return matrix.reduce(
    (acc, line) =>
      acc +
      line.reduce(
        (accCell, cell) => (cell === mark ? accCell + 1 : accCell),
        0
      ),
    0
  );
}

function solvePartOne(inputPath) {
  const input = parseInput(inputPath);
  const matrix = input.map((line) => line[0].split(""));
  let [y, x] = findGuard(matrix);
  matrix[y][x] = "X";
  let direction = "u";
  if (x === -1 && y === -1) return "ERROR";

  while (inBoundaries(matrix, y, x)) {
    updateMatrix(matrix, [y, x]);
    [y, x, direction] = getNextLocation(matrix, [y, x], direction);
  }
  return String(countVisits(matrix, "X"));
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath);
}

const inputPath = __dirname;

const partOneExpected = "41";
const partTwoExpected = "";

runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
