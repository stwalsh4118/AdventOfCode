import * as fs from "fs";

class FileSystem {
	constructor(databuffer) {
		this.fileStructure = [];

		this.parseFileSystemCommands(databuffer);
	}

	parseFileSystemCommands(databuffer) {
		let currentDirectory = "/";

		for (let i = 0; i < databuffer.length; i++) {
			const command = databuffer[i];

			const split = command.split(" ");

			if (split[0] === "$") {
				const result = this.executeCommand(command, currentDirectory, databuffer, i);

				//if we ls
				if (typeof result === "object") {
					findItemInFileTree(this.fileStructure[0], currentDirectory).contains.push(
						...result.map((item) => {
							const split = item.split(" ");
							const name =
								currentDirectory === "/"
									? currentDirectory + split[1]
									: currentDirectory + "/" + split[1];
							const type = split[0] === "dir" ? "directory" : "file";

							return new FileSystemItem(
								name,
								type === "directory" ? 0 : split[0],
								type,
								[],
								currentDirectory
							);
						})
					);

					continue;
				}

				//if we cd up
				if (result === "..") {
					currentDirectory = currentDirectory.split("/").slice(0, -1).join("/");
					continue;
				}

				//if we cd down

				const temp =
					currentDirectory === "/"
						? result === "/"
							? "/"
							: "/" + result
						: currentDirectory + "/" + result;

				//if we cd into new directory

				if (!findItemInFileTree(this.fileStructure[0], temp)) {
					this.fileStructure.push(new FileSystemItem(temp, 0, "directory", [], currentDirectory));
				}

				//if we cd into existing directory

				currentDirectory = temp;
			}
		}
	}

	executeCommand(command, currentDirectory, databuffer, currentCommandIndex) {
		const split = command.split(" ");

		switch (split[1]) {
			case "ls":
				const list = [];

				for (let i = currentCommandIndex + 1; i < databuffer.length; i++) {
					if (databuffer[i].split(" ")[0] === "$") return list;

					list.push(databuffer[i]);
				}

				return list;
			case "cd":
				return split[2];
		}
	}
}

class FileSystemItem {
	constructor(name, size, type, contains = [], parent = null) {
		this.name = name;
		this.size = size;
		this.type = type;
		this.contains = contains;
		this.parent = parent;
	}

	//recursivly calculate size of directory

	get size() {
		return calculateTotalSizeOfDirectory(this);
	}

	set size(value) {
		this._size = value;
	}
}

const calculateTotalSizeOfDirectory = (directory) => {
	let totalSize = 0;

	for (let i = 0; i < directory.contains.length; i++) {
		if (directory.contains[i].type === "directory") {
			totalSize += calculateTotalSizeOfDirectory(directory.contains[i]);
		} else {
			totalSize += parseInt(directory.contains[i].size);
		}
	}

	return totalSize + parseInt(directory._size);
};

const findItemInFileTree = (fileTree, name) => {
	let temp = "";

	if (!fileTree) {
		return temp;
	}
	if (fileTree.name === name) {
		return fileTree;
	}

	for (let i = 0; i < fileTree.contains.length; i++) {
		if (fileTree.contains[i].type === "directory")
			temp = findItemInFileTree(fileTree.contains[i], name);
		if (fileTree.contains[i].name === name) {
			temp = fileTree.contains[i];
		}

		if (temp) break;
	}

	return temp;
};

const sizeWholeFileTree = (fileTree, limit = 100000000000, list) => {
	if (fileTree.size < limit) list.push(fileTree);

	for (let i = 0; i < fileTree.contains.length; i++) {
		if (fileTree.contains[i].type === "directory") {
			sizeWholeFileTree(fileTree.contains[i], limit, list);
		}
	}
};

const data = fs.readFileSync("input.txt", "utf8").split("\n");

const fileSystem = new FileSystem(data);

const below100kList = [];

sizeWholeFileTree(fileSystem.fileStructure[0], 100000, below100kList);

console.log(`Answer to part 1: ${below100kList.reduce((acc, curr) => acc + curr.size, 0)}`);

const list = [];

sizeWholeFileTree(fileSystem.fileStructure[0], 10000000000000, list);

const totalSize = list[0].size;

const sizeToDelete = totalSize - 40000000;

console.log(
	`Answer to part 2: ${
		list
			.filter((item) => item.size > sizeToDelete)
			.reduce(function (prev, curr) {
				return prev.size < curr.size ? prev : curr;
			}).size
	}`
);
