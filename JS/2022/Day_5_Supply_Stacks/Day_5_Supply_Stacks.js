import * as fs from "fs";

//class to hold the stacks of crates and perform the instructions
class ShippingYard {
	constructor(crateStacks, instructions, model) {
		this.model = model;
		this.stacks = [...crateStacks];
		this.instructions = [...instructions];
	}

	//take instructions and perform them
	performInstructions() {
		for (const instruction of this.instructions) {
			// console.log(
			// 	`Moved ${instruction.amount} crates from stack ${instruction.source} to stack ${instruction.destination}.`
			// );

			if (this.model === 9000) {
				this.moveSingleCrates(instruction);
			} else if (this.model === 9001) {
				this.moveMultipleCrates(instruction);
			}
		}
	}

	//move a single crate at a time
	moveSingleCrates(instruction) {
		for (let i = 0; i < instruction.amount; i++) {
			// console.log(
			// 	`moving crate ${
			// 		this.stacks[instruction.source - 1][this.stacks[instruction.source - 1].length - 1]
			// 			.contents
			// 	} to stack ${instruction.destination}`
			// );
			this.stacks[instruction.destination - 1].push(this.stacks[instruction.source - 1].pop());
		}
	}

	//move multiple crates at a time
	moveMultipleCrates(instruction) {
		const cratesToMove = this.stacks[instruction.source - 1].slice(
			this.stacks[instruction.source - 1].length - instruction.amount
		);
		this.stacks[instruction.source - 1].splice(
			this.stacks[instruction.source - 1].length - instruction.amount
		);
		this.stacks[instruction.destination - 1].push(...cratesToMove);
	}

	//get the top of each stack
	getTopOfStacks() {
		const topOfStacks = [];
		for (const stack of this.stacks) {
			topOfStacks.push(stack[stack.length - 1].contents);
		}
		return topOfStacks.join("");
	}
}

//class to hold the crate contents
class Crate {
	constructor(contents) {
		this.contents = contents;
	}
}

//class to hold the instructions
class Instruction {
	constructor(instruction) {
		const split = instruction.split(" ");
		this.amount = parseInt(split[1]);
		this.source = parseInt(split[3]);
		this.destination = parseInt(split[5]);
	}
}

//read the input file
const lines = fs.readFileSync("input.txt", "utf8").split("\n");

//create the stacks
const stacks = Array.from({ length: (lines[0].split("").length + 1) / 4 }, () => []);

//get start of instructions
const instructionStart = lines.findIndex((line) => line === "");

//add crates to stacks
for (let i = 0; i < lines.length; i++) {
	if (lines[i] === "") break;

	const split = lines[i].split("");

	for (let j = 0; j < split.length; j += 4) {
		const crateContents = split[j + 1];

		if (crateContents === " " || parseInt(crateContents)) continue;

		stacks[j / 4].push(new Crate(split[j + 1]));
	}
}

//reverse the stacks
stacks.forEach((stack) => {
	stack.reverse();
});

const oldStacks = [];

stacks.forEach((stack) => {
	oldStacks.push([...stack]);
});

const instructions = [];

//add instructions to array
for (let i = instructionStart + 1; i < lines.length; i++) {
	instructions.push(new Instruction(lines[i]));
}

const oldShippingYard = new ShippingYard(oldStacks, instructions, 9000);

//perform instructions
oldShippingYard.performInstructions();

//get the top of each stack

console.log(`Answer to part 1: ${oldShippingYard.getTopOfStacks()}`);

//create shipping yard
const shippingYard = new ShippingYard(stacks, instructions, 9001);

//perform instructions
shippingYard.performInstructions();

//get the top of each stack

console.log(`Answer to part 2: ${shippingYard.getTopOfStacks()}`);
