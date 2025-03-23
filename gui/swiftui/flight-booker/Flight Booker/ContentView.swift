import SwiftUI

enum FlightType: String, CaseIterable {
    case oneway, `return`
}

struct ContentView: View {
    @State private var selected = FlightType.oneway
    @State private var startDate = Date.now
    @State private var returnDate = Date.now
    @State private var alert = false

    var body: some View {
        VStack {
            Picker("Flight type", selection: $selected) {
                ForEach(FlightType.allCases, id: \.self) { item in
                    Text("\(item.rawValue) flight")
                }
            }
            .labelsHidden()

            DatePicker("Start date", selection: $startDate, displayedComponents: [.date])
                .labelsHidden()
                .datePickerStyle(.field)

            DatePicker("Return date", selection: $returnDate, displayedComponents: [.date])
                .labelsHidden()
                .datePickerStyle(.field)
                .disabled(selected != .return)

            Button { alert = true } label: {
                Text("Book")
                    .frame(maxWidth: .infinity)
            }
            .disabled(startDate > returnDate)
        }
        .frame(width: 150)
        .padding()
        .onChange(of: selected) { newSelected in
            if newSelected != .return {
                returnDate = startDate
            }
        }
        .onChange(of: startDate) { [selected] newStartDate in
            if selected != .return {
                returnDate = newStartDate
            }
        }
        .alert(
            "You have booked a \(selected.rawValue) flight on \(startDate.formatted(date: .complete, time: .omitted))"
                + (selected == .return ?
                    " to return on \(returnDate.formatted(date: .complete, time: .omitted))" : ""),
            isPresented: $alert
        ) {
            Button("OK", role: .cancel) {}
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
