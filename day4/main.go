package main

import (
	"bufio"
	"fmt"
	"os"
)

type Grid struct {
	Bytes  [][]byte
	Width  int
	Height int
}

func (g *Grid) Get(x, y int) byte {
	if x >= g.Width || y >= g.Height || x < 0 || y < 0 {
		return 0
	}

	switch g.Bytes[y][x] {
	case '@':
		return 1
	case '.':
		return 0
	default:
		fmt.Printf("unexpected byte '%c'(%d) at position (%d, %d)\n", g.Bytes[y][x], g.Bytes[y][x], g.Width, g.Height)
		return 0
	}
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

func Part1(g *Grid) {
	w := g.Width
	h := g.Height

	reachable := 0
	marked := [][2]int{}
	for y := 0; y < h; y++ {
		for x := 0; x < w; x++ {
			if g.Get(x, y) == 0 {
				continue
			}
			top_left := g.Get(x-1, y-1)
			top_mid := g.Get(x, y-1)
			top_right := g.Get(x+1, y-1)
			left := g.Get(x-1, y)
			right := g.Get(x+1, y)
			bot_left := g.Get(x-1, y+1)
			bot_mid := g.Get(x, y+1)
			bot_right := g.Get(x+1, y+1)

			if top_left+top_mid+top_right+left+right+bot_left+bot_mid+bot_right < 4 {
				reachable += 1
				marked = append(marked, [2]int{x, y})
			}
		}
	}

	fmt.Println("Total : ", reachable)
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
	Part1(&grid)
}
