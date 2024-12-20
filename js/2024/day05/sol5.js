const runner = require("../../utils/runner");
const parseInput = require("../../utils/parseInput");
const { listenerCount } = require("process");

function getRules(input) {
  const rules = [];
  input.forEach((line) => {
    if (line[0].search(/\|/) === -1) {
      return;
    }
    rules.push(line[0].split("|"));
  });
  return rules;
}

function getUpdates(input) {
  const updates = [];
  input.forEach((line) => {
    if (line[0].search(/\|/) !== -1) return;
    if (line[0].trim().length === 0) return;

    updates.push(line[0].split(","));
  });
  return updates;
}

function checkViolation(update, rules) {
  const seen = [];
  return update.every((pageUpdate) => {
    const pageUpdateRules = rules.filter((rule) => rule[0] === pageUpdate);
    const pageUpdateValidity = seen.every(
      (seenUpdate) =>
        !pageUpdateRules.find((updateRule) => updateRule[1] === seenUpdate)
    );
    if (!pageUpdateValidity) return false;
    seen.push(pageUpdate);
    return true;
  });
}

function solvePartOne(inputPath) {
  const input = parseInput(inputPath);
  const rules = getRules(input);
  const updates = getUpdates(input);
  let middleSum = 0;
  updates.forEach((update) => {
    if (!checkViolation(update, rules)) return;
    middleSum += Number.parseInt(update[Math.floor(update.length / 2)]);
  });
  return String(middleSum);
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath);
}

const inputPath = __dirname;

const partOneExpected = "143";
const partTwoExpected = "";
runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
