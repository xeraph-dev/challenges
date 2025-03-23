import SwiftUI

@main
struct Circle_DrawerApp: App {
    @StateObject var state = AppState()

    var body: some Scene {
        WindowGroup {
            ContentView()
                .fixedSize()
                .environmentObject(state)
                .onDisappear {
                    state.selected = nil
                }
        }
        .windowResizability(.contentSize)

        WindowGroup("Edit circle", id: Windows.edit.rawValue) {
            EditView()
                .fixedSize()
                .environmentObject(state)
                .onDisappear {
                    state.update()
                }
        }
        .windowResizability(.contentSize)
        .handlesExternalEvents(matching: Set(arrayLiteral: "Edit circle"))
    }
}
