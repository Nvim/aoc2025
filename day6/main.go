package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
	"unicode"
	"unicode/utf8"
)

type Operation byte

const (
	ADD Operation = iota
	MUL
	BAD
)

func GetOp(str string) Operation {
	switch str {
	case "+":
		return ADD
	case "*":
		return MUL
	}
	return BAD
}

func (o Operation) Do(a uint64, b uint64) uint64 {
	switch o {
	case ADD:
		return a + b
	case MUL:
		return a * b
	}
	return a
}

func Part1(s *bufio.Scanner) {

	count := uint64(0)
	columns := make([][]uint64, 0)
	ops := make([]Operation, 0)

	// 1st pass outside loop to init slices
	s.Scan()
	line := s.Text()
	for str := range strings.FieldsSeq(line) {
		num, _ := strconv.ParseUint(str, 10, 64)
		columns = append(columns, []uint64{num})
	}

	// Fill columns
	for s.Scan() {
		line := s.Text()
		r, _ := utf8.DecodeRuneInString(strings.TrimLeft(line, " ")[0:])
		if !unicode.IsDigit(r) {
			// last line
			for str := range strings.FieldsSeq(line) {
				ops = append(ops, GetOp(str))
			}
			break
		}
		for i, str := range strings.Fields(line) {
			num, _ := strconv.ParseUint(str, 10, 64)
			columns[i] = append(columns[i], num)
		}
	}

	// Run OP on each column
	for i := range columns {
		total := columns[i][0]
		for j := 1; j < len(columns[i]); j++ {
			total = ops[i].Do(total, columns[i][j])
		}
		fmt.Printf("column %v: %v -> %v\n", i, columns[i], total)
		count += total
	}

	fmt.Printf("Count: %v\n", count)
}

func main() {
	f, err := os.Open("input.txt")
	// f, err := os.Open("input_example.txt")
	if err != nil {
		os.Exit(1)
	}
	defer f.Close()
	s := bufio.NewScanner(f)

	s.Split(bufio.ScanLines)
	Part1(s)
}
