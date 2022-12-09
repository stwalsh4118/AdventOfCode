import * as fs from "fs";
import * as util from "util";

util.inspect.defaultOptions.maxArrayLength = null;

//class to hold triangle sides
class Triangle {
	public sides: number[];

	constructor(sides: number[]) {
		this.sides = sides;
	}

	//checks if triangle is valid
	public isValid(): boolean {
		const [a, b, c] = this.sides;
		return a + b > c && a + c > b && b + c > a;
	}
}

//reads input file
const input = fs.readFileSync("input.txt", "utf8");

//splits input into array of triangles
const triangles = input
	.split("\n")
	.map((line) => line.trim())
	.map((line) => line.split(/\s+/))
	.map((sides) => new Triangle(sides.map((side) => parseInt(side, 10))));

//filters out invalid triangles
const validTriangles = triangles.filter((triangle) => triangle.isValid());

console.log(`Answer to part 1: ${validTriangles.length} triangles are valid.`);

const oneDimensionalTriangles = [];

//splits input into array of triangles
const triangleProccesing = input
	.split("\n")
	.map((line) => line.trim())
	.map((line) => line.split(/\s+/));

//converts 2d array to 1d array
for (let i = 0; i < triangleProccesing.length; i++) {
	oneDimensionalTriangles.push(...triangleProccesing[i]);
}

const columnTriangleSides = [];

//gets every 3rd element from 1d array and puts them into a new array to simulate reading by column
for (let i = 0; i < oneDimensionalTriangles.length; i += 9) {
	let triangleOne = [
		oneDimensionalTriangles[i],
		oneDimensionalTriangles[i + 3],
		oneDimensionalTriangles[i + 6],
	];

	let triangleTwo = [
		oneDimensionalTriangles[i + 1],
		oneDimensionalTriangles[i + 4],
		oneDimensionalTriangles[i + 7],
	];

	let triangleThree = [
		oneDimensionalTriangles[i + 2],
		oneDimensionalTriangles[i + 5],
		oneDimensionalTriangles[i + 8],
	];

	columnTriangleSides.push(triangleOne, triangleTwo, triangleThree);
}

//creates triangle objects from column read array
const columnTriangles = columnTriangleSides.map(
	(sides) => new Triangle(sides.map((side) => parseInt(side, 10)))
);

//filters out invalid triangles
const validColumnTriangles = columnTriangles.filter((triangle) => triangle.isValid());

console.log(`Answer to part 2: ${validColumnTriangles.length} triangles are valid.`);
