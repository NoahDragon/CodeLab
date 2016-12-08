module.exports = {
	readlines : function (filename){
			var fs = require('fs');

		if (fs.existsSync(filename)) {
			return fs.readFileSync(filename).toString().split(/\r?\n/);
		} else {
			return null;
		}
	}
}
