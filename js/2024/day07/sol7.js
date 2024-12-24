const runner = require("../../utils/runner");
const parseInput = require("../../utils/parseInput");

function getSumsAndNumbers(input) {
  const sums = [];
  const numbersLists = [];
  input.forEach((line) => {
    sums.push(Number.parseInt(line[0].slice(0, -1)));
    numbersLists.push(line.slice(1).map((number) => Number.parseInt(number)));
  });
  return [sums, numbersLists];
}

function isSumLegalRec(sum, accSum, index, numbersList, operators) {
  if (index === numbersList.length) {
    return sum === accSum;
  }
  if (accSum > sum) return false;
  return operators.some((operator) =>
    isSumLegalRec(
      sum,
      operator(accSum, numbersList[index]),
      index + 1,
      numbersList,
      operators
    )
  );
}

function isSumLegal(sum, numbersList, operators) {
  return isSumLegalRec(sum, numbersList[0], 1, numbersList, operators);
}

function countLegalSums(sums, numbersList, operators) {
  return sums.reduce(
    (accSum, sum, index) =>
      isSumLegal(sum, numbersList[index], operators) ? (accSum += sum) : accSum,
    0
  );
}

function solvePartOne(inputPath) {
  const input = parseInput(inputPath);
  const operators = [(a, b) => a + b, (a, b) => a * b];

  const [sums, numbersLists] = getSumsAndNumbers(input);
  return String(countLegalSums(sums, numbersLists, operators));
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath);
  const operators = [
    (a, b) => a + b,
    (a, b) => a * b,
    (a, b) => Number.parseInt(String(a) + String(b)),
  ];

  const [sums, numbersLists] = getSumsAndNumbers(input);
  return String(countLegalSums(sums, numbersLists, operators));
}

const inputPath = __dirname;

const partOneExpected = "3749";
const partTwoExpected = "11387";

runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
