package main

import "fmt"

func main() {
	set := 0
	for true {
		var n_roads int
		fmt.Scanf("%v", &n_roads)
		if n_roads == 0 {
			break
		}

		// Now read in each road
		n_cities := 0
		cities := make(map[string]int) // map city names to integers
		var w [100][100]int

		for road := 0; road < n_roads; road++ {
			var city1, city2 string
			var dist int
			fmt.Scanf("%s %s %d", &city1, &city2, &dist)

			// Add these cities to the city dictionary if they aren't already there
			for _, city := range [2]string{city1, city2} {
				_, ok := cities[city]
				if !ok {
					cities[city] = n_cities
					n_cities++
				}
			}

			// Look up the cities and add this route to the weight matrix
			c1 := cities[city1]
			c2 := cities[city2]
			w[c1][c2] = dist
			w[c2][c1] = dist
		}

		for i := 0; i < n_cities; i++ {
			for n := 0; n < n_cities; n++ {
				for m := 0; m < n_cities; m++ {
					if n == m {
						continue
					}
					if (w[n][i] != 0) && (w[i][m] != 0) {
						// check whether there is now a shorter route from n to m via i
						if (w[n][m] == 0) || ((w[n][i] + w[i][m]) < w[n][m]) {
							w[n][m] = w[n][i] + w[i][m]
							w[m][n] = w[n][m]
						}
					}
				}
			}
		}

		// find maximum
		the_max := 0
		for n := 0; n < n_cities; n++ {
			for m := 0; m < n_cities; m++ {
				if w[n][m] > the_max {
					the_max = w[n][m]
				}
			}
		}

		set++
		fmt.Printf("Set #%v: %v\n", set, the_max)
	}
	return
}
