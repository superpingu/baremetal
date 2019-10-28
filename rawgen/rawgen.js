var fs = require('fs');
var getPixels = require("get-pixels");
var program = require('commander');
var gamma = require('./gamma.js');

var inputFilename = "";

program
  .version('0.0.1')
  .usage('<input> [options]')
  .option('-o, --output <filename', 'path of the output raw image')
  .action(function(input) {
      inputFilename = input;
  })
  .parse(process.argv);

var outputFilename = program.output || "image.raw";

loadInput(inputFilename, function(pixels) {
    outputImage(outputFilename, pixels);
});

function loadInput(filename, callback) {
    getPixels(filename, function(err, pixels) {
        if(err) {
            console.log("Bad image path");
            return;
        }
        console.log("Got pixels !");
        callback(pixels);
    });
}

function outputImage(filename, pixels) {
    var out = [];
    for(var i=0; i<8; i++) {
        for(var j=0; j<8; j++) {
            out.push(gamma[pixels.get(i, j, 0)]);
            out.push(gamma[pixels.get(i, j, 1)]);
            out.push(gamma[pixels.get(i, j, 2)]);
        }
    }

    var wstream = fs.createWriteStream(filename);
    wstream.on('finish', function () {
        console.log('raw image saved');
    });
    wstream.write(new Buffer(out));
    wstream.end();
}
