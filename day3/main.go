package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
)

func Part1(s *bufio.Scanner) {
	s.Split(bufio.ScanLines)

	var count uint64 = 0
	for s.Scan() {
		line := s.Text()
		high, _ := strconv.ParseUint(string(line[0]), 10, 64)
		high_idx := 0
		for i := 0; i < len(line)-1; i++ {
			digit, _ := strconv.ParseUint(string(line[i]), 10, 64)
			if digit > high {
				high = digit
				high_idx = i
			}
		}

		rest := line[high_idx+1:]
		low, _ := strconv.ParseUint(string(rest[0]), 10, 64)
		for i := 0; i < len(rest); i++ {
			digit, _ := strconv.ParseUint(string(rest[i]), 10, 64)
			if digit > low {
				low = digit
			}
		}
		count += (10 * high) + low
	}
	fmt.Printf("%v\n", count)
}

func Part2(s *bufio.Scanner) {
	s.Split(bufio.ScanLines)

	var count uint64 = 0
	for s.Scan() {
		var linecount uint64 = 0
		line := s.Text()
		high_idx := 0

		for stop := 11; stop >= 0; stop-- {
			high, _ := strconv.ParseUint(string(line[0]), 10, 64)
			for i := 0; i < len(line)-stop; i++ {
				digit, _ := strconv.ParseUint(string(line[i]), 10, 64)
				if digit > high {
					high = digit
					high_idx = i
				}
			}
			inc := high * uint64(math.Pow10(stop))
			linecount += inc
			line = line[high_idx+1:]
			high_idx = 0
		}
		fmt.Printf("%v\n", linecount)
		count += linecount
	}
	fmt.Printf("%v\n", count)
}

func main() {
	f, err := os.Open("input.txt")
	if err != nil {
		os.Exit(1)
	}
	defer f.Close()

	s := bufio.NewScanner(f)
	Part2(s)
}
