const runner = require("../../utils/runner");
const parseInput = require("../../utils/parseInput");
const { count } = require("console");

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
  if (isSumLegalRec(sum, accSum + numbersList[index], index + 1, numbersList))
    return true;
  if (isSumLegalRec(sum, accSum * numbersList[index], index + 1, numbersList))
    return true;
  return false;
}

function isSumLegal(sum, numbersList) {
  return isSumLegalRec(sum, numbersList[0], 1, numbersList);
}

function countLegalSums(sums, numbersList) {
  let legalSums = 0;
  sums.forEach((sum, index) => {
    if (isSumLegal(sum, numbersList[index])) legalSums += sum;
  });
  return legalSums;
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
