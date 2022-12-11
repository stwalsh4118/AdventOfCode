import * as fs from "fs";
import * as util from "util";

util.inspect.defaultOptions.maxArrayLength = null;

class Monkey {
	id: number;
	heldItems: Item[];
	testDividend: number;
	testFunction: Function;
	operation: Function;
	monkeyBusiness: number = 0;

	constructor(
		id: number,
		testDividend: number,
		testFunction: Function,
		operation: Function,
		startingItems: Item[] = []
	) {
		this.id = id;
		this.testDividend = testDividend;
		this.heldItems = startingItems;
		this.testFunction = testFunction;
		this.operation = operation;
	}
}

class Item {
	value: number;

	constructor(value: number) {
		this.value = value;
	}
}

const findMonkeysWhoCanDivide = (monkeys: Monkey[], number: number): number[] => {
	return monkeys.map((monkey) => {
		return number % monkey.testDividend === 0 ? monkey.testDividend : 1;
	});
};

const input = fs.readFileSync("input.txt", "utf8").split("\n\n");

console.log(input);

const monkeys = input.map((monkeyInput) => {
	const split = monkeyInput.split("\n");

	const id = parseInt(split[0].split(" ")[1][0]);
	const startingItems = split[1]
		.split(": ")[1]
		.split(", ")
		.map((item) => new Item(parseInt(item)));

	const operation = split[2].split("= ")[1];

	const operationFunction = new Function("old", "return " + operation);

	const testCondition = parseInt(split[3].split("by ")[1]);

	const testOutcomes = [split[4], split[5]].map((outcome) => {
		return parseInt(outcome.split("monkey ")[1]);
	});

	const testFunction = new Function(
		"itemValue",

		`return itemValue % ${testCondition} === 0 ? ${testOutcomes[0]} : ${testOutcomes[1]}; `
	);

	return new Monkey(id, testCondition, testFunction, operationFunction, startingItems);

	// console.log(id);
});

for (let i = 0; i < 10000; i++) {
	console.log("\n\nRound " + i);

	for (let j = 0; j < monkeys.length; j++) {
		if (monkeys[j].heldItems.length === 0) continue;

		for (let k = 0; k < monkeys[j].heldItems.length; k++) {
			//inspect item
			monkeys[j].heldItems[k].value = monkeys[j].operation(monkeys[j].heldItems[k].value);

			//monkey business increase
			monkeys[j].monkeyBusiness++;

			//worry drop
			// monkeys[j].heldItems[k].value = Math.floor(monkeys[j].heldItems[k].value / 3);

			// console.log(monkeys[j].heldItems[k].value);

			const divider = monkeys.map((monkey) => monkey.testDividend).reduce((a, b) => a * b, 1);

			monkeys[j].heldItems[k].value = monkeys[j].heldItems[k].value % divider;

			//test worry level
			const monkeyToThrowTo = monkeys[j].testFunction(monkeys[j].heldItems[k].value);

			//throw item
			monkeys[monkeyToThrowTo].heldItems.push(monkeys[j].heldItems[k]);
		}

		monkeys[j].heldItems = [];
	}
}

const compare = (a: Monkey, b: Monkey) => {
	if (a.monkeyBusiness < b.monkeyBusiness) return 1;
	if (a.monkeyBusiness > b.monkeyBusiness) return -1;
	return 0;
};

monkeys.sort(compare);

console.log(monkeys);

console.log(monkeys[0].monkeyBusiness * monkeys[1].monkeyBusiness);
