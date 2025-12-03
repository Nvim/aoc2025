package main

import (
	"fmt"
	"io"
	"log"
	"os"
	"strconv"
	"strings"
)

func Part1(input string) {
	ranges := strings.Split(input, ",")

	var count uint64 = 0
	for _, rangeStr := range ranges {
		low := strings.Split(rangeStr, "-")[0]
		high := strings.Split(rangeStr, "-")[1]
		high = strings.TrimSuffix(high, "\n")

		start, err := strconv.ParseUint(low, 10, 64)
		if err != nil {
			log.Fatal("couldnt parse uint: ", err)
			return
		}
		end, err := strconv.ParseUint(high, 10, 64)
		if err != nil {
			log.Fatal("couldnt parse uint: ", err)
			return
		}

		for i := start; i <= end; i++ {
			numStr := strconv.FormatUint(i, 10)
			l := len(numStr)
			if l%2 != 0 {
				continue
			}
			chunk1 := numStr[0:(l / 2)]
			chunk2 := numStr[(l / 2):l]

			if chunk1 == chunk2 {
				// fmt.Printf("%v\n", i)
				count += i
			}
		}
	}
	fmt.Printf("Count: %v\n", count)
}

func Part2(input string) {
	ranges := strings.Split(input, ",")

	var count uint64 = 0
	for _, rangeStr := range ranges {
		low := strings.Split(rangeStr, "-")[0]
		high := strings.Split(rangeStr, "-")[1]
		high = strings.TrimSuffix(high, "\n")

		start, err := strconv.ParseUint(low, 10, 64)
		if err != nil {
			log.Fatal("couldnt parse uint: ", err)
			return
		}
		end, err := strconv.ParseUint(high, 10, 64)
		if err != nil {
			log.Fatal("couldnt parse uint: ", err)
			return
		}

		for i := start; i <= end; i++ {
			numStr := strconv.FormatUint(i, 10)
			l := len(numStr)

			for chunk_sz := 1; chunk_sz <= l/2; chunk_sz++ {
				// fmt.Printf("== %v -- CHUNK SIZE: %v ==\n", numStr, chunk_sz)
				firstChunk := numStr[0:chunk_sz]
				// fmt.Println(firstChunk)
				if l % chunk_sz != 0 {
					continue
				}
				chunkCount := l / chunk_sz
				good := true
				for j := 0; j < chunkCount; j++ {
					c := numStr[j*chunk_sz : (j*chunk_sz)+chunk_sz]
					if c != firstChunk {
						good = false
						break
					}
				}
				if good {
					count += i
					fmt.Printf("* %v (%v)!\n", i, chunk_sz)
					break
				}
			}
		}
	}
	fmt.Printf("Count: %v\n", count)
}

func main() {
	f, err := os.Open("input.txt")
	if err != nil {
		os.Exit(1)
	}
	defer f.Close()

	contents, err := io.ReadAll(f)
	if err != nil {
		os.Exit(1)
	}

	// fmt.Printf("%s\n", contents)
	Part1(string(contents))
	Part2(string(contents))
}
