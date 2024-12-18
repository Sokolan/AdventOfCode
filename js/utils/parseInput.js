const fs = require("node:fs");

function parseInput(file_path) {
  try {
    const parsedInput = fs.readFileSync(file_path, "utf8").trim().split("\n");
    return parsedInput.map((line) => line.split(/\s+/));
  } catch (err) {
    console.log(err);
  }
}

module.exports = parseInput;
