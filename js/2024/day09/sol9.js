const runner = require("../../utils/runner");
const parseInput = require("../../utils/parseInput");

function sumN(start, length) {
  return (length * (2 * start + (length - 1))) / 2;
}

function fillEmptySpace(
  filesystemArr,
  position,
  indexOfEmptySpace,
  paddingIndex
) {
  let checkSum = 0;
  let toPad = filesystemArr[indexOfEmptySpace];
  while (toPad > 0) {
    if (paddingIndex < indexOfEmptySpace) return [checkSum, paddingIndex];

    if (filesystemArr[paddingIndex] >= toPad) {
      filesystemArr[paddingIndex] -= toPad;
      return [
        checkSum + sumN(position, toPad) * (paddingIndex / 2),
        paddingIndex,
      ];
    }
    checkSum +=
      sumN(position, filesystemArr[paddingIndex]) * (paddingIndex / 2);
    position += filesystemArr[paddingIndex];

    toPad -= filesystemArr[paddingIndex];
    paddingIndex -= 2;
  }
}

function calcChecksum(filesystemArr) {
  let position = 0;
  let index = 0;
  let paddingIndex = filesystemArr.length - 1;
  let checkSum = 0;

  while (index <= paddingIndex) {
    if (index % 2 === 0) {
      checkSum += sumN(position, filesystemArr[index]) * (index / 2);
    } else {
      if (filesystemArr[index] <= filesystemArr[paddingIndex]) {
        filesystemArr[paddingIndex] -= filesystemArr[index];
        checkSum += sumN(position, filesystemArr[index]) * (paddingIndex / 2);
      } else {
        const [sum, pad] = fillEmptySpace(
          filesystemArr,
          position,
          index,
          paddingIndex
        );
        checkSum += sum;
        paddingIndex = pad;
      }
    }
    const fsai = filesystemArr[index];
    position += filesystemArr[index];
    index += 1;
  }
  return checkSum;
}

function solvePartOne(inputPath) {
  const input = parseInput(inputPath)[0][0];
  const inputArray = input.split("").map((_) => Number.parseInt(_));
  return String(calcChecksum(inputArray));
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath);
}

const inputPath = __dirname;

const partOneExpected = "1928";
const partTwoExpected = "";

runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
