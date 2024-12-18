const runner = require("../../utils/runner");
const parseInput = require("../../utils/parseInput");

function solvePartOne(inputPath) {
  const input = parseInput(inputPath);
  const lists = [[], []];
  input.forEach((line) => {
    lists[0].push(Number.parseInt(line[0]));
    lists[1].push(Number.parseInt(line[1]));
  });
  lists.forEach((list) => list.sort((a, b) => a - b));
  const res = lists[0].reduce(
    (acc, cur, index) => acc + Math.abs(lists[0][index] - lists[1][index]),
    0
  );
  return String(res);
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath);
  const lists = [[], []];
  input.forEach((line) => {
    lists[0].push(Number.parseInt(line[0]));
    lists[1].push(Number.parseInt(line[1]));
  });
  let res = 0;
  lists[0].forEach((number) => {
    res += lists[1].filter((val) => val === number).length * number;
  });
  return String(res);
}

const inputPath = __dirname;

const partOneExpected = "11";
const partTwoExpected = "31";

runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
