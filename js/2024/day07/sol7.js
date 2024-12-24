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

function isSumLegalRec(sum, accSum, index, numbersList) {
  if (index === numbersList.length) {
    return sum === accSum;
  }
  return (
    isSumLegalRec(sum, accSum + numbersList[index], index + 1, numbersList) ||
    isSumLegalRec(sum, accSum * numbersList[index], index + 1, numbersList)
  );
}

function isSumLegal(sum, numbersList) {
  return isSumLegalRec(sum, numbersList[0], 1, numbersList);
}

function countLegalSums(sums, numbersList) {
  return sums.reduce(
    (accSum, sum, index) =>
      isSumLegal(sum, numbersList[index]) ? (accSum += sum) : accSum,
    0
  );
}

function solvePartOne(inputPath) {
  const input = parseInput(inputPath);

  const [sums, numbersLists] = getSumsAndNumbers(input);
  return String(countLegalSums(sums, numbersLists));
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath);
}

const inputPath = __dirname;

const partOneExpected = "3749";
const partTwoExpected = "";

runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
