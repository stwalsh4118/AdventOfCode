import * as fs from "fs";
import * as util from "util";

util.inspect.defaultOptions.maxArrayLength = null;

const ALPHABET = "abcdefghijklmnopqrstuvwxyz";

class Position {
	elevation: number;
	label: string;
	visited: boolean;

	constructor(label: string) {
		this.elevation = label === "S" ? 0 : label === "E" ? 25 : ALPHABET.indexOf(label);

		this.label = label;

		this.visited = false;
	}
}

class Path {
	positions: Position[] = [];
}

class Map {
	positions: Position[][];

	paths: Path[];

	constructor(positions: Position[][]) {
		this.positions = positions;
	}
}
