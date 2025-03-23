import SwiftUI

struct ContentView: View {
    @EnvironmentObject private var state: TodoState

    var body: some View {
        VStack {
            Text("todos")
                .font(.largeTitle)
                .padding(.horizontal, 16)
                .padding(.top, 8)

            HStack {
                Button(action: state.complete) {
                    Image(systemName: "chevron.down")
                        .font(.title)
                        .foregroundColor(state.activeCount > 0 ? .primary : .secondary)
                }
                .buttonStyle(.plain)
                TextField("What needs to be done?", text: $state.newTodo)
                    .onSubmit(state.create)
            }
            .padding(.horizontal, 16)
            .padding(.vertical, 8)

            ScrollView {
                VStack(spacing: 0) {
                    ForEach($state.todos, id: \.id) { todo in
                        if state.todosState == .all ||
                            (state.todosState == .active && !todo.completed.wrappedValue) ||
                            (state.todosState == .completed && todo.completed.wrappedValue)
                        {
                            TodoView(todo: todo, onDelete: { state.delete(todo.wrappedValue) })
                        }
                    }
                }
            }
            .padding(.horizontal, 16)

            StateView()
        }
        .frame(width: 400, height: 500)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
            .environmentObject(TodoState())
    }
}
