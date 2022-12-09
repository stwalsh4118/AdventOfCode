import * as fs from "fs";

class Elf {
	constructor(assignedTasks) {
		const taskRange = assignedTasks.split("-");
		this.minTasks = parseInt(taskRange[0]);
		this.maxTasks = parseInt(taskRange[1]);

		const taskList = [];

		for (let i = this.minTasks; i <= this.maxTasks; i++) {
			taskList.push(i);
		}

		this.tasks = taskList;
	}

	//returns true if elf task list fully contains the given task list
	static containsTasks = (tasks, taskList) => {
		return taskList.every((task) => tasks.includes(task));
	};

	static containsPartialTasks = (tasks, taskList) => {
		return taskList.some((task) => tasks.includes(task));
	};
}

class ElfGroup {
	constructor(elfList) {
		this.elves = elfList;

		let overlaps = false;

		this.elves.forEach((elf) => {
			if (!overlaps) {
				overlaps = ElfGroup.containsAllTasks(this.elves, elf.tasks);
			}
		});

		this.overlaps = overlaps;

		let partialOverlap = false;
		this.elves.forEach((elf) => {
			if (!partialOverlap) {
				partialOverlap = ElfGroup.containsPartialTasks(this.elves, elf.tasks);
			}
		});

		this.partialOverlap = partialOverlap;
	}

	//returns true if elf group contains all tasks
	static containsAllTasks = (elves, taskList) => {
		let containsAll = true;

		elves.forEach((elf) => {
			if (!Elf.containsTasks(elf.tasks, taskList)) {
				containsAll = false;
			}
		});

		return containsAll;
	};

	static containsPartialTasks = (elves, taskList) => {
		let containsPartial = true;

		elves.forEach((elf) => {
			if (!Elf.containsPartialTasks(elf.tasks, taskList)) {
				containsPartial = false;
			}
		});

		return containsPartial;
	};
}

const elfGroups = [];

const lines = fs.readFileSync("input.txt", "utf8").split("\n");

let elfList = [];

lines.forEach((line) => {
	const elfGroup = line.split(",").map((elf) => new Elf(elf));
	elfGroups.push(new ElfGroup(elfGroup));
});

//get all elf groups that overlap
const overlappingGroups = elfGroups.filter((group) => group.overlaps);

console.log(`Answer to part 1: ${overlappingGroups.length}`);

//get all elf groups that partially overlap
const partiallyOverlappingGroups = elfGroups.filter((group) => group.partialOverlap);

console.log(`Answer to part 2: ${partiallyOverlappingGroups.length}`);
