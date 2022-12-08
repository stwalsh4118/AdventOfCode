import * as fs from "fs";
import { faker } from "@faker-js/faker";

class Tree {
	constructor(height, id) {
		this.height = height;
		this.id = id;
	}
}

class Forest {
	constructor(treesLines) {
		this.trees = treesLines.map((line) =>
			line.split("").map((height) => new Tree(height, faker.datatype.uuid()))
		);

		this.width = this.trees[0].length;
		this.height = this.trees.length;

		const visibleTrees = [];
		const scenicScores = [];

		for (let y = 0; y < this.height; y++) {
			for (let x = 0; x < this.width; x++) {
				const currentPosition = { x, y };
				const direction = this.getDirection(currentPosition);

				const trees = this.checkTrees(direction, currentPosition, visibleTrees);

				visibleTrees.push(...trees);
			}
		}

		console.log("GETTING SCENIC SCORES");

		for (let i = 0; i < this.height; i++) {
			for (let j = 0; j < this.width; j++) {
				const currentPosition = { x: j, y: i };

				const tree = this.trees[i][j];

				scenicScores.push(this.getScenicScore(tree, currentPosition));
			}
		}

		this.scenicScores = scenicScores;

		this.bestScenicScore = Math.max(...scenicScores);

		this.visibleTrees = visibleTrees;

		this.numVisibleTrees = this.visibleTrees.length;
	}

	getScenicScore(tree, currentPosition) {
		const scores = { left: 0, right: 0, up: 0, down: 0 };

		const directions = ["left", "right", "up", "down"];

		let previousTrees = [];

		for (let i = 0; i < directions.length; i++) {
			const direction = directions[i];

			const xMod = direction === "left" ? 1 : direction === "right" ? -1 : 0;
			const yMod = direction === "up" ? -1 : direction === "down" ? 1 : 0;

			let distance;

			if (direction === "right") {
				distance = currentPosition.x;
			} else if (direction === "left") {
				distance = this.width - currentPosition.x - 1;
			} else if (direction === "up") {
				distance = currentPosition.y;
			} else if (direction === "down") {
				distance = this.height - currentPosition.y - 1;
			}

			// console.log("CHECKING", direction, "DIRECTION", distance, "DISTANCE", xMod, yMod);

			previousTrees = [];
			for (let j = 1; j <= distance; j++) {
				const newX = currentPosition.x + xMod * j;
				const newY = currentPosition.y + yMod * j;
				previousTrees.push(this.trees[newY][newX]);

				const check = Forest.checkIfTallerThanPreviousTrees(previousTrees, tree);

				if (check === "accept") {
					// console.log("+ ADDING SCORE");
					scores[direction] += 1;
				} else {
					// console.log("+ ADDING SCORE THEN BREAKING");
					scores[direction] += 1;
					break;
				}
			}
		}

		// console.log(
		// 	`SCORES FOR TREE ${tree.height} AT ${currentPosition.x}, ${currentPosition.y}:`,
		// 	scores
		// );

		// console.log(`TOTAL SCORE: ${scores.left * scores.right * scores.up * scores.down} \n`);

		return scores.left * scores.right * scores.up * scores.down;
	}

	checkTrees(direction, currentPosition, alreadyVisibleTrees) {
		const { x, y } = currentPosition;
		if (direction === "middle") return [];
		if (direction === "corner") {
			if (!alreadyVisibleTrees.find((tree) => tree.id === this.trees[y][x].id)) {
				// console.log(" + ADDING CORNER TREE", this.trees[y][x].height);
				return [this.trees[y][x]];
			}

			return [];
		}

		const visibleTrees = [];

		const xMod = direction === "left" ? 1 : direction === "right" ? -1 : 0;
		const yMod = direction === "up" ? -1 : direction === "down" ? 1 : 0;

		const distance = direction === "left" || direction === "right" ? this.width : this.height;

		// let previousTree = -1;
		let previousTrees = [];

		let newX = x;
		let newY = y;

		for (let i = 1; i < distance; i++) {
			if (newX < 0 || newY < 0 || newX >= this.width || newY >= this.height) break;

			console
				.log
				// `CHECKING TREE AT ${newX}, ${newY} IN ${direction} DIRECTION HAS HEIGHT ${this.trees[newY][newX].height}`
				();

			const check = Forest.checkIfTallerThanPreviousTrees(previousTrees, this.trees[newY][newX]);
			if (check === "accept") {
				if (alreadyVisibleTrees.find((tree) => tree.id === this.trees[newY][newX].id)) {
					// console.log(` - DECLINING TREE AT ${newX}, ${newY} BECAUSE IT'S ALREADY VISIBLE`);
					// previousTree = this.trees[newY][newX].height;
					previousTrees.push(this.trees[newY][newX]);
				} else {
					// console.log(` + ADDING TREE AT ${newX}, ${newY}`);
					visibleTrees.push(this.trees[newY][newX]);
					// previousTree = this.trees[newY][newX].height;
					previousTrees.push(this.trees[newY][newX]);
				}
			} else {
			}

			newX = x + xMod * i;
			newY = y + yMod * i;

			// console.log(`NEW X: ${newX}, NEW Y: ${newY}`);
		}

		console
			.log
			// `TREE AT ${x}, ${y} CAN SEE ${visibleTrees.length} TREES IN ${direction} DIRECTION \n`
			();
		return visibleTrees;
	}

	getDirection(currentPosition) {
		let { x, y } = currentPosition;

		if (x === 0 && y === 0) return "corner";
		if (x === 0 && y === this.height - 1) return "corner";
		if (x === this.width - 1 && y === 0) return "corner";
		if (x === this.width - 1 && y === this.height - 1) return "corner";

		if (x === 0) return "left";
		if (x === this.width - 1) return "right";
		if (y === 0) return "down";
		if (y === this.height - 1) return "up";

		return "middle";
	}

	static checkIfTallerThanPreviousTrees(previousTrees, tree) {
		console.log(previousTrees.map((tree) => tree.height));
		if (previousTrees.length === 0) {
			// console.log(" + NO PREVIOUS TREES, ACCEPTING TREE");
			return "accept";
		}

		for (let i = 0; i < previousTrees.length; i++) {
			if (previousTrees[i].height >= tree.height) {
				if (previousTrees[i].height === tree.height) {
					return "equal";
				}

				// console.log(` - DECLINING TREE BECAUSE IT'S NOT TALLER THAN ${previousTrees[i].height}`);
				return "decline";
			}
		}

		return "accept";
	}
}

const treeLines = fs.readFileSync("input.txt", "utf-8").split("\n");

const forest = new Forest(treeLines);

console.log(forest);
