import * as fs from "fs";

const ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

//class to hold the data for each elf's rucksack
class Rucksack {
	constructor(items) {
		this.items = items;

		//split items into its compartments
		this.compartment1 = items.substr(0, items.length / 2);
		this.compartment2 = items.substr(items.length / 2);

		//get the shared item between compartments
		this.sharedItem = Rucksack.findSharedItems(this.compartment1, this.compartment2)[0];

		//get priority of shared item
		this.sharedItemPriority = Rucksack.getPriorityOfItem(this.sharedItem);
	}

	//finds shared item between compartments
	static findSharedItems = (compartment1, compartment2) => {
		const sharedItems = [];
		for (let i = 0; i < compartment1.length; i++) {
			if (compartment2.includes(compartment1[i])) {
				sharedItems.push(compartment1[i]);
			}
		}
		return sharedItems;
	};

	//returns priority of item
	static getPriorityOfItem = (item) => {
		return ALPHABET.indexOf(item) + 1;
	};
}

//class to hold the data for each elf group
class ElfGroup {
	//holds rucksacks
	constructor(rucksacks) {
		this.rucksacks = rucksacks;
	}

	//get shared items between groups
	get badge() {
		const sharedItems = this.rucksacks.map((rucksack) => {
			//unique letter in string
			const uniqueItems = [...new Set(rucksack.items)];

			return uniqueItems;
		});

		const sharedItemsInAllRucksacks = sharedItems.reduce((acc, curr) => {
			return acc.filter((item) => curr.includes(item));
		});

		return sharedItemsInAllRucksacks[0];
	}
}

const Rucksacks = [];

const lines = fs.readFileSync("input.txt", "utf8").split("\n");

lines.forEach((line) => {
	if (line === "") {
		return;
	}

	Rucksacks.push(new Rucksack(line));
});

console.log(Rucksacks);

//get total priority of shared items
const totalPriority = Rucksacks.reduce((acc, rucksack) => acc + rucksack.sharedItemPriority, 0);

console.log(totalPriority);

const ElfGroups = [];

for (let i = 0; i < Rucksacks.length; i += 3) {
	ElfGroups.push(new ElfGroup(Rucksacks.slice(i, i + 3)));
}

console.log(ElfGroups);

//get total priority of badges
const totalPriorityOfGroups = ElfGroups.reduce((acc, elfGroup) => {
	// console.log(elfGroup.badge);
	return acc + Rucksack.getPriorityOfItem(elfGroup.badge);
}, 0);

console.log(totalPriorityOfGroups);
