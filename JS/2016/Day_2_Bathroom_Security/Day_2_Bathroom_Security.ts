import * as fs from "fs";

//keypads for reference
const keyPad = [
	[1, 2, 3],
	[4, 5, 6],
	[7, 8, 9],
];

const nonSquareKeyPad = [
	[null, null, 1, null, null],
	[null, 2, 3, 4, null],
	[5, 6, 7, 8, 9],
	[null, "A", "B", "C", null],
	[null, null, "D", null, null],
];

//class to hold commands
class Commands {
	actions: string[][];

	constructor(input: string) {
		this.actions = input.split("\n").map((line) => line.split(""));
	}

	//runs all commands inputted, takes in type of keypad to use
	executeCommands(padType: "square" | "non-square"): number[] {
		let position = padType === "square" ? { x: 1, y: 1 } : { x: 0, y: 2 };
		let pinNumbers = [];

		//loops through all of the commands
		for (let i = 0; i < this.actions.length; i++) {
			//loops through all of the actions in for a command, e.g. UDLR
			for (let j = 0; j < this.actions[i].length; j++) {
				const command = this.actions[i][j];

				//checks if square or non-square keypad, then moves position, then checks if position is valid
				if (padType === "square") {
					switch (command) {
						case "U":
							position.y = Math.max(0, position.y - 1);
							break;
						case "D":
							position.y = Math.min(2, position.y + 1);
							break;
						case "L":
							position.x = Math.max(0, position.x - 1);
							break;
						case "R":
							position.x = Math.min(2, position.x + 1);
							break;
					}
				} else if (padType === "non-square") {
					switch (command) {
						case "U":
							position.y = Math.max(0, position.y - 1);
							if (nonSquareKeyPad[position.y][position.x] === null) {
								position.y++;
							}
							break;
						case "D":
							position.y = Math.min(4, position.y + 1);
							if (nonSquareKeyPad[position.y][position.x] === null) {
								position.y--;
							}
							break;
						case "L":
							position.x = Math.max(0, position.x - 1);
							if (nonSquareKeyPad[position.y][position.x] === null) {
								position.x++;
							}
							break;
						case "R":
							position.x = Math.min(4, position.x + 1);
							if (nonSquareKeyPad[position.y][position.x] === null) {
								position.x--;
							}
							break;
					}
				}
			}

			//pushes the number in position at end of command to the pinNumbers array
			padType === "square"
				? pinNumbers.push(keyPad[position.y][position.x])
				: pinNumbers.push(nonSquareKeyPad[position.y][position.x]);
		}

		return pinNumbers;
	}
}

const input = fs.readFileSync("input.txt", "utf8");

const commands = new Commands(input);

const pinNumbers = commands.executeCommands("square").join("");

console.log(`Answer to part 1: The PIN to the bathroom is ${pinNumbers}`);

const realPinNumbers = commands.executeCommands("non-square").join("");

console.log(`Answer to part 2: The PIN to the bathroom is ${realPinNumbers}`);
