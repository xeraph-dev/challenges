package main

import (
	"strconv"

	"fyne.io/fyne/v2/app"
	"fyne.io/fyne/v2/container"
	"fyne.io/fyne/v2/layout"
	"fyne.io/fyne/v2/widget"
)

func main() {
	a := app.New()
	w := a.NewWindow("Counter")

	count := 0

	input := widget.NewEntry()
	input.SetText(strconv.Itoa(count))
	input.Disable()

	button := widget.NewButton("Count", func() {
		count++
		input.SetText(strconv.Itoa(count))
	})

	content := container.New(layout.NewGridLayout(2), input, button)

	w.SetContent(content)

	w.ShowAndRun()
}
