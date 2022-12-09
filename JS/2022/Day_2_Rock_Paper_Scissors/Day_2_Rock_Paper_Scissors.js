import * as fs from "fs";

class Rock_Paper_Scissors_Round {
	constructor(player1, player2) {
		this.player1 = player1 === "A" ? "Rock" : player1 === "B" ? "Paper" : "Scissors";
		this.player2 = player2 === "X" ? "Rock" : player2 === "Y" ? "Paper" : "Scissors";
	}

	get points() {
		if (this.player1 === this.player2) {
			return this.player2 === "Rock" ? 4 : this.player2 === "Paper" ? 5 : 6;
		} else if (this.player1 === "Rock" && this.player2 === "Scissors") {
			return 3;
		} else if (this.player1 === "Paper" && this.player2 === "Rock") {
			return 1;
		} else if (this.player1 === "Scissors" && this.player2 === "Paper") {
			return 2;
		} else {
			return this.player2 === "Rock" ? 7 : this.player2 === "Paper" ? 8 : 9;
		}
	}

	static getOriginalInput = (inputName) => {
		return inputName === "Rock" ? "X" : inputName === "Paper" ? "Y" : "Z";
	};

	static getNeededPlay = (opponent, outcome) => {
		const parsedOutcome = outcome === "X" ? "LOSE" : outcome === "Y" ? "TIE" : "WIN";

		if (parsedOutcome === "WIN") {
			return opponent === "Rock" ? "Paper" : opponent === "Paper" ? "Scissors" : "Rock";
		} else if (parsedOutcome === "TIE") {
			return opponent;
		} else {
			return opponent === "Rock" ? "Scissors" : opponent === "Paper" ? "Rock" : "Paper";
		}
	};
}

const Rounds = [];

const lines = fs.readFileSync("input.txt", "utf8").split("\n");

lines.forEach((line) => {
	if (line === "") {
		return;
	}

	const [player1, player2] = line.split(" ");
	Rounds.push(new Rock_Paper_Scissors_Round(player1, player2));
});

const totalPoints = Rounds.reduce((acc, round) => acc + round.points, 0);
const neededPlays = Rounds.map((round) =>
	Rock_Paper_Scissors_Round.getNeededPlay(
		round.player1,
		Rock_Paper_Scissors_Round.getOriginalInput(round.player2)
	)
);

//Question 1 Answer
console.log(`Answer to part 1: ${totalPoints}`);

neededPlays.forEach((play, i) => (Rounds[i].player2 = play));

const totalPoints2 = Rounds.reduce((acc, round) => acc + round.points, 0);
//Question 2 Answer
console.log(`Answer to part 2: ${totalPoints2}`);
