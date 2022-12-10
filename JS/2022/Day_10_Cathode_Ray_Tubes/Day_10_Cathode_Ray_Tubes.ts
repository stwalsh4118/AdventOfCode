import * as fs from "fs";
import * as util from "util";

util.inspect.defaultOptions.maxArrayLength = null;

class CPU {
	register: number = 1;
	instructions: Instruction[];
	cyclesToCheck: number[];
	screen: Screen;

	constructor(instructions: Instruction[], cyclesToCheck: number[]) {
		this.instructions = instructions;
		this.cyclesToCheck = cyclesToCheck;

		this.screen = new Screen();
	}

	execute(): number[] {
		let cycle = 0;
		const testedCycleStrengths = [];

		for (let i = 0; i < this.instructions.length; i++) {
			if (this.instructions[i].command === "noop") {
				cycle++;

				if (this.cyclesToCheck.includes(cycle)) {
					testedCycleStrengths.push(this.register * cycle);
				}

				continue;
			} else {
				for (let j = 0; j < 2; j++) {
					cycle++;

					if (this.cyclesToCheck.includes(cycle)) {
						testedCycleStrengths.push(this.register * cycle);
					}
				}

				this.register += this.instructions[i].value;
			}
		}

		return testedCycleStrengths;
	}

	drawScreen(): void {
		let cycle = 0;
		let screenHeight = 0;
		this.register = 1;

		for (let i = 0; i < this.instructions.length; i++) {
			if (this.instructions[i].command === "noop") {
				console.log(`Noop AT ${this.register} (${cycle})`);

				if (this.spritePosition(cycle).includes(this.register)) {
					this.screen.pixels[screenHeight][cycle] = "#";
				}

				cycle++;

				console.log(this.spritePosition(cycle), this.spritePosition(cycle).includes(this.register));

				this.screen.print();

				if (cycle % 40 === 0) {
					console.log(`going to new line at ${this.register} (${cycle})`);

					cycle = 0;
					screenHeight++;
				}
			} else {
				for (let j = 0; j < 2; j++) {
					console.log(`adding ${this.instructions[i].value} to ${this.register} at (${cycle})`);

					if (this.spritePosition(cycle).includes(this.register)) {
						this.screen.pixels[screenHeight][cycle] = "#";
					}

					cycle++;

					console.log(
						this.spritePosition(cycle),
						this.spritePosition(cycle).includes(this.register)
					);

					this.screen.print();

					if (cycle % 40 === 0) {
						console.log(`going to new line at ${this.register} (${cycle})`);
						cycle = 0;

						screenHeight++;
					}
				}

				this.register += this.instructions[i].value;
			}
		}
	}

	spritePosition(cycle): number[] {
		return [cycle - 1, cycle, cycle + 1];
	}
}

class Screen {
	pixels: string[][];

	constructor() {
		this.pixels = [];

		for (let i = 0; i < 6; i++) {
			this.pixels.push([]);

			for (let j = 0; j < 50; j++) {
				this.pixels[i].push(".");
			}
		}
	}
	print(): void {
		for (let i = 0; i < 6; i++) {
			console.log(this.pixels[i].join(""));
		}
	}
}

class Instruction {
	command: string;
	value: number;

	constructor(instruction: string) {
		const split = instruction.split(" ");

		this.command = split[0];
		this.value = this.command === "noop" ? 0 : parseInt(split[1]);
	}
}

const input = fs.readFileSync("input.txt", "utf8");

const instructions = input.split("\n").map((i) => new Instruction(i));

console.log(instructions);

const cyclesToCheck = [20, 60, 100, 140, 180, 220];

const cpu = new CPU(instructions, cyclesToCheck);

console.log(cpu.execute().reduce((a, b) => a + b, 0));

cpu.drawScreen();
cpu.screen.print();
