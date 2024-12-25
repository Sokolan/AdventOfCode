const runner = require("../../utils/runner");
const parseInput = require("../../utils/parseInput");
const { arrayBuffer } = require("stream/consumers");

function getAntennasLocationMap(locationMatrix) {
  const antennasLocations = new Map();
  const boundary = locationMatrix.length;
  for (let row = 0; row < boundary; row += 1) {
    for (let column = 0; column < boundary; column += 1) {
      const antennaType = locationMatrix[row][column];
      if (antennaType.match(/[0-9a-zA-Z]/)) {
        if (!antennasLocations.has(antennaType)) {
          antennasLocations.set(antennaType, new Set());
        }
        antennasLocations.get(antennaType).add([row, column]);
      }
    }
  }
  return antennasLocations;
}

function calcAntinodeJump(antennaA, antennaB) {
  return [antennaA[0] - antennaB[0], antennaA[1] - antennaB[1]];
}

function calcAntinodeLocation(antennaA, jump) {
  const [dy, dx] = jump;
  return [antennaA[0] + dy, antennaA[1] + dx];
}

function inBoundaries(location, boundaries) {
  return (
    location[0] >= 0 &&
    location[0] < boundaries &&
    location[1] >= 0 &&
    location[1] < boundaries
  );
}

function addAntinodesLocationA(
  antennaA,
  antinodeJump,
  boundaries,
  antinodeLocationsSet
) {
  const antinodeLocation = calcAntinodeLocation(antennaA, antinodeJump);
  if (!inBoundaries(antinodeLocation, boundaries)) return false;
  antinodeLocationsSet.add(`${antinodeLocation}`);
  return true;
}

function addAntinodesLocationsA(
  antennasLocation,
  antinodeLocationsSet,
  boundaries
) {
  antennasLocation.forEach((antennaA, indexA) => {
    antennasLocation.forEach((antennaB, indexB) => {
      if (indexA === indexB) return;
      const antinodeJump = calcAntinodeJump(antennaA, antennaB);
      addAntinodesLocationA(
        antennaA,
        antinodeJump,
        boundaries,
        antinodeLocationsSet
      );
    });
  });
}

function solvePartOne(inputPath) {
  const input = parseInput(inputPath);
  const locationMatrix = input.map((line) => [...line[0].trim().split("")]);
  const antennasLocationsMap = getAntennasLocationMap(locationMatrix);
  const antinodesLocationsSet = new Set();
  antennasLocationsMap.forEach((antennasLocation) =>
    addAntinodesLocationsA(
      antennasLocation,
      antinodesLocationsSet,
      input.length
    )
  );
  return String(antinodesLocationsSet.size);
}

function addAntinodesLocationB(
  antennaA,
  antinodeJump,
  boundaries,
  antinodeLocationsSet
) {
  let antenna = antennaA;
  let antinodeLocation = calcAntinodeLocation(antenna, [0, 0]);
  while (inBoundaries(antinodeLocation, boundaries)) {
    antenna = antinodeLocation;
    antinodeLocationsSet.add(`${antinodeLocation}`);
    antinodeLocation = calcAntinodeLocation(antenna, antinodeJump);
  }
}

function addAntinodesLocationsB(
  antennasLocation,
  antinodeLocationsSet,
  boundaries
) {
  antennasLocation.forEach((antennaA, indexA) => {
    antennasLocation.forEach((antennaB, indexB) => {
      if (indexA === indexB) return;
      const antinodeJump = calcAntinodeJump(antennaA, antennaB);
      addAntinodesLocationB(
        antennaA,
        antinodeJump,
        boundaries,
        antinodeLocationsSet
      );
    });
  });
}

function solvePartTwo(inputPath) {
  const input = parseInput(inputPath);
  const locationMatrix = input.map((line) => [...line[0].trim().split("")]);
  const antennasLocationsMap = getAntennasLocationMap(locationMatrix);
  const antinodesLocationsSet = new Set();
  antennasLocationsMap.forEach((antennasLocation) =>
    addAntinodesLocationsB(
      antennasLocation,
      antinodesLocationsSet,
      input.length
    )
  );
  const arr = [];
  antinodesLocationsSet.forEach((location) => {
    arr.push(location.split(",").map((_) => Number.parseInt(_)));
  });

  return String(antinodesLocationsSet.size);
}

const inputPath = __dirname;

// 413
const partOneExpected = "14";
const partTwoExpected = "34";

runner(solvePartOne, partOneExpected, solvePartTwo, partTwoExpected, inputPath);
