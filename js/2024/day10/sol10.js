const runner = require("../../utils/runner");
const parseInput = require("../../utils/parseInput");

function getStartLocations(topographicMap) {
  const startLocations = [];
  topographicMap.forEach((row, rowIndex) =>
    row.forEach((height, columnIndex) => {
      if (height === 0) startLocations.push({ rowIndex, columnIndex });
    })
  );
  return startLocations;
}

const moves = [
  [1, 0],
  [0, 1],
  [-1, 0],
  [0, -1],
];

function checkBoundaries(topographicMap, y, x) {
  return (
    y >= 0 &&
    x >= 0 &&
    y < topographicMap.length &&
    x < topographicMap[y].length
  );
}

function trailheadScore(topographicMap, y, x, goalHeight, locationsFound) {
  if (topographicMap[y][x] === goalHeight)
    return locationsFound.add(`${y}|${x}`);
  moves.forEach((move) => {
    const [newY, newX] = [move[0] + y, move[1] + x];
    if (
      !checkBoundaries(topographicMap, newY, newX) ||
      topographicMap[newY][newX] - topographicMap[y][x] !== 1
    )
      return;
    trailheadScore(topographicMap, newY, newX, goalHeight, locationsFound);
  });
}

function countTrailheadsScores(topographicMap) {
  const startPoints = getStartLocations(topographicMap);

  return startPoints.reduce((acc, currentStart) => {
    const goalHeightSet = new Set();
    trailheadScore(
      topographicMap,
      currentStart.rowIndex,
      currentStart.columnIndex,
      9,
      goalHeightSet
    );
    return acc + goalHeightSet.size;
  }, 0);
}

function trailheadRating(topographicMap, y, x, goalHeight) {
  if (topographicMap[y][x] === goalHeight) return 1;
  return moves.reduce((acc, move) => {
    const [newY, newX] = [move[0] + y, move[1] + x];
    if (
      !checkBoundaries(topographicMap, newY, newX) ||
      topographicMap[newY][newX] - topographicMap[y][x] !== 1
    )
      return acc;
    return acc + trailheadRating(topographicMap, newY, newX, goalHeight);
  }, 0);
}

function countTrailheadsRating(topographicMap) {
  const startPoints = getStartLocations(topographicMap);

  return startPoints.reduce((acc, currentStart) => {
    return (
      acc +
      trailheadRating(
        topographicMap,
        currentStart.rowIndex,
        currentStart.columnIndex,
        9
      )
    );
  }, 0);
}

function solvePartOne(inputPath) {
  const input = parseInput(inputPath);
  const inputMatrix = input.map((_) =>
    _[0].split("").map((_) => Number.parseInt(_))
  );
  const trailheadsScores = countTrailheadsScores(inputMatrix);
  return String(trailheadsScores);
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath);
  const inputMatrix = input.map((_) =>
    _[0].split("").map((_) => Number.parseInt(_))
  );
  const trailheadsScores = countTrailheadsRating(inputMatrix);
  return String(trailheadsScores);
}

const inputPath = __dirname;

const partOneExpected = "36";
const partTwoExpected = "81";

runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
