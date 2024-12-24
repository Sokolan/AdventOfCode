const runner = require("../../utils/runner");
const parseInput = require("../../utils/parseInput");
const { dir } = require("console");

const directionMap = {
  u: [-1, 0],
  d: [1, 0],
  r: [0, 1],
  l: [0, -1],
};

const nextDirection = {
  u: "r",
  r: "d",
  d: "l",
  l: "u",
};

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

function getNextLocation(matrix, guardLocation, direction) {
  let [y, x] = guardLocation;
  let [dy, dx] = directionMap[direction];

  if (!inBoundaries(matrix, y + dy, x + dx)) return [y + dy, x + dx, direction];
  else if (matrix[y + dy][x + dx] === "." || matrix[y + dy][x + dx] === "X")
    return [y + dy, x + dx, direction];
  else if (matrix[y + dy][x + dx] === "#")
    return [y, x, nextDirection[direction]];

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

function markGuardMoves(matrix) {
  let [y, x] = findGuard(matrix);
  if (y === -1 && x === -1) return console.log("ERROR GUARD NOT FOUND");
  matrix[y][x] = "X";

  let direction = "u";

  while (inBoundaries(matrix, y, x)) {
    updateMatrix(matrix, [y, x]);
    [y, x, direction] = getNextLocation(matrix, [y, x], direction);
  }
}

function solvePartOne(inputPath) {
  const input = parseInput(inputPath);
  const matrix = input.map((line) => line[0].split(""));

  markGuardMoves(matrix);

  return String(countVisits(matrix, "X"));
}

function makeDirectionsMatrix(matrix) {
  return Array(matrix.length)
    .fill(null)
    .map(() =>
      Array(matrix[0].length)
        .fill(null)
        .map(() => Array().fill(null))
    );
}

function hasDuplication(directions) {
  const directionsSet = new Set();
  // have a duplication if not all elements distinct
  return directions.some((direction) => {
    if (directionsSet.has(direction)) return true;
    directionsSet.add(direction);
    return false;
  });
}
function checkForCycle(matrix, guardLocation) {
  const visitedCells = new Set();
  let [y, x] = guardLocation;
  if (y === -1 && x === -1) return console.log("ERROR GUARD NOT FOUND");
  matrix[y][x] = "X";

  let direction = "u";

  while (inBoundaries(matrix, y, x)) {
    const guardVisit = `${y}|${x}|${direction}`;
    if (visitedCells.has(guardVisit)) return true;
    visitedCells.add(guardVisit);
    [y, x, direction] = getNextLocation(matrix, [y, x], direction);
  }
  return false;
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath);
  const matrix = input.map((line) => line[0].split(""));
  const guardLocation = findGuard(matrix);
  const guardVisits = matrix.map((row) => [...row]);
  markGuardMoves(guardVisits);

  let countCycles = 0;

  for (let obstacleY = 0; obstacleY < matrix.length; obstacleY += 1) {
    for (let obstacleX = 0; obstacleX < matrix[0].length; obstacleX += 1) {
      const currentElement = matrix[obstacleY][obstacleX];
      if (currentElement === "#" || currentElement === "^") continue;
      if (guardVisits[obstacleY][obstacleX] === "X") {
        matrix[obstacleY][obstacleX] = "#";
        if (checkForCycle(matrix, guardLocation)) countCycles += 1;
        matrix[obstacleY][obstacleX] = ".";
      }
    }
  }
  return String(countCycles);
}

const inputPath = __dirname;

// 5564
const partOneExpected = "41";
// 1976
const partTwoExpected = "6";

runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
