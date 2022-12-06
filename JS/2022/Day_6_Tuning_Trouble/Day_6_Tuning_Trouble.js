import * as fs from "fs";

class Device {
	constructor(databuffer) {
		this.databuffer = databuffer;

		this.packetMarkerEnd = this.findStartOfMarker(4);

		this.messageMarkerEnd = this.findStartOfMarker(14);
	}

	findStartOfMarker(markerLength) {
		//split input
		const split = this.databuffer.split("");

		const markerChecks = [];

		for (let i = 0; i < split.length; i++) {
			const marker = split[i];
			//add new array for symbols
			markerChecks.push([]);

			//for each array of symbols, add the current symbol, then check if it has the correct amount of unique symbols
			for (let j = 0; j < markerChecks.length; j++) {
				markerChecks[j].push(marker);
				if (this.checkUniquenessOfMarker(markerChecks[j], markerLength)) {
					return i + 1;
				}
			}

			//remove arrays that are too long
			for (let j = 0; j < markerChecks.length; j++) {
				if (markerChecks[j].length === markerLength) {
					markerChecks.splice(j, 1);
				}
			}
		}

		return -1;
	}

	checkUniquenessOfMarker(marker, markerLength) {
		if (marker.length === markerLength) {
			console.log(marker, [...new Set(marker)]);
			return [...new Set(marker)].length === markerLength;
		} else {
			return false;
		}
	}
}

const data = fs.readFileSync("input.txt", "utf8");

const device = new Device(data);

console.log(device.packetMarkerEnd);
console.log(device.messageMarkerEnd);
