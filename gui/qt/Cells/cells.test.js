// valid expressions are:
// - single numbers: 5; -5, 5.5, -5.5
// - formulas:
//	 - binary operations: 5 + 5, 10 / 2, B1 + 5, SUM(B1:C10) + A1 + 2, (2 + 2) * 3
//	 	- support: expressions, numbers and cells and ranges
//		- all parenthesis should be paired
//	 - functions: SUM, SUB, MUL, DIV
//	 	- support: expressions, numbers, cells and ranges
//		- trailing comma is not allowed

const columns = 8
const rows = 24

const state = {
	cells: []
}

function resetCells() {
	state.cells = Array.from({ length: columns * rows }).map((_, index) => createCell(index))
}

function setCellValue(x, y, value) {
	state.cells[x * y + x].value = value
}

function getCellVisualValue(x, y) {
	return state.cells[x * y + x].visualValue
}

function createCell(index) {
	const x = index % columns
	const y = Math.floor(index / columns)

	return { "point": { "x": x, "y": y }, "value": "" }
}

function eof(str, idx) {
	return str.length <= idx
}

function tryScanNumber(str, idx) {
	if (eof(str, idx)) return [idx, null]
	if (!'-.0123456789'.includes(str[idx])) return [idx, null]

	const startIdx = idx

	const isNegative = str[idx] === "-"
	if (isNegative) idx++

	let hasDot = false

	while (!eof(str, idx)) {
		if (str[idx] >= "0" && str[idx] <= "9") idx++
		else if (str[idx] === ".") {
			if (hasDot) throw new Error(`scan: invalid character at ${idx}: numbers can have one one dot`)
			if (idx === 0) throw new Error(`scan: invalid character at ${idx}: numbers can not start with a dot (.)`)
			if (isNegative && idx === 1) throw new Error(`scan: invalid character at ${idx}: negative numbers can not start with a dot (.)`)

			hasDot = true
			idx++
		} else {
			break
		}
	}

	if (str[idx - 1] === ".") throw new Error(`scan: invalid character at ${idx}: numbers can not end with a dot (.)`)

	return [idx, { type: "number", value: str.slice(startIdx, idx) }]
}

function tryScanBinaryOperator(str, idx) {
	if (eof(str, idx)) return [idx, null]
	if (!'+-*/'.includes(str[idx])) return [idx, null]

	return [idx + 1, { type: "binary-operator", value: str[idx] }]
}

function scanCell(str) {
	const tokens = []
	let token = null
	let idx = 0

	while (!eof(str, idx)) {
		if (token === null) [idx, token] = tryScanNumber(str, idx)
		if (token === null) [idx, token] = tryScanBinaryOperator(str, idx)
		if (token === null) throw new Error(`scan: unexpected character at ${idx}`)

		tokens.push(token)
		token = null
	}

	return tokens
}

function tryParseNumber(tokens, idx) {
	if (eof(tokens, idx)) return [idx, null]
	if (tokens[idx].type !== "number") return [idx, null]
	return [idx + 1, { type: "number", value: parseFloat(tokens[idx].value) }]
}

function tryParseBinaryOperation(tokens, idx) {
	if (eof(tokens, idx)) return [idx, null]

	const startIdx = idx

	let left = null
	let right = null
	let operator = null;

	;[idx, left] = tryParseNumber(tokens, idx)
	if (left === null) return [startIdx, null]
	if (eof(tokens, idx)) return [startIdx, null]
	if (tokens[idx].type !== "binary-operator") return [startIdx, null]
	operator = tokens[idx].value;
	idx++;
	;[idx, right] = tryParseNumber(tokens, idx)
	if (right === null) throw new Error(`parse: missing right part of binary operation`)

	return [idx, { type: "binary-operation", operator, left, right }]
}

function tryParseExpression(tokens, idx) {
	let atom = null

	if (atom === null) [idx, atom] = tryParseBinaryOperation(tokens, idx)
	if (atom === null) [idx, atom] = tryParseNumber(tokens, idx)
	if (atom === null) throw new Error(`parse: unexpected token at ${idx}`)

	return [idx, atom]
}

function parseCell(tokens) {
	const ast = []

	let atom = null
	let idx = 0

	while (!eof(tokens, idx)) {
		;[idx, atom] = tryParseExpression(tokens, idx)
		ast.push(atom)
	}

	return ast
}

function tryEvalNumber(atom) {
	if (atom.type !== "number") return null
	return atom.value
}


function evalCell(ast) {
	let value = null
	let idx = 0

	if (value === null) value = tryEvalNumber(ast[idx++])

	return value
}

function processCell(index) {
	let value = state.cells[index].value.trim()

	if (value.startsWith("=")) {
		try {
			const tokens = scanCell(value.slice(1))
			const ast = parseCell(tokens)
			value = evalCell(ast).toString()
		} catch (error) {
			console.log(error)
			value = "error"
		}
	}

	state.cells[index].visualValue = value
}

const { describe, it, beforeEach } = require('node:test')
const assert = require('node:assert')

describe('eof', () => {
	it('empty string', () => {
		assert.ok(eof('', 0))
	})

	it('non-empty string, not eof', () => {
		assert.ok(!eof('a', 0))
	})

	it('non-empty string, eof', () => {
		assert.ok(eof('a', 1))
	})
})

