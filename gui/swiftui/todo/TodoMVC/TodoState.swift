import Foundation

enum TodosState: String, CaseIterable {
    case all, active, completed
}

final class TodoState: ObservableObject {
    @Published var hovered: Todo?
    @Published var selected: Todo?
    @Published var todos = [Todo]()
    @Published var newTodo = ""
    @Published var todosState: TodosState = .all
    var activeCount: Int { todos.filter { !$0.completed }.count }
    var completedCount: Int { todos.filter { $0.completed }.count }

    func create() {
        todos.append(Todo(text: newTodo))
        newTodo = ""
    }

    func delete(_ todo: Todo) {
        guard let index = todos.firstIndex(of: todo)
        else { return }
        todos.remove(at: index)
    }

    func clean() {
        todos.removeAll(where: { $0.completed })
    }

    func complete() {
        let completed = activeCount != 0
        for (i, _) in todos.enumerated() {
            todos[i].completed = completed
        }
    }
}
