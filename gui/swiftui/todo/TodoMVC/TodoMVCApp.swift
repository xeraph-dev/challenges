import SwiftUI

@main
struct TodoMVCApp: App {
    @State private var state = TodoState()

    var body: some Scene {
        WindowGroup {
            ContentView()
                .fixedSize()
                .environmentObject(state)
        }
        .windowResizability(.contentSize)
    }
}
