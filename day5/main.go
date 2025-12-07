package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

type Range struct {
	Start uint64
	End   uint64
}

func parse_range(s string) Range {
	start, err := strconv.ParseUint(strings.Split(s, "-")[0], 10, 64)
	if err != nil {
		log.Fatalf("couldn't parse: %v", fmt.Errorf("%w", err))
		os.Exit(1)
	}
	end, err := strconv.ParseUint(strings.Split(s, "-")[1], 10, 64)
	if err != nil {
		log.Fatalf("couldn't parse: %v", fmt.Errorf("%w", err))
		os.Exit(1)
	}

	return Range{start, end}
}

func Part1(s *bufio.Scanner) {

	count := uint64(0)
	ret := []Range{}

	// var min_range uint64 = math.MaxUint64
	// max_range := uint64(0)
	for s.Scan() {
		line := s.Text()
		if len(line) == 0 {
			break
		}

		ret = append(ret, parse_range(line))
	}

	for s.Scan() {
		idx, _ := strconv.ParseUint(s.Text(), 10, 64)
		for _, r := range ret {
			if idx >= r.Start && idx <= r.End {
				fmt.Printf("%v is fresh\n", idx)
				count++
				break
			}
		}
	}
	fmt.Printf("Fresh count: %v\n", count)
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
