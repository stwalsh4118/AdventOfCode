import * as fs from "fs";

// type for directions
type Direction = "N" | "S" | "E" | "W";

//class to hold commands
class Command {
	turnDirection: string;
	distance: number;

	constructor(command) {
		const splitCommand = command.split("");
		this.turnDirection = splitCommand[0];
		this.distance = parseInt(splitCommand.slice(1).join(""));
	}
}

//Taxi class to hold position and direction
class Taxi {
	position: {
		x: number;
		y: number;
	};

	direction: Direction;

	constructor() {
		this.position = {
			x: 0,
			y: 0,
		};

		this.direction = "N";
	}

	//takes input from command and returns direction
	static transformDirection(direction: Direction, turnDirection: string): Direction {
		if (turnDirection === "R") {
			switch (direction) {
				case "N":
					return "E";
				case "E":
					return "S";
				case "S":
					return "W";
				case "W":
					return "N";
			}
		} else {
			switch (direction) {
				case "N":
					return "W";
				case "E":
					return "N";
				case "S":
					return "E";
				case "W":
					return "S";
			}
		}
	}
}

//runs commands, returns distance from start and first revisited position
function executeCommands(input: string): any[] {
	const taxi = new Taxi();
	//splits input into commands
	const commands = input.split(", ").map((command) => new Command(command));
	const positions = [];
	const firstRevisitedPosition = [];

	//runs all commands
	commands.forEach((command) => {
		//get cardinal direction from command after turning
		taxi.direction = Taxi.transformDirection(taxi.direction, command.turnDirection);

		//moves taxi
		for (let i = 0; i < command.distance; i++) {
			positions.push({ x: taxi.position.x, y: taxi.position.y });

			//checks if taxi has revisited a position
			if (
				firstRevisitedPosition.length === 0 &&
				positions.filter(
					(position) => position.x === taxi.position.x && position.y === taxi.position.y
				).length > 1
			) {
				firstRevisitedPosition.push({ x: taxi.position.x, y: taxi.position.y });
			}

			//moves taxi one unit in direction
			switch (taxi.direction) {
				case "N":
					taxi.position.y += 1;
					break;
				case "E":
					taxi.position.x += 1;
					break;
				case "S":
					taxi.position.y -= 1;
					break;
				case "W":
					taxi.position.x -= 1;
					break;
			}
		}
	});

	return [Math.abs(taxi.position.x) + Math.abs(taxi.position.y), firstRevisitedPosition[0]];
}

const input = fs.readFileSync("input.txt", "utf8");

const [part1, part2] = executeCommands(input);

console.log(`Answer to part 1: ${part1} blocks away.`);
console.log(
	`Answer to part 2: First revisited position is (${part2.x}, ${part2.y}) which is ${
		Math.abs(part2.x) + Math.abs(part2.y)
	} blocks away.`
);
