import SwiftUI

struct RoundedRectProgressViewStyle: ProgressViewStyle {
    func makeBody(configuration: Configuration) -> some View {
        HStack {
            configuration.label

            GeometryReader { geometry in
                ZStack(alignment: .leading) {
                    RoundedRectangle(cornerRadius: 5)
                        .frame(width: geometry.size.width, height: 20)
                        .foregroundColor(.secondary)
                        .overlay(Color.black.opacity(0.5))
                        .cornerRadius(5)

                    RoundedRectangle(cornerRadius: 5)
                        .frame(
                            width: CGFloat(configuration.fractionCompleted ?? 0) * geometry.size
                                .width
                        )
                        .foregroundColor(.blue)
                }
            }
            .frame(height: 20)
        }
    }
}

struct ContentView: View {
    @State private var elapsedTime = 0.0
    @State private var duration = 20.0
    @State private var timer = Timer.publish(every: 0.1, on: .main, in: .common).autoconnect()

    var body: some View {
        VStack(alignment: .leading) {
            ProgressView("Elapsed time:", value: elapsedTime, total: duration)
                .labelsHidden()
                .progressViewStyle(RoundedRectProgressViewStyle())

            Text("\(String(format: "%.1f", elapsedTime))s")

            Slider(value: $duration, in: 0 ... 100) {
                Text("Duration:")
            }

            Button {
                elapsedTime = 0
                timer = Timer.publish(every: 0.1, on: .main, in: .common).autoconnect()

            } label: {
                Text("Reset")
                    .frame(maxWidth: .infinity)
            }
        }
        .frame(width: 250)
        .padding()
        .onChange(of: duration) { _ in
            if elapsedTime < duration {
                timer = Timer.publish(every: 0.1, on: .main, in: .common).autoconnect()
            }
        }
        .onReceive(timer) { _ in
            if elapsedTime >= duration {
                return timer.upstream.connect().cancel()
            }
            elapsedTime += 0.1
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
