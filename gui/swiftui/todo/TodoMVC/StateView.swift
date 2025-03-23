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

struct StateView: View {
    @EnvironmentObject private var state: TodoState

    var body: some View {
        HStack(spacing: 0) {
            Text("\(state.activeCount) items left")

            Spacer()

            HStack {
                Picker("States", selection: $state.todosState) {
                    ForEach(TodosState.allCases, id: \.self) { todosState in
                        Text(todosState.rawValue.capitalized)
                    }
                }
                .pickerStyle(.segmented)
                .labelsHidden()
                .scaleEffect(0.8)
            }

            Spacer()

            Button("Clear completed", action: state.clean)
                .buttonStyle(.borderless)
                .if(state.completedCount == 0) {
                    $0.hidden()
                }
        }
        .font(.caption)
        .padding(.horizontal, 16)
        .padding(.vertical, 8)
    }
}

struct StateView_Previews: PreviewProvider {
    static var previews: some View {
        StateView()
            .environmentObject(TodoState())
            .frame(width: 400)
    }
}
