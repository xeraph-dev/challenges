import SwiftUI

struct ContentView: View {
    @State private var counter = 0

    var body: some View {
        HStack {
            Text("\(counter)")
                .frame(width: 60, alignment: .leading)
                .padding(.vertical, 4)
                .padding(.horizontal, 8)
                .background(.gray.opacity(0.2))
                .cornerRadius(4)

            Button("Count") {
                counter += 1
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
