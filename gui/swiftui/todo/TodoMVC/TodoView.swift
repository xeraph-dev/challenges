import SwiftUI

struct TodoView: View {
    @EnvironmentObject private var state: TodoState

    @Binding var todo: Todo
    @State private var text = ""
    @FocusState private var focused: Bool

    var onDelete: () -> Void

    var body: some View {
        HStack {
            Image(systemName: todo.completed ? "checkmark.circle" : "circle")
                .font(.title)
                .onTapGesture {
                    todo.completed.toggle()
                }

            if state.selected == todo {
                TextField("", text: $text)
                    .font(.title2)
                    .focused($focused)
                    .onSubmit {
                        if !text.isEmpty {
                            todo.text = text
                        }
                        state.selected = nil
                        text = ""
                        focused = false
                    }
            } else {
                Text(todo.text)
                    .strikethrough(todo.completed)
                    .font(.title2)
                    .foregroundColor(todo.completed ? .secondary : .primary)
                    .onTapGesture(count: 2) {
                        if !todo.completed {
                            text = todo.text
                            focused = true
                            state.selected = todo
                        }
                    }
            }

            Spacer()
            if state.hovered == todo {
                Button(action: onDelete) {
                    Image(systemName: "xmark")
                }
                .buttonStyle(.plain)
            }
        }
        .padding(.vertical, 4)
        .onHover { over in
            if over {
                state.hovered = todo
            } else if state.hovered == todo {
                state.hovered = nil
            }
        }
        .onTapGesture {
            state.hovered = todo
            if state.hovered != state.selected {
                state.selected = nil
                focused = false
                text = ""
            }
        }
    }
}

struct TodoView_Previews: PreviewProvider {
    static var previews: some View {
        TodoView(todo: .constant(Todo(text: "Test"))) {}
            .environmentObject(TodoState())
    }
}
