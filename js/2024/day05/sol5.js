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

function findViolation(updates, rules) {
  const violation = [];
  for (let i = 0; i < updates.length; i += 1) {
    for (let j = i + 1; j < updates.length; j += 1) {
      if (
        rules.find((rule) => rule[0] === updates[j] && rule[1] === updates[i])
      ) {
        return [i, j];
      }
    }
  }
  return [-1, -1];
}

function solvePartOne(inputPath) {
  const input = parseInput(inputPath);
  const rules = getRules(input);
  const updatesList = getUpdates(input);
  let middleSum = 0;
  updatesList.forEach((updates) => {
    if (!checkViolation(updates, rules)) return;
    middleSum += Number.parseInt(updates[Math.floor(updates.length / 2)]);
  });
  return String(middleSum);
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath);
  const rules = getRules(input);
  const updates = getUpdates(input);
  let middleSum = 0;
  updates.forEach((update) => {
    if (checkViolation(update, rules)) return;
    const fixedUpdate = update;
    do {
      const violation = findViolation(update, rules);
      [fixedUpdate[violation[1]], fixedUpdate[violation[0]]] = [
        fixedUpdate[violation[0]],
        fixedUpdate[violation[1]],
      ];
    } while (!checkViolation(fixedUpdate, rules));
    middleSum += Number.parseInt(
      fixedUpdate[Math.floor(fixedUpdate.length / 2)]
    );
  });
  return String(middleSum);
}

const inputPath = __dirname;

const partOneExpected = "143";
const partTwoExpected = "123";
runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
