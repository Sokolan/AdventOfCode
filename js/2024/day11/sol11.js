const runner = require("../../utils/runner");
const parseInput = require("../../utils/parseInput");

function splitStone(stone) {
  return [
    String(Number.parseInt(stone.slice(stone.length / 2))),
    stone.slice(0, stone.length / 2),
  ];
}

function makeMoves(stones, numberOfMoves) {
  let stonesArray = stones.slice();
  for (let i = 0; i < numberOfMoves; i += 1) {
    const newStones = [];
    stonesArray.forEach((stone, index) => {
      if (stone.localeCompare("0") === 0) {
        stonesArray[index] = "1";
      } else if (stone.length % 2 === 0) {
        const [leftStone, rightStone] = splitStone(stone);
        newStones.push(leftStone);
        stonesArray[index] = rightStone;
      } else {
        stonesArray[index] = String(Number.parseInt(stone) * 2024);
      }
    });
    stonesArray = stonesArray.concat(newStones);
  }
  return stonesArray;
}

function solvePartOne(inputPath) {
  const input = parseInput(inputPath)[0];
  const numberOfStones = makeMoves(input, 25).length;
  return String(numberOfStones);
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath);
}

const inputPath = __dirname;

const partOneExpected = "55312";
const partTwoExpected = "";

runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
