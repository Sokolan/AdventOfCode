const runner = require("../../utils/runner");
const parseInput = require("../../utils/parseInput");

function getAnthenasLocationMap(locationMatrix) {
  const anthenasLocations = {};
  for (let row = 0; row < locationMatrix.length; row += 1) {
    for (let column = 0; column < locationMatrix.length; column += 1) {
      const anthenaType = locationMatrix[row][column];
      if (anthenaType.match(/[0-9a-zA-Z]/)) {
        if (!anthenasLocations[anthenaType]) {
          anthenasLocations[anthenaType] = new Set();
        }
        anthenasLocations[anthenaType].add([row, column]);
      }
    }
  }
  return anthenasLocations;
}

function calcAntinodeLocation(anthenaA, anthenaB) {
  const [dy, dx] = [anthenaA[0] - anthenaB[0], anthenaA[1] - anthenaB[1]];
  return [anthenaA[0] + dy, anthenaA[1] + dx];
}

function inBoundaries(location, boundaries) {
  return (
    location[0] >= 0 &&
    location[0] < boundaries &&
    location[1] >= 0 &&
    location[1] < boundaries
  );
}

function addAntinodesLocations(
  anthenasLocation,
  antinodeLocationsSet,
  boundaries
) {
  anthenasLocation.forEach((anthenaA, indexA) => {
    anthenasLocation.forEach((anthenaB, indexB) => {
      if (indexA === indexB) return;
      const antinodeLocation = calcAntinodeLocation(anthenaA, anthenaB);
      if (!inBoundaries(antinodeLocation, boundaries)) return;
      antinodeLocationsSet.add(`${antinodeLocation}`);
    });
  });
}

function solvePartOne(inputPath) {
  const input = parseInput(inputPath);
  const locationMatrix = input.map((line) => [...line[0].trim().split("")]);
  const anthenasLocationsMap = getAnthenasLocationMap(locationMatrix);
  const antinodesLocationsSet = new Set();
  Object.values(anthenasLocationsMap).forEach((anthenasLocation) =>
    addAntinodesLocations(anthenasLocation, antinodesLocationsSet, input.length)
  );
  return String(antinodesLocationsSet.size);
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath);
}

const inputPath = __dirname;

const partOneExpected = "14";
const partTwoExpected = "";

runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
