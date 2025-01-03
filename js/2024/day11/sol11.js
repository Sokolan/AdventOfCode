const runner = require("../../utils/runner");
const parseInput = require("../../utils/parseInput");

function splitStone(stone) {
  return [
    String(Number.parseInt(stone.slice(stone.length / 2))),
    stone.slice(0, stone.length / 2),
  ];
}

function addStonesToMap(stonesMap, stone, stonesToAdd) {
  const currentStonesCount = stonesMap.get(stone);
  if (!currentStonesCount) {
    stonesMap.set(stone, stonesToAdd);
  } else {
    stonesMap.set(stone, currentStonesCount + stonesToAdd);
  }
}

function countStonesInMap(stonesMap) {
  let stonesCount = 0;
  stonesMap.forEach(
    (stoneCount) => (stonesCount += Number.parseInt(stoneCount))
  );
  return stonesCount;
}

function makeMoves(stones, numberOfMoves) {
  let stonesMap = new Map();
  stones.forEach((stone) => {
    stonesMap.set(stone, 1);
  });
  for (let i = 0; i < numberOfMoves; i += 1) {
    const tmpMap = new Map();
    stonesMap.forEach((stonesCount, stone) => {
      if (stone.localeCompare("0") === 0) {
        addStonesToMap(tmpMap, "1", stonesCount);
      } else if (stone.length % 2 === 0) {
        const [leftStone, rightStone] = splitStone(stone);
        addStonesToMap(tmpMap, leftStone, stonesCount);
        addStonesToMap(tmpMap, rightStone, stonesCount);
      } else {
        const stone2024 = String(Number.parseInt(stone) * 2024);
        addStonesToMap(tmpMap, stone2024, stonesCount);
      }
    });
    stonesMap = tmpMap;
  }
  return countStonesInMap(stonesMap);
}

function solvePartOne(inputPath) {
  const input = parseInput(inputPath)[0];
  const numberOfStones = makeMoves(input, 25);
  return String(numberOfStones);
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath)[0];
  const numberOfStones = makeMoves(input, 75);
  return String(numberOfStones);
}

const inputPath = __dirname;

const partOneExpected = "55312";
const partTwoExpected = "65601038650482";

runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