describe('tryScanNumber', () => {
	describe("valid number", () => {
		it('unsigned integer', () => {
			assert.deepEqual(tryScanNumber("5", 0), [1, { type: "number", value: "5" }])
		})

		it('non-zero index', () => {
			assert.deepEqual(tryScanNumber("+ 5+", 2), [3, { type: "number", value: "5" }])
		})

		it("signed integer", () => {
			assert.deepEqual(tryScanNumber("-5", 0), [2, { type: "number", value: "-5" }])
		})

		it("unsigned real", () => {
			assert.deepEqual(tryScanNumber("5.5", 0), [3, { type: "number", value: "5.5" }])
		})

		it("signed real", () => {
			assert.deepEqual(tryScanNumber("-5.5", 0), [4, { type: "number", value: "-5.5" }])
		})
	})

	describe("skip scanner", () => {
		it("eof", () => {
			assert.deepEqual(tryScanNumber("5", 1), [1, null])
		})

		it("not a number", () => {
			assert.deepEqual(tryScanNumber("a", 0), [0, null])
		})
	})

	describe("scanner errors", () => {
		it("numbers can have one one dot", () => {
			assert.throws(() => tryScanNumber("5..5", 0), new Error('scan: invalid character at 2: numbers can have one one dot'))
		})

		it("numbers can not start with a dot (.)", () => {
			assert.throws(() => tryScanNumber(".5", 0), new Error("scan: invalid character at 0: numbers can not start with a dot (.)"))
		})

		it("negative numbers can not start with a dot (.)", () => {
			assert.throws(() => tryScanNumber("-.5", 0), new Error("scan: invalid character at 1: negative numbers can not start with a dot (.)"))
		})

		it("numbers can not end with a dot (.)", () => {
			assert.throws(() => tryScanNumber("5.", 0), new Error("scan: invalid character at 2: numbers can not end with a dot (.)"))
		})
	})
})

describe('tryScanNumber', () => {
	describe("valid operators", () => {
		assert.deepEqual(tryScanBinaryOperator("+", 0), [1, { type: "binary-operator", value: "+" }])
		assert.deepEqual(tryScanBinaryOperator("-", 0), [1, { type: "binary-operator", value: "-" }])
		assert.deepEqual(tryScanBinaryOperator("*", 0), [1, { type: "binary-operator", value: "*" }])
		assert.deepEqual(tryScanBinaryOperator("/", 0), [1, { type: "binary-operator", value: "/" }])
	})
})

describe("scanCell", () => {
	it("single number", () => {
		assert.deepEqual(scanCell("5"), [{ type: "number", value: "5" }])
	})

	it("unexpected character", () => {
		assert.throws(() => scanCell("5©"), new Error("scan: unexpected character at 1"))
	})
})

describe("tryParseNumber", () => {
	it("valid number token", () => {
		assert.deepEqual(tryParseNumber(scanCell("5"), 0), [1, { type: "number", value: 5 }])
	})

	it("non-zero index", () => {
		assert.deepEqual(tryParseNumber([{ type: "__test__", value: "10" }, { type: "number", value: "5" }], 1), [2, { type: "number", value: 5 }])
	})

	describe("skip parser", () => {
		it("eof", () => {
			assert.deepEqual(tryParseNumber([{ type: "__test__", value: "5" }], 1), [1, null])
		})

		it("not a number token", () => {
			assert.deepEqual(tryParseNumber([{ type: "__test__", value: "5" }], 0), [0, null])
		})
	})
})

describe("tryParseBinaryOperation", () => {
	it("valid operation with numbers", () => {
		assert.deepEqual(tryParseBinaryOperation(scanCell("5+3"), 0), [3, {
			type: "binary-operation",
			operator: "+",
			left: { type: "number", value: "5" },
			right: { type: "number", value: "3" }
		}])
	})
})

describe("parseCell", () => {
	it("single number", () => {
		assert.deepEqual(parseCell(scanCell("5")), [{ type: "number", value: 5 }])
	})

	it("binary operation with numbers", () => {
		assert.deepEqual(parseCell(scanCell("5+3")), [{
			type: "binary-operation",
			operator: "+",
			left: { type: "number", value: "5" },
			right: { type: "number", value: "3" }
		}])
	})

	it("unexpected character", () => {
		assert.throws(() => parseCell([...scanCell("5"), { type: "__test__", value: "©" }]), new Error("parse: unexpected token at 1"))
	})
})

describe("tryEvalNumber", () => {
	it("valid number atom", () => {
		assert.deepEqual(tryEvalNumber(parseCell(scanCell("5"))[0]), 5)
	})

	describe("skip eval", () => {
		it("not a number atom", () => {
			assert.deepEqual(tryEvalNumber([{ type: "__test__", value: 5 }]), null)
		})
	})
})

describe("evalCell", () => {
	it("single number", () => {
		assert.deepEqual(evalCell(parseCell(scanCell("5"))), 5)
	})
})

describe("processCell", () => {
	beforeEach(() => resetCells())

	it("single raw number", () => {
		setCellValue(0, 0, "5")
		processCell(0)
		assert.deepEqual(getCellVisualValue(0, 0), "5")
	})

	it("single number", () => {
		setCellValue(0, 0, "=-5.5")
		processCell(0)
		assert.deepEqual(getCellVisualValue(0, 0), "-5.5")
	})
})
