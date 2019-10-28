# Rawgen

This script generates raw images, ready to be embedded into an elf, from a
8x8 PNG, JPG or GIF.

## Installation

* install node if you don't have it already (see [https://nodejs.org/en/download/](https://nodejs.org/en/download/))
* run `npm install` (in the directory containing this README)

## Usage

To convert an image use (in the directory containing this README) :

```bash
node rawgen.js <source image file> [-o <destination file>]
```
By default, destination file is set to `./image.raw`.
