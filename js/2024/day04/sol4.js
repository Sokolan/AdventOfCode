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
      for (let index = 0 ; index < word.length ; index += 1) {
        const x = location.x + (horizontal * index);
        const y = location.y + (verical * index);
        if (!checkBoundaries(matrix, x, y)) break;
        if (word[index] !== matrix[x][y]) break;
        if (index === (word.length - 1)) count += 1;
      }
    }
  }
  return count;
}

function solvePartOne(inputPath) {
  const input = parseInput(inputPath);
  const inputMatrix = input.map((line) => line[0].split(""));
  const res = inputMatrix.reduce((acc, currLine, x) => acc + currLine.reduce((acc, currCell, y) => 
  acc + countWordsAt(inputMatrix, "XMAS", {x, y}), 0), 0);
  
  return String(res);
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath);
}

const inputPath = __dirname;

const partOneExpected = "18";
const partTwoExpected = "";
runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
