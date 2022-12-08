import * as fs from "fs";

type Direction = "N" | "S" | "E" | "W";

class Command {
	turnDirection: string;
	distance: number;

	constructor(command) {
		const splitCommand = command.split("");
		this.turnDirection = splitCommand[0];
		this.distance = parseInt(splitCommand.slice(1).join(""));
	}
}

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

function executeCommands(input: string): any[] {
	const taxi = new Taxi();
	const commands = input.split(", ").map((command) => new Command(command));
	const positions = [];
	const firstRevisitedPosition = [];

	commands.forEach((command) => {
		taxi.direction = Taxi.transformDirection(taxi.direction, command.turnDirection);

		for (let i = 0; i < command.distance; i++) {
			positions.push({ x: taxi.position.x, y: taxi.position.y });

			if (
				firstRevisitedPosition.length === 0 &&
				positions.filter(
					(position) => position.x === taxi.position.x && position.y === taxi.position.y
				).length > 1
			) {
				firstRevisitedPosition.push({ x: taxi.position.x, y: taxi.position.y });
			}

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
