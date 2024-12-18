function resultChecker(part, result, expected) {
  const input_path = process.cwd();

  if (result.localeCompare(expected) === 0) {
    console.log(`PART ${part} TEST PASSED`);
    return true;
  } else {
    console.log(`Part ${part} test failed:\n
            Expected result: ${expected}\n
            Actual result: ${result}`);
  }
  return false;
}

function runner(
  partOneSolver,
  partOneExpected,
  partTwoSolver,
  partTwoExpected,
  path
) {
  const resultPartOne = partOneSolver(`${path}/test.txt`);

  if (resultChecker(1, resultPartOne, partOneExpected)) {
    console.log(`Part one solution: ${partOneSolver(`${path}/input.txt`)}`);
  }
  
  const resultPartTwo = partTwoSolver(`${path}/test.txt`);
  if (!resultPartTwo) return;
  if (resultChecker(2, resultPartTwo, partTwoExpected)) {
    console.log(`Part two solution: ${partTwoSolver(`${path}/input.txt`)}`);
  }
}

module.exports = runner;
