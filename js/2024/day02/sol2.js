const runner = require("../../utils/runner");
const parseInput = require("../../utils/parseInput");

function solvePartOne(inputPath) {
  const input = parseInput(inputPath);
  let safeLists = 0;
  input.forEach((report) => {
    if (report.length <= 1) {
      safeLists += 1;
      return;
    }
    const ascOrDesc =
      Number.parseInt(report[1]) > Number.parseInt(report[0]) ? "asc" : "desc";
    if (
      report.every((_, index) => {
        if (Number.parseInt(index) === 0) return true;
        const distance =
          Number.parseInt(report[index]) - Number.parseInt(report[index - 1]);
        if (ascOrDesc === "asc") {
          return distance >= 1 && distance <= 3;
        }
        return distance <= -1 && distance >= -3;
      })
    ) {
      safeLists += 1;
    }
  });
  return String(safeLists);
}

function checkReportValidity(report) {
  if (report.length <= 1) {
    safeLists += 1;
    return;
  }
  let failIndex = 0;
  const ascOrDesc =
    Number.parseInt(report[1]) > Number.parseInt(report[0]) ? "asc" : "desc";
  if (
    report.every((_, index) => {
      if (index === 0) return true;

      const distance =
        Number.parseInt(report[index]) - Number.parseInt(report[index - 1]);
      if (ascOrDesc === "asc") {
        if (distance < 1 && distance > 3) return false;
      }
      return distance <= -1 && distance >= -3;
    })
  ) {
    safeLists += 1;
  }
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath);
  let safeLists = 0;
  input.forEach((report) => {});
  return String(safeLists);
}

const inputPath = __dirname;

const partOneExpected = "2";
const partTwoExpected = "4";

runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
