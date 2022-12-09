import * as fs from "fs";
import * as util from "util";

util.inspect.defaultOptions.maxArrayLength = null;

class RopePiece {
	name: string;
	position: {
		x: number;
		y: number;
	};

	constructor(name: string, x: number, y: number) {
		this.name = name;
		this.position = { x, y };
	}
}

class Command {
	direction: string;
	distance: number;

	constructor(command: string) {
		const split = command.split(" ");

		this.direction = split[0] === "L" ? "W" : split[0] === "R" ? "E" : split[0] === "U" ? "N" : "S";
		this.distance = parseInt(split[1]);
	}
}

class Bridge {
	pieces: RopePiece[];
	commands: Command[];

	constructor(pieces: RopePiece[], commands: Command[]) {
		this.pieces = pieces;
		this.commands = commands;
	}

	private checkPiecesTouching(a: RopePiece, b: RopePiece): boolean {
		if (Math.abs(a.position.x - b.position.x) <= 1 && Math.abs(a.position.y - b.position.y) <= 1) {
			return true;
		}

		return false;
	}

	private getDirectionToMove(leader: RopePiece, follower: RopePiece): string {
		if (leader.position.x < follower.position.x && leader.position.y < follower.position.y) {
			return "SW";
		} else if (leader.position.x < follower.position.x && leader.position.y > follower.position.y) {
			return "NW";
		} else if (leader.position.x > follower.position.x && leader.position.y < follower.position.y) {
			return "SE";
		} else if (leader.position.x > follower.position.x && leader.position.y > follower.position.y) {
			return "NE";
		}

		if (leader.position.x < follower.position.x) {
			return "W";
		} else if (leader.position.x > follower.position.x) {
			return "E";
		} else if (leader.position.y < follower.position.y) {
			return "S";
		} else if (leader.position.y > follower.position.y) {
			return "N";
		}

		return "";
	}

	public simulateBridge(): number {
		const tailPositions: { x: number; y: number }[] = [];

		for (let i = 0; i < this.commands.length; i++) {
			const command = this.commands[i];

			for (let j = 0; j < command.distance; j++) {
				switch (command.direction) {
					case "N":
						this.pieces[0].position.y++;
						break;
					case "S":
						this.pieces[0].position.y--;
						break;
					case "E":
						this.pieces[0].position.x++;
						break;
					case "W":
						this.pieces[0].position.x--;
						break;
				}

				for (let k = 1; k < this.pieces.length; k++) {
					const leader = this.pieces[k - 1];
					const follower = this.pieces[k];

					if (!this.checkPiecesTouching(leader, follower)) {
						const directionToMove = this.getDirectionToMove(leader, follower);

						switch (directionToMove) {
							case "N":
								follower.position.y++;
								break;
							case "S":
								follower.position.y--;
								break;
							case "E":
								follower.position.x++;
								break;
							case "W":
								follower.position.x--;
								break;
							case "NE":
								follower.position.x++;
								follower.position.y++;
								break;
							case "NW":
								follower.position.x--;
								follower.position.y++;
								break;
							case "SE":
								follower.position.x++;
								follower.position.y--;
								break;
							case "SW":
								follower.position.x--;
								follower.position.y--;
								break;
						}
					}

					if (
						k === this.pieces.length - 1 &&
						!tailPositions.find((p) => p.x === follower.position.x && p.y === follower.position.y)
					) {
						tailPositions.push({ x: follower.position.x, y: follower.position.y });
					}
				}
			}
		}

		return tailPositions.length;
	}
}

const input = fs.readFileSync("input.txt", "utf-8").split("\n");

const rope2Pieces = Array.from(Array(2).keys()).map((i) => {
	return new RopePiece(`Rope Piece ${i + 1}`, 0, 0);
});

const firstBridge = new Bridge(
	rope2Pieces,
	input.map((command) => new Command(command))
);

console.log(firstBridge.simulateBridge());

const rope10Pieces = Array.from(Array(10).keys()).map((i) => {
	return new RopePiece(`Rope Piece ${i + 1}`, 0, 0);
});

const secondBridge = new Bridge(
	rope10Pieces,
	input.map((command) => new Command(command))
);

console.log(secondBridge.simulateBridge());
