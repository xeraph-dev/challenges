import SwiftUI

struct ContentView: View {
    @State private var celsius = 0.0
    @State private var fahrenheit = 32.0

    var body: some View {
        HStack {
            VStack {
                HStack {
                    TextField("Celsius", value: $celsius, format: .number)
                        .onSubmit {
                            let f = Double(celsius) * (9.0 / 5.0) + 32.0
                            fahrenheit = round(f * 10) / 10
                        }
                        .frame(width: 50)
                    Text("Celsius")
                }

                Text("C = (F - 32) * (5/9)")
                    .font(.caption)
                    .foregroundColor(.gray)
            }

            Text("=")
                .padding(.top, -18)

            VStack {
                HStack {
                    TextField("Fahrenheit", value: $fahrenheit, format: .number)
                        .onSubmit {
                            let c = (Double(fahrenheit) - 32.0) * (5.0 / 9.0)
                            celsius = round(c * 10) / 10
                        }
                        .frame(width: 50)
                    Text("Fahrenheit")
                }

                Text("F = C * (9/5) + 32")
                    .font(.caption)
                    .foregroundColor(.gray)
            }
        }
        .padding()
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
