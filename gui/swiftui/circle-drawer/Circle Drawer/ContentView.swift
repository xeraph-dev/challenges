import SwiftUI

extension View {
    @ViewBuilder
    func `if`<Content: View>(_ condition: Bool, transform: (Self) -> Content) -> some View {
        if condition {
            transform(self)
        } else {
            self
        }
    }
}

struct ContentView: View {
    @Environment(\.openWindow) private var openWindow
    @Environment(\.supportsMultipleWindows) private var supportsMultipleWindows
    @EnvironmentObject var state: AppState

    var body: some View {
        VStack {
            HStack {
                Button("Undo", action: state.undo)
                    .disabled(!state.canUndo)
                Button("Redo", action: state.redo)
                    .disabled(!state.canRedo)
            }
            ZStack {
                ForEach(state.circles) { circle in
                    Circle()
                        .if(state.selected != circle) {
                            $0.strokeBorder(.primary)
                        }
                        .frame(width: circle.d)
                        .background(Circle().fill(.primary.opacity(0.01)))
                        .position(x: circle.x, y: circle.y)
                        .onTapGesture {
                            guard state.selected == nil else { return }
                            state.selected = circle
                            state.cacheSelected = circle.copy() as? CirclePoint
                            openWindow(id: Windows.edit.rawValue)
                        }
                }
            }
            .frame(width: 300, height: 200)
            .border(.primary)
            .background(.secondary.opacity(0.1))
            .onTapGesture {
                guard state.selected == nil else { return }
                let circle = CirclePoint(id: state.circles.count, x: $0.x, y: $0.y)
                state.circles.append(circle)
                state.append(circle)
            }
        }
        .padding()
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
            .environmentObject(AppState())
    }
}
