const runner = require("../../utils/runner");
const parseInput = require("../../utils/parseInput");

function checkBoundaries(matrix, x, y) {
  if (x < 0 || y < 0) return false;
  if (x >= matrix.length || y >= matrix[x].length) return false;
  return true;
}

function countWordsAt(matrix, word, location) {
  let count = 0;
  for (let horizontal = -1; horizontal <= 1; horizontal += 1) {
    for (let verical = -1; verical <= 1; verical += 1) {
      for (let index = 0; index < word.length; index += 1) {
        const x = location.x + horizontal * index;
        const y = location.y + verical * index;
        if (!checkBoundaries(matrix, x, y)) break;
        if (word[index] !== matrix[x][y]) break;
        if (index === word.length - 1) count += 1;
      }
    }
  }
  return count;
}

function solvePartOne(inputPath) {
  const input = parseInput(inputPath);
  const inputMatrix = input.map((line) => line[0].split(""));
  const res = inputMatrix.reduce(
    (acc, currLine, x) =>
      acc +
      currLine.reduce(
        (acc, currCell, y) => acc + countWordsAt(inputMatrix, "XMAS", { x, y }),
        0
      ),
    0
  );

  return String(res);
}

function checkXmas(matrix, location) {
  const [x, y] = location;
  let letters = "";
  if (matrix[x][y] !== "A") return false;
  for (let horizontal = -1; horizontal <= 1; horizontal += 2) {
    for (let vertical = -1; vertical <= 1; vertical += 2) {
      if (!checkBoundaries(matrix, x + horizontal, y + vertical)) return false;
    }
  }
  const verticeA = matrix[x - 1][y - 1] + matrix[x + 1][y + 1];
  const verticeB = matrix[x - 1][y + 1] + matrix[x + 1][y - 1];
  if (verticeA !== "MS" && verticeA !== "SM") return false;
  if (verticeB !== "MS" && verticeB !== "SM") return false;
  return true;
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath);
  const inputMatrix = input.map((line) => line[0].split(""));
  const res = inputMatrix.reduce(
    (acc, currLine, x) =>
      acc +
      currLine.reduce(
        (acc, currCell, y) => acc + checkXmas(inputMatrix, [x, y]),
        0
      ),
    0
  );
  return String(res);
}

const inputPath = __dirname;

const partOneExpected = "18";
const partTwoExpected = "9";

runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
