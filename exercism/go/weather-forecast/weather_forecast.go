// Package weather i'm too lazy to write a good comment.
package weather

// CurrentCondition i'm too lazy to write a good comment.
var CurrentCondition string

// CurrentLocation i'm too lazy to write a good comment.
var CurrentLocation string

// Forecast i'm too lazy to write a good comment.
func Forecast(city, condition string) string {
	CurrentLocation, CurrentCondition = city, condition
	return CurrentLocation + " - current weather condition: " + CurrentCondition
}
