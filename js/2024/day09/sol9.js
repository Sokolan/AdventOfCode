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

function moveFile(filesystemArr, fileToMoveIndex, emptyIndex, fillData) {
  while (emptyIndex < fileToMoveIndex) {
    const toMoveFile = filesystemArr[fileToMoveIndex];

    if (filesystemArr[emptyIndex] >= toMoveFile) {
      if (!fillData[emptyIndex]) fillData[emptyIndex] = [];
      fillData[emptyIndex].push({
        fileID: fileToMoveIndex / 2,
        size: toMoveFile,
      });
      fillData[fileToMoveIndex] = {
        fileID: 0,
        size: toMoveFile,
      };
      filesystemArr[emptyIndex] -= toMoveFile;
      filesystemArr[fileToMoveIndex] = 0;
      return;
    }
    emptyIndex += 2;
  }
}

function filesMover(filesystemArr) {
  const fillData = Array(Math.floor(filesystemArr.length)).fill(null);
  let emptyIndex = 1;
  let fileToMoveIndex =
    (filesystemArr.length - 1) % 2 === 0
      ? filesystemArr.length - 1
      : filesystemArr.length - 2;
  while (fileToMoveIndex > 0) {
    moveFile(filesystemArr, fileToMoveIndex, emptyIndex, fillData);
    if (filesystemArr[emptyIndex] === 0) {
      emptyIndex += 2;
    }
    fileToMoveIndex -= 2;
  }
  return fillData;
}

function calcChecksumMoved(filesystemArr, fillData) {
  let position = 0;
  return (checkSum = filesystemArr.reduce((checkSum, currentBlock, index) => {
    if (index % 2 === 0) {
      if (fillData[index]) {
        position += fillData[index].size;
      }
      checkSum += sumN(position, currentBlock) * (index / 2);
      position += currentBlock;
    } else {
      if (!fillData[index]) {
        position += filesystemArr[index];
        return checkSum;
      }
      fillData[index].forEach((movedFile) => {
        if (!movedFile) return;
        checkSum += sumN(position, movedFile.size) * movedFile.fileID;
        position += movedFile.size;
      });
      position += filesystemArr[index];
    }
    return checkSum;
  }, 0));
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath)[0][0];
  const inputArray = input.split("").map((_) => Number.parseInt(_));
  const fillData = filesMover(inputArray);
  const checkSum = calcChecksumMoved(inputArray, fillData);
  return String(checkSum);
}

const inputPath = __dirname;

const partOneExpected = "1928";
const partTwoExpected = "2858";

runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
