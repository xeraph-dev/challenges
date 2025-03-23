import SwiftUI

@main
struct CRUDApp: App {
    var body: some Scene {
        WindowGroup {
            ContentView()
                .fixedSize()
        }
        .windowResizability(.contentSize)
    }
}
