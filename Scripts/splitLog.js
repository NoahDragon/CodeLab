/*
*	Usage: node splitLog.js ar_sp_InventoryDaybook
*/
var readlines = require("./lib/readlines.js");

var lines = readlines.readlines(process.argv[2]); 
var sp_name = process.argv[3];

var sp_pattern = /(ar_sp|usp)_\w+/gi;
var time_pattern = /\d{2}:\d{2}:\d{2}(\.|:)\d{3}/;

var results = {};

for (var l in lines){
	var c = lines[l];

	if(sp_pattern.test(c)){
		var sp = c.match(sp_pattern);

		if(!results[sp])
			results[sp] = [];

		if(time_pattern.test(c))
			results[sp].push(c);
	}
}
console.log(results[sp_name]);
