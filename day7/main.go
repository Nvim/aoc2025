package main

import (
	"bufio"
	"fmt"
	"os"
)

const RAY = '|'
const SPLITTER = '^'
const EMPTY = '.'

type Grid struct {
	Bytes  [][]byte
	Width  int
	Height int
}

func (g *Grid) Get(x, y int) byte {
	if x >= g.Width || y >= g.Height || x < 0 || y < 0 {
		return 0
	}

	return g.Bytes[y][x]
}

func (g *Grid) Set(x, y int, val byte) {
	if x < g.Width && y < g.Height && x >= 0 && y >= 0 {
		g.Bytes[y][x] = val
	} else {
		fmt.Printf("(%v - %v is bad)\n", x, y)
	}
}

func (g *Grid) Parse(f *os.File) {
	s := bufio.NewScanner(f)

	s.Split(bufio.ScanLines)

	for s.Scan() {
		b := s.Bytes()
		line := make([]byte, len(b))
		copy(line, b)
		g.Bytes = append(g.Bytes, line)
	}

	g.Width = len(g.Bytes[0])
	g.Height = len(g.Bytes)
	fmt.Printf("w: %v - h: %v\n", g.Width, g.Height)
}

func Part1(grid *Grid) uint64 {
	var count uint64 = 0
	for y := 0; y < grid.Height-1; y++ {
		for x := 0; x < grid.Width; x++ {
			c := grid.Get(x, y)

			switch c {
			case 'S':
				fallthrough
			case RAY:
				if grid.Get(x, y+1) != SPLITTER {
					grid.Set(x, y+1, RAY)
				}

			case SPLITTER:
				if grid.Get(x, y-1) == RAY {
					count++
					if grid.Get(x+1, y) != SPLITTER {
						grid.Set(x+1, y, RAY)
					}
					if grid.Get(x-1, y) != SPLITTER {
						grid.Set(x-1, y, RAY)
						if grid.Get(x-1, y+1) != SPLITTER {
							grid.Set(x-1, y+1, RAY)
						}
					}
				}
			}
		}
	}
	return count
}

func main() {
	f, err := os.Open("input.txt")
	// f, err := os.Open("input_example.txt")
	if err != nil {
		os.Exit(1)
	}
	defer f.Close()

	var grid Grid
	grid.Parse(f)
	count := Part1(&grid)

	// for y := 0; y < grid.Height; y++ {
	// 	for x := 0; x < grid.Width; x++ {
	// 		fmt.Printf("%c", grid.Get(x, y))
	// 	}
	// 	fmt.Printf("\n")
	// }
	fmt.Printf("Count: %v\n", count)
}
