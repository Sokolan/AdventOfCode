const runner = require("../../utils/runner");
const parseInput = require("../../utils/parseInput");
const fs = require("node:fs");

function calcMuls(input) {
  let mulsRes = 0;
  const searchTerm = /mul\(\d{1,3},\d{1,3}\)/g;
  const muls = input.reduce(
    (acc, curr) => acc.concat([...curr.matchAll(searchTerm)]),
    []
  );
  muls.forEach((mul) => {
    const numbers = [...mul[0].matchAll(/\d{1,3}/g)];
    mulsRes += Number.parseInt(numbers[0]) * Number.parseInt(numbers[1]);
  });
  return mulsRes;
}

function solvePartOne(inputPath) {
  const input = parseInput(inputPath);

  let res = 0;
  input.forEach((line) => {
    res += calcMuls(line);
  });
  return String(res);
}

function cleanLine(line, enabled = true) {
  let res = line;
  if (!enabled) {
    const doLocation = res.search(/do\(\)/);
    if (doLocation === -1) return { line: "", enabled: false };

    res = line.slice(doLocation + "do()".length);
    enabled = true;
  }

  // removes from "don't()" to "do()"
  while (res.search(/don\'t\(\)/) !== -1) {
    const from = res.search(/don\'t\(\)/);
    const to = res.search(/do\(\)/) + "do()".length;
    if (to - "do()".length === -1) {
      return { line: res.slice(0, from), enabled: false };
    }
    if (to < from) {
      res = res.replace("do()", "");
      continue;
    }

    res = res.slice(0, from).concat(res.slice(to));
  }

  return { line: res, enabled: true };
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath);
  let enabled = true;
  const cleanInput = input.map((line) =>
    line.map((word) => {
      const res = cleanLine(word, enabled);
      enabled = res.enabled;
      return res.line;
    })
  );
  let res = 0;
  cleanInput.forEach((line) => {
    res += calcMuls(line);
  });
  return String(res);
}

const inputPath = __dirname;

const partOneExpected = "161";
const partTwoExpected = "48";

runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);

// const str = "01don't()dsds";
// console.log(str.search(/don\'t\(\)/));
