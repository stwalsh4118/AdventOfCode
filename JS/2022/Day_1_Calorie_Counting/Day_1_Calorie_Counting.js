import * as fs from "fs";
import { faker } from "@faker-js/faker";
import _ from "lodash";

class Elf {
	constructor(foodItems, name, numberInLine) {
		this.foodItems = foodItems;
		this.name = name;
		this.numberInLine = numberInLine;
	}

	get calories() {
		return this.foodItems.reduce((acc, item) => acc + item, 0);
	}

	addFoodItem(foodItem) {
		this.foodItems.push(parseInt(foodItem));
	}

	static readElfData = (inputName, ElfLine) => {
		const lines = fs.readFileSync("input.txt", "utf8").split("\n");

		ElfLine.push(new Elf([], faker.name.firstName(), 1));

		lines.forEach((line) => {
			if (line === "") {
				Elves.push(new Elf([], faker.name.firstName(), ElfLine.length + 1));
				return;
			}

			ElfLine[ElfLine.length - 1].addFoodItem(line);
		});
	};

	static getHighestCalorieElf = (ElfLine) => {
		let highestCalorieElf = ElfLine[0];
		console.log(ElfLine);

		ElfLine.forEach((elf) => {
			console.log(elf.calories, highestCalorieElf.calories);

			if (elf.calories > highestCalorieElf.calories) {
				highestCalorieElf = elf;
			}
		});

		return highestCalorieElf;
	};

	static getHighestCalorieElves = (ElfLine, numElves) => {
		const tempElves = _.cloneDeep(ElfLine);
		const highestCalorieElves = [];

		for (let i = 0; i < numElves; i++) {
			const highestCalorieElf = Elf.getHighestCalorieElf(tempElves);
			highestCalorieElves.push(highestCalorieElf);
			tempElves.splice(tempElves.indexOf(highestCalorieElf), 1);
		}

		const totalCalories = highestCalorieElves.reduce((acc, elf) => acc + elf.calories, 0);

		return [highestCalorieElves, totalCalories];
	};
}

const Elves = [];
Elf.readElfData("input.txt", Elves);

const highestCalorieElf = Elf.getHighestCalorieElf(Elves);

//Question 1 Answer
console.log(highestCalorieElf, highestCalorieElf.calories);

const [highestCalorieElves, totalCalories] = Elf.getHighestCalorieElves(Elves, 3);
//Question 2 Answer
console.log(highestCalorieElves, totalCalories);
